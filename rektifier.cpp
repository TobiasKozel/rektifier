#include "rektifier.h"
#include "IPlug_include_in_plug_src.h"
#include "IPlugPaths.h"
#include "IconsForkAwesome.h"
#include "IconsFontaudio.h"

rektifier::rektifier(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
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
    const IBitmap switchBitmap = pGraphics->LoadBitmap((PNGSWITCH_FN), 2, true);
    
    auto knobOffset = [](int x, int y) {
      const int knobWidth = 70;
      const int knobHeight = 70;
      int w2 = knobWidth / 2;
      int h2 = knobHeight / 2;
      return IRECT(x - w2, y - h2, x + w2, y + h2);
    };

    pGraphics->AttachControl(new IBKnobControl(knobOffset(260, 56), knobBitmap, kParamGate), kNoTag, "general");
    pGraphics->AttachControl(new IBKnobControl(knobOffset(420, 56), knobBitmap, kParamCab), kNoTag, "general");
    pGraphics->AttachControl(new IBKnobControl(knobOffset(585, 56), knobBitmap, kParamWidth), kNoTag, "general");

    pGraphics->AttachControl(new IBKnobControl(knobOffset(260, 267), knobBitmap, kParamGain), kNoTag, "distortion");
    pGraphics->AttachControl(new IBKnobControl(knobOffset(420, 267), knobBitmap, kParamRekt), kNoTag, "distortion");
    pGraphics->AttachControl(new IBKnobControl(knobOffset(585, 267), knobBitmap, kParamSag), kNoTag, "distortion");

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
}

#if IPLUG_EDITOR

void rektifier::OnMidiMsgUI(const IMidiMsg& msg) { }

void rektifier::OnUIClose()
{
}

#endif

#if IPLUG_DSP
void rektifier::OnIdle()
{
  mScopeSender.TransmitData(*this);
  mMeterSender.TransmitData(*this);
  mRTTextSender.TransmitData(*this);
  mDisplaySender.TransmitData(*this);

  float val = std::fabs(mLastOutputData.vals[0]);
  //SendControlValueFromDelegate(kCtrlTagRedLED, std::copysign(val, mLastOutputData.vals[0]));
  //SendControlValueFromDelegate(kCtrlTagGreenLED, std::copysign(val, -mLastOutputData.vals[0]));
}

void rektifier::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{

  const int nChans = NOutChansConnected();

  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s];
    }
  }

  return;

  const bool left = 0.5 <= GetParam(kParamLeft)->Value();
  const bool right = 0.5 <= GetParam(kParamRight)->Value();


  const double phaseIncr1 = (1. / GetSampleRate()) * GetParam(kParamFreq1)->Value();
  const double phaseIncr2 = (1. / GetSampleRate()) * GetParam(kParamFreq2)->Value();

  for (int s = 0; s < nFrames; s++) {
    static double phase1 = 0.;
    static double phase2 = 0.;

    outputs[0][s] = cos(phase1 += phaseIncr1);
    outputs[1][s] = sin(phase2 += phaseIncr2);
  }
  
  mDisplaySender.ProcessBlock(outputs, nFrames, kCtrlTagDisplay);
  mScopeSender.ProcessBlock(outputs, nFrames, kCtrlTagScope);
  mMeterSender.ProcessBlock(outputs, nFrames, kCtrlTagMeter);

  mLastOutputData.vals[0] = (float) outputs[0][0]; // just take first value in block

  mRTTextSender.PushData(mLastOutputData);

  for (int s = 0; s < nFrames; s++) {
    outputs[0][s] = 0.;
    outputs[1][s] = 0.;
  }
}
#endif
