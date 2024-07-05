#define PLUG_NAME "rektifier"
#define PLUG_MFR "classified audio"
#define PLUG_VERSION_HEX 0x00010000
#define PLUG_VERSION_STR "1.0.0"
#define PLUG_UNIQUE_ID 'Rctf'
#define PLUG_MFR_ID 'XXXX'
#define PLUG_URL_STR "https://github.com/TobiasKozel"
#define PLUG_EMAIL_STR "classifiedaudio@pm.me"
#define PLUG_COPYRIGHT_STR "Copyright 2021 Tobias Kozel"
#define PLUG_CLASS_NAME rektifier
#define PLUG_HOST_RESIZE 0

#define BUNDLE_NAME "rektifier"
#define BUNDLE_MFR "classified audio"
#define BUNDLE_DOMAIN "com"

#define PLUG_CHANNEL_IO "1-1 2-2"
#define SHARED_RESOURCES_SUBPATH "rektifier"

#define PLUG_LATENCY 0
#define PLUG_TYPE 0
#define PLUG_DOES_MIDI_IN 0
#define PLUG_DOES_MIDI_OUT 0
#define PLUG_DOES_MPE 0
#define PLUG_DOES_STATE_CHUNKS 0
#define PLUG_HAS_UI 1
#define PLUG_WIDTH 692
#define PLUG_HEIGHT 376
#define PLUG_FPS 60
#define PLUG_SHARED_RESOURCES 0
#define SAMPLE_TYPE_FLOAT

#define AUV2_ENTRY rektifier_Entry
#define AUV2_ENTRY_STR "rektifier_Entry"
#define AUV2_FACTORY rektifier_Factory
#define AUV2_VIEW_CLASS rektifier_View
#define AUV2_VIEW_CLASS_STR "rektifier_View"

#define AAX_TYPE_IDS 'RCTF'
#define AAX_TYPE_IDS_AUDIOSUITE 'EFA1', 'EFA2'
#define AAX_PLUG_MFR_STR "Xxxx"
#define AAX_PLUG_NAME_STR "rektifier\n'"
#define AAX_PLUG_CATEGORY_STR "Effect"
#define AAX_DOES_AUDIOSUITE 1

#define VST3_SUBCATEGORY "Fx"

#define CLAP_MANUAL_URL "https://iplug2.github.io/manuals/example_manual.pdf"
#define CLAP_SUPPORT_URL "https://github.com/iPlug2/iPlug2/wiki"
#define CLAP_DESCRIPTION "A simple distortion effect."
#define CLAP_FEATURES "audio-effect"//, "utility"

#define APP_NUM_CHANNELS 2
#define APP_N_VECTOR_WAIT 0
#define APP_MULT 1
#define APP_COPY_AUV3 0
#define APP_SIGNAL_VECTOR_SIZE 64

#define ROBOTO_FN "Roboto-Regular.ttf"

#define PNGKNOB_FN "knob.png"
#define PNGSWITCH_FN "switch.png"
#define PNGBG_FN "bg.png"
