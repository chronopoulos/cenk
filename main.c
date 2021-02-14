// Chris Chronopoulos 20210213

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include <jack/jack.h>
#include <jack/midiport.h>

float FREQ = 220.;

struct synth_data {
    jack_nframes_t sr; // sample rate
    jack_nframes_t bs; // buffer size
    jack_port_t *inport;
    jack_port_t *outport;
    float phasor;
    float freq;
    float ampl;
};

void synth_data_init(struct synth_data *data) {

    data->sr = 0;
    data->bs = 0;
    data->inport = NULL;
    data->outport = NULL;
    data->phasor = 0.0;
    data->freq= 440.0;
    data->ampl = 0.;

}

float mtof(int m) {

    // MIDI note to frequency (in Hz)
    return 440. * pow(2, (m-69)/12.);

}

static int process(jack_nframes_t nframes, void *arg) {

    struct synth_data *data = arg;

    void *inbuf = jack_port_get_buffer(data->inport, nframes);
    jack_default_audio_sample_t *outbuf =
        (jack_default_audio_sample_t *) jack_port_get_buffer(data->outport, nframes);

    //

    jack_midi_event_t mev;
    size_t mev_index = 0;
    jack_nframes_t mev_avail = jack_midi_get_event_count(inbuf);
    bool mev_loaded = false;

    if (mev_index < mev_avail) {
        jack_midi_event_get(&mev, inbuf, mev_index++);
        mev_loaded = true;
    }

    //

    for(int i=0; i<nframes; i++) {

        data->ampl /= 1.0001;
        if (mev_loaded && (i == mev.time)) {

            // if note-on, maximize amplitude
            if ((mev.buffer[0] & 0xf0) == 0x90) {
                data->ampl = 1.;
                data->freq = mtof(mev.buffer[1]);
            }

            // advance to next midi event (mev)
            if (mev_index < mev_avail) {
                jack_midi_event_get(&mev, inbuf, mev_index++);
                mev_loaded = true;
            } else {
                mev_loaded = false;
            }

        }

        data->phasor += data->freq / data->sr;
        if (data->phasor > 1.0) data->phasor = 0.;

		outbuf[i] = data->ampl * sin(2*M_PI * data->phasor);
    }

    return 0;

}

int main(void) {

    jack_client_t *jack_client;

    struct synth_data data;
    synth_data_init(&data);

    // open jack client
    jack_client = jack_client_open("cenk", JackNoStartServer, NULL);
	if (jack_client == NULL) {
        fprintf(stderr, "failed to open JACK client\n");
        exit(1);
	}

    // get jack server parameters
    data.sr = jack_get_sample_rate(jack_client);
    data.bs = jack_get_buffer_size(jack_client);

    // create the ports
    data.inport = jack_port_register(jack_client, "midi-in", JACK_DEFAULT_MIDI_TYPE,
                                        JackPortIsInput, 0);
    data.outport = jack_port_register(jack_client, "audio_out", JACK_DEFAULT_AUDIO_TYPE,
                                        JackPortIsOutput, 0);

    // set jack process callback
	jack_set_process_callback(jack_client, process, &data);

    // start jack thread
    if (jack_activate(jack_client)) {
        fprintf(stderr, "cannot activate client");
        exit(1);
    }

    // sleep forever
    while(1) {
        sleep(1);
    }

    jack_client_close(jack_client);
    exit(0);

}

