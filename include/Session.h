#ifndef SESSION_H
#define SESSION_H

#include <jack/jack.h>

#include "Synth.h"

#define NSYNTHS_MAX 16

class Session {

    public:

        Session(void);
        void addSynth(Synth*);
        void start(void);
        void process(jack_nframes_t);

    private:

        jack_client_t *jack_client;

        jack_nframes_t sr; // sample rate
        jack_nframes_t bs; // buffer size

        jack_port_t *inport;
        jack_port_t *outport;

        //struct synth_data synths[NSYNTHS_MAX];
        Synth* synths[NSYNTHS_MAX];
        size_t nsynths;

};

#endif
