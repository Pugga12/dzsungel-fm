#include <cstdlib>
#include "synth/VoiceManager.hpp"
#include "synth/MidiPreprocessor.hpp"
#include "Options.h"

extern "C" {
	#include "dsp/wavetablegen.h"
    #include "io/wav.h"
}

int main(int argc, char** argv) {
    smf::Options options;
    options.process(argc, argv);
	float* sinePtr = static_cast<float*>(malloc(sizeof(float) * 4096));
	float* outputPtr = static_cast<float*>(malloc(sizeof(float) * 10584000));
	wavetableGenSine(sinePtr, 4096);

    MidiProcessor mp;
    if (options.getArgCount() == 0) return -3;
    if(!mp.load(options.getArg(1))) {
        return -2;
    }
    mp.convert();

	VoiceManager vm(mp.getEvents(), sinePtr, sinePtr, 44100.0f, 4096);
	if (!vm.go(outputPtr, 10584000)) {
        std::printf("Invalid output size");
        return -1;
    }
    if (options.getArgCount() == 2) {
        auto& filename = options.getArg(2);
        writeWavF32(filename.data(), outputPtr, 10584000, 44100);
    } else {
        char* defaultString = "out.wav";
        writeWavF32(defaultString, outputPtr, 10584000, 44100);
    }


	free(sinePtr);
	free(outputPtr);
	return 0;
}
