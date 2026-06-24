cmake_minimum_required(VERSION 3.10)

# Definitions
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#project(cmake_c_template)
project(dzsungel VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Assign the include directories
include_directories(${PROJECT_SOURCE_DIR}/include/dzsungel)
add_subdirectory(libs)
option(EXPONENTIAL_ADSR "Use exponential/log adsr calculations" ON)

set(COMMON_SOURCES src/dsp/adsr.c src/dsp/oscillator.c
        src/synth/Voices.cpp
        src/synth/VoiceManager.cpp
        src/dsp/wavetablegen.c
        src/synth/MidiPreprocessor.cpp
        include/dzsungel/types.hpp
        src/data/Programs.cpp
)

set(MAX_VOICES 32 CACHE STRING "Max voice polyphony")

set(MAIN_FILE src/new-main.cpp)
add_executable(dzsungel ${COMMON_SOURCES} ${MAIN_FILE} ${MIDIFILE_SOURCES})
target_link_libraries(dzsungel PRIVATE m midifile dr_wav)
if(EXPONENTIAL_ADSR)
    target_compile_definitions(dzsungel PRIVATE EXPONENTIAL_ADSR)
endif ()
target_compile_definitions(
    dzsungel
    PRIVATE MAX_VOICES=${MAX_VOICES}
)
