#include <jack/midiport.h>
#include <math.h>

#include "KickSynth.h"

float mtof(int m) {

    // MIDI note to frequency (in Hz)
    return 440. * pow(2, (m-69)/12.);

}

KickSynth::KickSynth(uint8_t channel) : Synth(channel) {

    phasor = 0.0;
    freq= 110.0;
    ampl = 0.;

}

jack_default_audio_sample_t* KickSynth::process(jack_nframes_t nframes, void *midibuf) {

    // midi state machine init

    jack_midi_event_t mev;  // mev = midi event
    size_t mev_index = 0;
    jack_nframes_t mev_avail = jack_midi_get_event_count(midibuf);
    bool mev_loaded = false;

    if (mev_index < mev_avail) {
        jack_midi_event_get(&mev, midibuf, mev_index++);
        mev_loaded = true;
    }

    // processing loop

    for (size_t i=0; i<nframes; i++) {

        // amplitude decay
        ampl /= 1.0001;
        freq /= 1.0001;

        // MIDI state machine
        // this needs to be a while loop to handle cases where there are
        // multiple midi events with the same timestep
        while (mev_loaded && (i == mev.time)) {

            // if note-on, maximize amplitude, and set frequency
            if ( ((mev.buffer[0] & 0xf0) == 0x90)
                    && ((mev.buffer[0] & 0x0f) == chan - 1)) {
                ampl = 0.5;
                freq = mtof(mev.buffer[1] - 24);
            }

            // advance to next midi event
            if (mev_index < mev_avail) {
                jack_midi_event_get(&mev, midibuf, mev_index++);
                mev_loaded = true;
            } else {
                mev_loaded = false;
            }

        }

        // audio rate stuff
        phasor += freq / sr;
        if (phasor > 1.0) phasor = 0.;
		buf[i] = vol * ampl * sin(2*M_PI * phasor);

    }

    return buf;

}

