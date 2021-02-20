#ifndef SINUS_H
#define SINUS_H

#include <stdint.h>

#include <jack/jack.h>

struct sinus_data {

    jack_nframes_t sr;
    jack_nframes_t bs;

    uint8_t chan;   // midi channel (1-indexed)

    float phasor;
    float freq;
    float ampl;

    jack_default_audio_sample_t *buf;

};

void sinus_init(struct sinus_data*, jack_nframes_t, jack_nframes_t, uint8_t);
void sinus_process(void*, void*);
jack_default_audio_sample_t *sinus_get_buffer(void*);

#endif
