#ifndef SYNTH_H
#define SYNTH_H

#include <jack/jack.h>

class Synth {

    public:

        Synth(uint8_t);
        void setAudioParams(jack_nframes_t, jack_nframes_t);

        virtual jack_default_audio_sample_t* process(jack_nframes_t, void*) {return NULL;}

    protected:

        jack_nframes_t sr;
        jack_nframes_t bs;
        jack_default_audio_sample_t *buf;

        uint8_t chan;   // midi channel (1-indexed)


};

#endif
