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
  kParamInput,
  kNumParams
};

enum EControlTags
{
  kCtrlTags
};

using namespace iplug;
using namespace igraphics;

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
