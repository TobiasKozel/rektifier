cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)

set(NAME rektifier-plugin)
project(${NAME})

add_subdirectory(dpf)

dpf_add_plugin(${NAME}
  TARGETS clap lv2 vst2 vst3 jack
  FILES_DSP
      src/PluginDSP.cpp
      GuitarD/src/headless/compile_unit/GHeadlessUnit.cpp
  FILES_UI
      src/PluginUI.cpp
      # dpf-widgets/opengl/DearImGui.cpp
)
target_include_directories(${NAME} PUBLIC src)
# target_include_directories(${NAME} PUBLIC dpf-widgets/generic)
# target_include_directories(${NAME} PUBLIC dpf-widgets/opengl)
