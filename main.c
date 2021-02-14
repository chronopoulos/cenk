// Chris Chronopoulos 20210213

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include <jack/midiport.h>

#include "session.h"
#include "sinus.h"

static int process(jack_nframes_t nframes, void *arg) {

    struct session_data *session;
    void *inbuf;
    jack_default_audio_sample_t *outbuf;

    // get the session data
    session = (struct session_data *) arg;

    // get buffers
    inbuf = jack_port_get_buffer(session->inport, nframes);
    outbuf = (jack_default_audio_sample_t *) jack_port_get_buffer(session->outport, nframes);

    // first, clear outbuf (necessary to prevent noisy AM)
    for(int j=0; j<nframes; j++) {
        outbuf[j] = 0.;
    }

    // then, iterate through the synths, adding their contributions to the outbuf
    jack_default_audio_sample_t *buf;   // tmp variable
    for (size_t i=0; i<session->nsynths; i++) {
        session->synths[i].process(session->synths[i].data, inbuf);
        buf = session->synths[i].get_buffer(session->synths[i].data);
        for(int j=0; j<nframes; j++) {
            outbuf[j] += buf[j];
        }
    }


    return 0;

}

int main(void) {

    jack_client_t *jack_client;
    struct session_data session;

    // open jack client
    jack_client = jack_client_open("cenk", JackNoStartServer, NULL);
	if (jack_client == NULL) {
        fprintf(stderr, "failed to open JACK client\n");
        exit(1);
	}

    // initialize the session
    session_init(&session, jack_client);

    // initialize four synths, add them to the session
    struct sinus_data *sinus;
    struct synth_data synth_tmp;
    for (int i=0; i<4; i++) {
        sinus = malloc(sizeof(struct sinus_data));
        sinus_init(sinus, session.sr, session.bs, i+1);
        synth_tmp.data = sinus;
        synth_tmp.process = sinus_process;
        synth_tmp.get_buffer = sinus_get_buffer;
        session_add_synth(&session, &synth_tmp);
    }

    // set jack process callback
	jack_set_process_callback(jack_client, process, &session);

    // start jack thread
    if (jack_activate(jack_client)) {
        fprintf(stderr, "cannot activate client");
        exit(1);
    }

    // sleep forever
    while(1) {
        sleep(1);
    }

    // clean up
    jack_client_close(jack_client);
    exit(0);

}

