#include "rektifier.h"
#include "IPlug_include_in_plug_src.h"
#include "IPlugPaths.h"
#include "IconsForkAwesome.h"
#include "IconsFontaudio.h"
#include "./preset.h"
#include "./ui.h"

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
: iplug::Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  std::signal(SIGINT, signal_handler);
  GetParam(kParamGain)->InitGain("Gain", 0.0, -90, 40);
  GetParam(kParamGate)->InitGain("Gate", -57.0, -120, 0);
  GetParam(kParamCab)->InitPercentage("Cab", 100.0);
  GetParam(kParamSag)->InitPercentage("Sag", 59.67);
  GetParam(kParamWidth)->InitPercentage("Width", 50.0);
  GetParam(kParamRekt)->InitPercentage("Rekt", 50.0);

  GetParam(kParamInput)->InitEnum("Input", 2, { "Right", "Stereo", "Left" });

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
    const IBitmap switchBitmap = pGraphics->LoadBitmap((PNGSWITCH_FN), 3);
    
    const auto knobOffset = [](int x, int y) {
      const int knobWidth = 130;
      const int knobHeight = 130;
      int w2 = knobWidth / 2;
      int h2 = knobHeight / 2;
      IRECT ret = IRECT(x - w2, y - h2, x + w2, y + h2);
      ret.Translate(2, 17);
      return ret;
    };

    const IRECT size = { 0, 0, 256, 256 };
    

    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(260, 56), knobBitmap, size, kParamGate), kNoTag, "general");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(420, 56), knobBitmap, size, kParamCab), kNoTag, "general");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(585, 56), knobBitmap, size, kParamWidth), kNoTag, "general");

    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(260, 267), knobBitmap, size, kParamGain), kNoTag, "distortion");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(420, 267), knobBitmap, size, kParamRekt), kNoTag, "distortion");
    pGraphics->AttachControl(new FittedBitMapKnob(knobOffset(585, 267), knobBitmap, size, kParamSag), kNoTag, "distortion");

    IRECT switchPost = { 0, 0, 200 / 5, 500 / 5 };
    switchPost.Translate(150, 30);
    pGraphics->AttachControl(new FittedBitMapSwitch(switchPost, switchBitmap, { 0, 0, 200, 500 } , kParamInput), kNoTag, "input");
    
    pGraphics->EnableMouseOver(true);
    pGraphics->EnableMultiTouch(true);
    pGraphics->EnableTooltips(true);
    //pGraphics->AttachTextEntryControl();
    //pGraphics->AttachPopupMenuControl(DEFAULT_LABEL_TEXT);
    //pGraphics->AttachBubbleControl();


  };
#endif

#if IPLUG_DSP
  mGuitard.setConfig(48000, 2, 2);
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


  const double input = GetParam(kParamInput)->Value();
  const double left = input > 0.33;
  const double right = 0.66 > input;

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

  const double cab = GetParam(kParamCab)->GetNormalized();
  mGuitard.setParam(36, cab);

  const double sag = GetParam(kParamSag)->GetNormalized();
  mGuitard.setParam(46, sag);

  const double gain = GetParam(kParamGain)->GetNormalized();
  mGuitard.setParam(33, gain);

  const double gate = GetParam(kParamGate)->GetNormalized();
  mGuitard.setParam(52, gate);

  const double rekt = GetParam(kParamRekt)->GetNormalized();

  const double width = GetParam(kParamWidth)->GetNormalized();

  double pan1;
  double pan2;
  double mix;
  if (rekt <= 0.5) {
    pan1 = -rekt + 0.5;
    pan2 = 1.0;
    mix = rekt * 1.6;
  } else {
    pan1 = 0.0;
    pan2 = -0.6 * rekt + 1.3;
    mix = rekt * 0.4 + 0.6;
  }

  mGuitard.setParam(20, pan1);
  mGuitard.setParam(21, pan2);
  mGuitard.setParam(22, mix);
  mGuitard.setParam(74, width * 0.9);
  mGuitard.setParam(72, iplug::Clip(float(1.0 - width * 0.5), 0.5f, 1.0f));

  mGuitard.process(const_cast<const sample**>(inputs), outputs, nFrames);

  for (int c = 0; c < nChansOut; c++) {
    for (int i = 0; i < nFrames; i++) {
      outputs[c][i] *= 0.5;
    }
  }
}
#endif
