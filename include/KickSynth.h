#ifndef KICKSYNTH_H
#define KICKSYNTH_H

#include "Synth.h"

class KickSynth : public Synth {

    public:

        KickSynth(uint8_t);
        jack_default_audio_sample_t* process(jack_nframes_t, void*);

    private:

        float phasor;
        float freq;
        float ampl;

};

#endif
