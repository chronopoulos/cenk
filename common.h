#ifndef COMMON_H
#define COMMON_H

#include "session.h"

float mtof(int);

void add_bong_to_session(struct session_data*, uint8_t);
void add_sinus_to_session(struct session_data*, uint8_t);

#endif
