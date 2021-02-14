#ifndef BONG_H
#define BONG_H

#include <stdint.h>

#include <jack/jack.h>

struct bong_data {

    jack_nframes_t sr;
    jack_nframes_t bs;

    uint8_t chan;   // midi channel (1-indexed)

    float phasor;
    float freq;
    float ampl;

    jack_default_audio_sample_t *buf;

};

void bong_init(struct bong_data*, jack_nframes_t, jack_nframes_t, uint8_t);
void bong_process(void*, void*);
jack_default_audio_sample_t *bong_get_buffer(void*);

#endif
