#include <cstdlib>
#include <QDebug>

#include "Synth.h"

#define SYNTH_RB_LENGTH 16

enum synth_param {SYNTH_VOLUME};

typedef struct {

    enum synth_param param;

    // parameter-dependent value fields
    int vi;
    float vf;
    bool vb;
    void *vp;

} synth_ctrl_msg_t ;

Synth::Synth(uint8_t channel) {

    chan = channel;

    vol = 1.;

    // allocate and lock ringbuffer
    rb = jack_ringbuffer_create(SYNTH_RB_LENGTH * sizeof(synth_ctrl_msg_t));
    int err = jack_ringbuffer_mlock(rb);
    if (err) {
        qDebug() << "failed to lock ringbuffer";
        exit(1);
    }

}

void Synth::setAudioParams(jack_nframes_t sr, jack_nframes_t bs) {

    this->sr = sr;
    this->bs = bs;

    this->buf = (jack_default_audio_sample_t*) malloc(this->bs * sizeof(jack_default_audio_sample_t));

}

void Synth::setVolume(float volume) {

    synth_ctrl_msg_t msg;
    long unsigned int avail;

    avail = jack_ringbuffer_write_space(rb);
    if (avail < sizeof(synth_ctrl_msg_t)) {
        qDebug() << "synth ringbuffer: overflow";
        return;
    }

    msg.param = SYNTH_VOLUME;
    msg.vf = volume;

    jack_ringbuffer_write(rb, (const char*) &msg, sizeof(synth_ctrl_msg_t));

}

void Synth::handleCtrlMsgs(void) {

    synth_ctrl_msg_t msg;
    long unsigned int avail;

    avail = jack_ringbuffer_read_space(rb);
    while(avail >= sizeof(synth_ctrl_msg_t)) {

        jack_ringbuffer_read(rb, (char*) &msg, sizeof(synth_ctrl_msg_t));

        if (msg.param == SYNTH_VOLUME) {
            vol = msg.vf;
        }

        avail -= sizeof(synth_ctrl_msg_t);

    }

}

