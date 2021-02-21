#ifndef SYNTH_H
#define SYNTH_H

#include <jack/jack.h>
#include <jack/ringbuffer.h>

class Synth {

    public:

        Synth(uint8_t);
        void setAudioParams(jack_nframes_t, jack_nframes_t);

        void handleCtrlMsgs(void);
        virtual jack_default_audio_sample_t* process(jack_nframes_t, void*) {return NULL;}

        void setVolume(float);

    protected:

        jack_nframes_t sr;
        jack_nframes_t bs;
        jack_default_audio_sample_t *buf;

        jack_ringbuffer_t *rb;

        uint8_t chan;   // midi channel [1,16]
        float vol;      // volume [0,1]


};

#endif
