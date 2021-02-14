#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <jack/midiport.h>

#include "sinus.h"

float mtof(int m) {

    // MIDI note to frequency (in Hz)
    return 440. * pow(2, (m-69)/12.);

}

void sinus_init(struct sinus_data *data, jack_nframes_t sr, jack_nframes_t bs, uint8_t channel) {

    data->sr = sr;
    data->bs = bs;

    data->chan = channel;

    data->phasor = 0.0;
    data->freq= 220.0;
    data->ampl = 0.;

    data->buf = (jack_default_audio_sample_t*) malloc(data->bs * sizeof(jack_default_audio_sample_t));

}

void sinus_process(void *data_vp, void *midibuf) {

    struct sinus_data *data = (struct sinus_data*) data_vp;

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

    for (size_t i=0; i<data->bs; i++) {

        // amplitude decay
        data->ampl /= 1.0001;

        // MIDI state machine
        // this needs to be a while loop to handle cases where there are
        // multiple midi events with the same timestep
        while (mev_loaded && (i == mev.time)) {

            // if note-on, maximize amplitude, and set frequency
            if ( ((mev.buffer[0] & 0xf0) == 0x90)
                    && ((mev.buffer[0] & 0x0f) == data->chan - 1)) {
                data->ampl = 0.5;
                data->freq = mtof(mev.buffer[1]);
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
        data->phasor += data->freq / data->sr;
        if (data->phasor > 1.0) data->phasor = 0.;
		data->buf[i] = data->ampl * sin(2*M_PI * data->phasor);

    }

}

jack_default_audio_sample_t *sinus_get_buffer(void *data_vp) {

    return ((struct sinus_data*) data_vp)->buf;

}

