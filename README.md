# dzsungel-fm
Dzsungel (Hungarian for "jungle") is a phase modulation-based software synth designed to emulate the sound of 80's New Wave music, particularly [Spandau Ballet](https://en.wikipedia.org/wiki/Spandau_Ballet) and the Hungarian synth pop band [Bonanza Banzai](https://en.wikipedia.org/wiki/Bonanza_Banzai), the latter of which inspired the name. It is written mostly in C++ with a bit of C.

# Features
- Partial MIDI support (currently just note on / note off, pitch bending, some CC support. Support for more MIDI features coming soon)
- Block-based: Samples are calculated in blocks of 64 to improve cache performance
- Smart voice management: MIDI preprocessor with advanced bookkeeping. Number of voices is customizable using the `MAX_VOICES` CMake flag. 
    - Notes are automatically assigned to voices within a channel, and if none are free, a new voice is added to that channel or the closest-to-finishing voice is stolen.
- Oscillators: Standard 2-Op PM synthesis and feedback modes
- Outputs in standard WAV files
# Installation
```bash
cmake -B build
cmake --build build
```
Your executable will be in the `bin` folder. 
## Usage
```bash
./bin/dzsungel [input midi file] [output wav file (optional)]
```
For example:
```bash
./bin/dzsungel "Bonanza Banzai - Induljon a banzai.mid" magyar.wav
```
If you do not type in an output file name, it will automatically be written to `out.wav`
