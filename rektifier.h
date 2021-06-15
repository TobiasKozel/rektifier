#pragma once
//#define SOUNDWOOFER_NO_API
#include "./config.h"
#include "./GuitarD/src/headless/compile_unit/GHeadlessUnit.h"
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
  kNumParams
};

enum EControlTags
{
  kCtrlTags
};

using namespace iplug;
using namespace igraphics;

// Class to draw scaled background
class FittedBitMapControl : public IBitmapControl {
public:
  FittedBitMapControl(const IRECT& bounds, const IBitmap& bitmap) :
    IBitmapControl(bounds, bitmap) { }
  void Draw(IGraphics& g) override {
    IBlend blend = mControl->GetBlend();
    g.DrawFittedBitmap(mBitmap, mControl->GetRECT(), &blend);
  }
};

// class to draw scaled knob
class FittedBitMapKnob : public IKnobControlBase {
  IBitmap mBitmap;
  IRECT mFraming;
  int mWidth;
  int mHeight;
  int mFrames;
public:
  FittedBitMapKnob(
    const IRECT& bounds, const IBitmap& bitmap,
    const IRECT& framing, int paramIdx,
    double gearing = DEFAULT_GEARING
  ) : IKnobControlBase(bounds, paramIdx, EDirection::Vertical, gearing) {
    mBitmap = bitmap;
    mFraming = framing;

    mWidth = floor(bitmap.H() / double(framing.H()));
    mHeight = floor(bitmap.W() / double(framing.W()));
    mFrames = mWidth * mHeight;
  }

  virtual ~FittedBitMapKnob() { }

  void Draw(IGraphics& g) override {
    int x = 0;
    int y = 0;
    if (mFrames > 1) {
      int i = 0;
      i = int(0.5 + GetValue() * double(mFrames));
      i = Clip(i, 0, mFrames - 1);
      x = i % mWidth;
      y = (i - x) / mHeight;
    }
    IBlend blend = GetBlend();
    IRECT bounds = GetRECT();

    g.PathTransformSave();
    g.PathTransformTranslate(bounds.L, bounds.T);
    IRECT newBounds(
      0., 0.,
      float(mFraming.W()),
      float(mFraming.H())
    );
    g.PathTransformScale(
      bounds.W() / float(mFraming.W()),
      bounds.H() / float(mFraming.H())
    );
    g.DrawBitmap(
      mBitmap,
      newBounds,
      0 + mFraming.L + mFraming.W() * x,
      0 + mFraming.T + mFraming.H() * y,
      &blend
    );
    g.PathTransformRestore();
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
  void OnReset() override;
  void OnActivate(bool active) override;
private:
  guitard::GuitarDHeadless mGuitard;
#endif
};
