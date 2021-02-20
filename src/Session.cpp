#include <QDebug>

#include "Session.h"

static int _process(jack_nframes_t nframes, void *arg) {

    Session *session;
    session = (Session *) arg;

    session->process(nframes);

    /*

    void *inbuf;
    jack_default_audio_sample_t *outbuf;

    // get the session data

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

    */

    return 0;

}

Session::Session(void) {

    // open jack client
    jack_client = jack_client_open("trox", JackNoStartServer, NULL);

	if (jack_client == NULL) {
        qDebug() << "failed to open JACK client";
        exit(1);
	}

    // set jack process callback
	jack_set_process_callback(jack_client, _process, this);

    ////

    sr = jack_get_sample_rate(jack_client);
    bs = jack_get_buffer_size(jack_client);

    inport = jack_port_register(jack_client, "midi-in", JACK_DEFAULT_MIDI_TYPE,
                                  JackPortIsInput, 0);
    outport = jack_port_register(jack_client, "audio_out", JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsOutput, 0);

    nsynths = 0;

}

void Session::process(jack_nframes_t nframes) {

    void *inbuf;
    jack_default_audio_sample_t *outbuf;

    // get buffers
    inbuf = jack_port_get_buffer(inport, nframes);
    outbuf = (jack_default_audio_sample_t *) jack_port_get_buffer(outport, nframes);

    // first, clear outbuf (necessary to prevent noisy AM)
    for(jack_nframes_t j=0; j<nframes; j++) {
        outbuf[j] = 0.;
    }

    // then, iterate through the synths, adding their contributions to the outbuf
    jack_default_audio_sample_t *buf;   // tmp variable
    for (size_t i=0; i<nsynths; i++) {
        buf = synths[i]->process(nframes, inbuf);
        for(jack_nframes_t j=0; j<nframes; j++) {
            outbuf[j] += buf[j];
        }
    }

}


void Session::addSynth(Synth *synth) {

    synth->setAudioParams(sr, bs);
    synths[nsynths++] = synth;

}

void Session::start(void) {

    if (jack_activate(jack_client)) {
        qDebug() << "cannot activate client";
        exit(1);
    }

}

