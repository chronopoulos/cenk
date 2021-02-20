#include <cstdlib>

#include "Synth.h"

Synth::Synth(uint8_t channel) {

    chan = channel;

}

void Synth::setAudioParams(jack_nframes_t sr, jack_nframes_t bs) {

    this->sr = sr;
    this->bs = bs;

    this->buf = (jack_default_audio_sample_t*) malloc(this->bs * sizeof(jack_default_audio_sample_t));

}

