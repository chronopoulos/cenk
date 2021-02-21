#ifndef HATSYNTH_H
#define HATSYNTH_H

#include "Synth.h"

class HatSynth : public Synth {

    public:

        HatSynth(uint8_t);
        jack_default_audio_sample_t* process(jack_nframes_t, void*);

    private:

        float ampl;

};

#endif
