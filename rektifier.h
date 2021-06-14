#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "IControls.h"
#include "IPlugPaths.h"

const int kNumPresets = 1;

enum EParams
{
  kParamGate = 0,
  kParamGain,
  kParamWidth,
  kParamCab,
  kParamRekt,
  kParamSag,
  kParamLeft,
  kParamRight,
  kParamMode,
  kParamFreq1,
  kParamFreq2,
  kNumParams
};

enum EControlTags
{
  kCtrlTagDialogResult = 0,
  kCtrlTagVectorButton,
  kCtrlTagVectorSliderV,
  kCtrlTagVectorSliderH,
  kCtrlTagTabSwitch,
  kCtrlTagRadioButton,
  kCtrlTagScope,
  kCtrlTagDisplay,
  kCtrlTagMeter,
  kCtrlTagRTText,
  kCtrlTagRedLED,
  kCtrlTagGreenLED,
  kCtrlTagBlueLED,
  kCtrlTags
};

using namespace iplug;
using namespace igraphics;

// Class to draw HD background easily
class FittedBitMapControl : public IBitmapControl {
public:
  FittedBitMapControl(const IRECT& bounds, const IBitmap& bitmap) :
    IBitmapControl(bounds, bitmap) { }
  void Draw(IGraphics& g) override {
    IBlend blend = mControl->GetBlend();
    g.DrawFittedBitmap(mBitmap, mControl->GetRECT(), &blend);
  }
};

class rektifier final : public Plugin
{
public:
  rektifier(const InstanceInfo& info);

#if IPLUG_EDITOR
  void OnMidiMsgUI(const IMidiMsg& msg) override;
  void OnUIClose() override;

#endif
  
#if IPLUG_DSP // http://bit.ly/2S64BDd
public:
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnIdle() override;
private:
  IBufferSender<2> mScopeSender;
  IBufferSender<1> mDisplaySender;
  IPeakSender<2> mMeterSender;
  ISender<1> mRTTextSender;
  ISenderData<1> mLastOutputData = { kCtrlTagRTText, 1, 0 };
#endif
};
