#pragma once

#include "IControls.h"
#include "IPlugLogger.h"

using IBitmapControl = iplug::igraphics::IBitmapControl;
using IRECT = iplug::igraphics::IRECT;
using IBitmap = iplug::igraphics::IBitmap;
using IGraphics = iplug::igraphics::IGraphics;
using IBlend = iplug::igraphics::IBlend;
using IKnobControlBase = iplug::igraphics::IKnobControlBase;
using EDirection = iplug::igraphics::EDirection;

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
    double gearing = 4.0
  ) : IKnobControlBase(bounds, paramIdx, EDirection::Vertical, gearing) {
    mBitmap = bitmap;
    mFraming = framing;

    mHeight = floor(bitmap.H() / double(framing.H()));
    mWidth = floor(bitmap.W() / double(framing.W()));
    mFrames = mWidth * mHeight;
  }

  virtual ~FittedBitMapKnob() { }

  void Draw(IGraphics& g) override {
    int x = 0;
    int y = 0;
    int i = 0;

    const double val = GetValue();
    i = int(val * double(mFrames - 1));
    x = i % mWidth;
    y = (i - x) / mHeight;

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

class FittedBitMapSwitch : public FittedBitMapKnob {
public:
  FittedBitMapSwitch(
    const IRECT& bounds, const IBitmap& bitmap,
    const IRECT& framing, int paramIdx
  ) : FittedBitMapKnob(bounds, bitmap, framing, paramIdx) {

  }

  void OnMouseDown(float x, float y, const IMouseMod& mod) override {
    double val = GetValue();
    if (val < 0.3) {
      SetValue(0.5);
      DBGMSG("0.5");
    } else if (val < 0.6) {
      SetValue(1.0);
      DBGMSG("1.0");

    } else {
      SetValue(0.0);
      DBGMSG("0.0");
    }

    mMouseDown = true;
    SetDirty(true);
  }

  void OnMouseUp(float x, float y, const IMouseMod& mod) override {
    mMouseDown = false;
    SetDirty(true);
  }
  void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod& mod) override { }
  void OnMouseWheel(float x, float y, const IMouseMod& mod, float d) override { }
  
};