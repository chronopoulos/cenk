#ifndef SESSION_H
#define SESSION_H

#include <jack/jack.h>

#define NSYNTHS_MAX 16

struct synth_data {

    void *data;
    void (*process) (void*, void*);
    jack_default_audio_sample_t* (*get_buffer) (void*);

};

struct session_data {

    jack_nframes_t sr; // sample rate
    jack_nframes_t bs; // buffer size

    jack_port_t *inport;
    jack_port_t *outport;

    struct synth_data synths[NSYNTHS_MAX];
    size_t nsynths;

};

void session_init(struct session_data*, jack_client_t*);
void session_add_synth(struct session_data*, struct synth_data*);

#endif
