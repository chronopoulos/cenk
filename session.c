#include <string.h>

#include "session.h"

void session_init(struct session_data *data, jack_client_t *client) {

    data->sr = jack_get_sample_rate(client);
    data->bs = jack_get_buffer_size(client);

    data->inport = jack_port_register(client, "midi-in", JACK_DEFAULT_MIDI_TYPE,
                                        JackPortIsInput, 0);
    data->outport = jack_port_register(client, "audio_out", JACK_DEFAULT_AUDIO_TYPE,
                                        JackPortIsOutput, 0);

    data->nsynths = 0;

}

void session_add_synth(struct session_data *data, struct synth_data *synth) {

    memcpy(data->synths + (data->nsynths++), synth, sizeof(struct synth_data));

}

