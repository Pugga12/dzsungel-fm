//
// Created by adama on 5/7/26.
//
#include <algorithm>
#include <vector>
#include "synth/VoiceManager.hpp"
#include "synth/SynthVoice.hpp"

constinit Program PRG_DEFAULT_BASS {
    0.001,
    1,
    {
        MS_TO_S(10),
        MS_TO_S(400),
        0.5,
        MS_TO_S(100)
    },
    {
        MS_TO_S(2),
        MS_TO_S(50),
        0.1,
        MS_TO_S(100)
    }
};

VoiceManager::VoiceManager(std::vector<TimedEvent> *timedEvents, float* modTable, float* carrierTable, float sr, size_t tableSize) : sr(sr) {
    events.reserve(timedEvents->size());

    for (auto& v : voices) {
        v.init(&PRG_DEFAULT_BASS, modTable, carrierTable, sr, tableSize);
    }

    uint32_t maxBlock = 0;

    for (auto& e : *timedEvents) {
        const uint32_t blockId = e.timecode >> 6;
        const uint8_t offset = e.timecode & 63;

        if (blockId > maxBlock) {
            maxBlock = blockId;
        }

        events.push_back(
            {
                blockId,
                e.voiceId,
                e.type,
                offset,
                e.value
            }
        );
    }

    std::stable_sort(events.begin(), events.end(), [](const VoiceEvent& a, const VoiceEvent& b) {
        return a.blockId < b.blockId;
    });

    this->maxBlock = maxBlock;
}

bool VoiceManager::go(float* outputBuffer, size_t outputSize) {
    float blocksFractional = outputSize / 64.0f;

    if (maxBlock > blocksFractional) {
        return false;
    }

    uint32_t fullBlocks = outputSize / 64;
    uint8_t remBlockSize = outputSize % 64; 
    uint64_t currentEvent = 0;
    uint32_t currentBlock = 0;

    for (uint32_t i = 0; i < fullBlocks; i++) {
        float* bSt = outputBuffer + (64 * i); 

        while (currentEvent < events.size() && events[i].blockId == currentBlock) {
            VoiceEvent& ev = events[i];
            if (ev.voiceId < voices.size()) {
                voices[ev.voiceId].pushEv(ev);
            } 
        }

    for (auto& v : voices) {
            if (v.getState() != VOICE_IDLE) {
                 v.processBlock(bSt, 64);
            }
        }
    }

    return true;
}
