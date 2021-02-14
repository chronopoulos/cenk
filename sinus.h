#ifndef SINUS_H
#define SINUS_H

#include <jack/jack.h>

struct sinus_data {

    jack_nframes_t sr;
    jack_nframes_t bs;

    float phasor;
    float freq;
    float ampl;

    jack_default_audio_sample_t *buf;

};

void sinus_init(struct sinus_data*, jack_nframes_t, jack_nframes_t);
void sinus_process(void*, void*);
jack_default_audio_sample_t *sinus_get_buffer(void*);

#endif
