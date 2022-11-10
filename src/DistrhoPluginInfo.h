#ifndef _PLUGIN_INFO
#define _PLUGIN_INFO

#define DISTRHO_PLUGIN_LICENSE            "WTFPL"
#define DISTRHO_PLUGIN_NAME               "rektifier"
#define DISTRHO_PLUGIN_BRAND              "Classified Audio"

#define DISTRHO_PLUGIN_NUM_INPUTS         2
#define DISTRHO_PLUGIN_NUM_OUTPUTS        2

#define DISTRHO_PLUGIN_HAS_UI             1
#define DISTRHO_PLUGIN_IS_RT_SAFE         1 // should be
#define DISTRHO_PLUGIN_IS_SYNTH           0 // nope
#define DISTRHO_PLUGIN_WANT_MIDI_INPUT    0 // just doing dsp
#define DISTRHO_PLUGIN_WANT_MIDI_OUTPUT   0 // just doing dsp
#define DISTRHO_PLUGIN_WANT_PROGRAMS      0 // nope
#define DISTRHO_PLUGIN_WANT_STATE         0 // all state is represented by the params
#define DISTRHO_PLUGIN_WANT_FULL_STATE    0 // see above
#define DISTRHO_PLUGIN_WANT_DIRECT_ACCESS 0 // not needed since the parameters can be used for ui dsp communication
#define DISTRHO_PLUGIN_WANT_LATENCY       0 // TODO IR actually causes latency see Plugin::setLatency(uint32_t)
#define DISTRHO_PLUGIN_WANT_TIMEPOS       0 // not interested

#define DISTRHO_UI_DEFAULT_WIDTH          600 // TODO get the actual dimensions
#define DISTRHO_UI_DEFAULT_HEIGHT         400 // TODO get the actual dimensions

#define DISTRHO_UI_USE_CUSTOM             0 // maybe needed for imgui later
// #define DISTRHO_UI_CUSTOM_INCLUDE_PATH "DearImGui.hpp"
// #define DISTRHO_UI_CUSTOM_WIDGET_TYPE DGL_NAMESPACE::ImGuiTopLevelWidget

#define DISTRHO_UI_USER_RESIZABLE         1 // yes UI::setGeometryConstraints(uint, uint, bool, bool)
#define DISTRHO_UI_USE_NANOVG             0 // hmmm


#define DISTRHO_PLUGIN_URI                "urn:classified:amps:rektifier"
#define DISTRHO_UI_URI                    DISTRHO_PLUGIN_URI "#UI"
#define DISTRHO_PLUGIN_LV2_CATEGORY       "lv2:AmplifierPlugin"
#define DISTRHO_PLUGIN_VST3_CATEGORIES    "Fx|Distortion|Stereo"
#define DISTRHO_PLUGIN_CLAP_FEATURES      "audio-effect", "distortion", "stereo"
#define DISTRHO_PLUGIN_CLAP_ID            "classified.amps.rektifier"


#define DISTRHO_PLUGIN_WANT_PARAMETER_VALUE_CHANGE_REQUEST 0 // Nope

// Non dpf macros
#define DISTRHO_PLUGIN_VERSION_MAJOR      0
#define DISTRHO_PLUGIN_VERSION_MINOR      0
#define DISTRHO_PLUGIN_VERSION_PATCH      1

enum EParams {
    kParamGate = 0,
    kParamGain,
    kParamWidth,
    kParamCab,
    kParamRekt,
    kParamSag,
    kParamInput,
    kNumParams
};

#endif // _PLUGIN_INFO