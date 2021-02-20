#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "sinus.h"
#include "bong.h"

float mtof(int m) {

    // MIDI note to frequency (in Hz)
    return 440. * pow(2, (m-69)/12.);

}

void add_sinus_to_session(struct session_data *session, uint8_t channel) {

    // convenience function

    struct sinus_data *sinus;
    struct synth_data synth;

    sinus = malloc(sizeof(struct sinus_data));
    sinus_init(sinus, session->sr, session->bs, channel);

    synth.data = sinus;
    synth.process = sinus_process;
    synth.get_buffer = sinus_get_buffer;

    session_add_synth(session, &synth);

}

void add_bong_to_session(struct session_data *session, uint8_t channel) {

    // convenience function

    struct bong_data *bong;
    struct synth_data synth;

    bong = malloc(sizeof(struct bong_data));
    bong_init(bong, session->sr, session->bs, channel);

    synth.data = bong;
    synth.process = bong_process;
    synth.get_buffer = bong_get_buffer;

    session_add_synth(session, &synth);

}

