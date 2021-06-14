#include "rektifier.h"
#include "IPlug_include_in_plug_src.h"
#include "IPlugPaths.h"
#include "IconsForkAwesome.h"
#include "IconsFontaudio.h"
#include "./preset.h"

#include <csignal>

namespace {
  volatile std::sig_atomic_t gSignalStatus;
}

void signal_handler(int signal) {
  gSignalStatus = signal;
  assert(false);
  exit(signal);
}


rektifier::rektifier(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  std::signal(SIGINT, signal_handler);
  GetParam(kParamGain)->InitGain("Gain");
  GetParam(kParamCab)->InitPercentage("Cab", 100);
  GetParam(kParamGate)->InitGain("Gate", -40);
  GetParam(kParamSag)->InitPercentage("Sag", 50);
  GetParam(kParamWidth)->InitPercentage("Width", 100);
  GetParam(kParamRekt)->InitPercentage("Rekt", 100);

  GetParam(kParamLeft)->InitBool("Left", true);
  GetParam(kParamRight)->InitBool("Right", false);

  GetParam(kParamMode)->InitEnum("Mode", 0, 4, "", IParam::kFlagsNone, "", "one", "two", "three", "four");
  GetParam(kParamFreq1)->InitDouble("Freq 1 - X", 0.5, 0.001, 10., 0.01, "Hz", IParam::kFlagsNone, "", IParam::ShapePowCurve(1.));
  GetParam(kParamFreq2)->InitDouble("Freq 2 - Y", 0.5, 0.001, 10., 0.01, "Hz", IParam::kFlagsNone, "", IParam::ShapePowCurve(1.));

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    if (pGraphics->NControls()) { return; }

    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, true);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();

    auto bgBitMap = pGraphics->LoadBitmap(PNGBG_FN, 1, false);
    IControl* pBG = new FittedBitMapControl(b, bgBitMap);
    pGraphics->AttachControl(pBG);

    const IBitmap knobBitmap = pGraphics->LoadBitmap(PNGKNOB_FN, 60);
    const IBitmap knobBitmapSingle = pGraphics->LoadBitmap(PNGKNOB_FN);
    const IBitmap switchBitmap = pGraphics->LoadBitmap((PNGSWITCH_FN), 2, true);
    
    auto knobOffset = [](int x, int y) {
      const int knobWidth = 130;
      const int knobHeight = 130;
      int w2 = knobWidth / 2;
      int h2 = knobHeight / 2;
      IRECT ret = IRECT(x - w2, y - h2, x + w2, y + h2);
      ret.Offset(0, 10, 0, 10);
      return ret;
    };

    const IRECT size = { 0, 0, 256, 256 };

    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(260, 56), knobBitmap, size, kParamGate), kNoTag, "general");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(420, 56), knobBitmap, size, kParamCab), kNoTag, "general");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(585, 56), knobBitmap, size, kParamWidth), kNoTag, "general");

    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(260, 267), knobBitmap, size, kParamGain), kNoTag, "distortion");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(420, 267), knobBitmap, size, kParamRekt), kNoTag, "distortion");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(585, 267), knobBitmap, size, kParamSag), kNoTag, "distortion");

    pGraphics->AttachControl(new IBSwitchControl({ 150, 26, 193, 66 }, switchBitmap, kParamLeft), kNoTag, "input");
    pGraphics->AttachControl(new IBSwitchControl({ 150, 73, 193, 141 }, switchBitmap, kParamRight), kNoTag, "input");
    
    pGraphics->EnableMouseOver(true);
    pGraphics->EnableMultiTouch(true);
    pGraphics->EnableTooltips(true);
    //pGraphics->AttachTextEntryControl();
    //pGraphics->AttachPopupMenuControl(DEFAULT_LABEL_TEXT);
    //pGraphics->AttachBubbleControl();


    //const IText forkAwesomeText{ 16.f, "ForkAwesome" };
    //const IText bigLabel{ 24, COLOR_WHITE, "Roboto-Regular", EAlign::Near, EVAlign::Top, 0 };
    //const IText fontaudioText{ 32.f, "Fontaudio" };

  };
#endif

#if IPLUG_DSP
  mGuitard.setConfig(60000, 2, 2);
  mGuitard.load(preset);
#endif
}

#if IPLUG_EDITOR

void rektifier::OnMidiMsgUI(const IMidiMsg& msg) { }

void rektifier::OnUIClose()
{
}

#endif

#if IPLUG_DSP
void rektifier::OnIdle() {
  return;
  mScopeSender.TransmitData(*this);
  mMeterSender.TransmitData(*this);
  mRTTextSender.TransmitData(*this);
  mDisplaySender.TransmitData(*this);

  float val = std::fabs(mLastOutputData.vals[0]);
  //SendControlValueFromDelegate(kCtrlTagRedLED, std::copysign(val, mLastOutputData.vals[0]));
  //SendControlValueFromDelegate(kCtrlTagGreenLED, std::copysign(val, -mLastOutputData.vals[0]));
}

void rektifier::OnReset() {
  const int sr = static_cast<int>(GetSampleRate());
  const int outputChannels = NOutChansConnected();
  const int inputChannels = NInChansConnected();
  if (sr > 0 && outputChannels > 0 && inputChannels > 0) {
     mGuitard.setConfig(sr, outputChannels, inputChannels);
  }
}

void rektifier::OnActivate(bool active) {
   mGuitard.reset();
}

void rektifier::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const int nChansOut = NOutChansConnected();
  const int nChansIn = NInChansConnected();

  for (int c = 0; c < nChansOut; c++) {
    for (int i = 0; i < nFrames; i++) {
      outputs[c][i] = 0.0;
    }
  }


  const bool left = 0.5 <= GetParam(kParamLeft)->Value();
  const bool right = 0.5 <= GetParam(kParamRight)->Value();

  if (nChansIn == 1) {
    assert(false);
    // needs to be handled
  }

  if (left && !right) {
    for (int i = 0; i < nFrames; i++) {
      inputs[1][i] = inputs[0][i];
    }
  }
  if (right && !left) {
    for (int i = 0; i < nFrames; i++) {
      inputs[0][i] = inputs[1][i];
    }
  }

  mGuitard.process(const_cast<const sample**>(inputs), outputs, nFrames);

  //mDisplaySender.ProcessBlock(outputs, nFrames, kCtrlTagDisplay);
  //mScopeSender.ProcessBlock(outputs, nFrames, kCtrlTagScope);
  //mMeterSender.ProcessBlock(outputs, nFrames, kCtrlTagMeter);

  //mLastOutputData.vals[0] = (float) outputs[0][0]; // just take first value in block

  //mRTTextSender.PushData(mLastOutputData);

}
#endif
