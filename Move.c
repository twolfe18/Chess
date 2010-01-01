
#include "Move.h"

unsigned char moving_type(Move *m) {
	return (unsigned char) (m->moving_capturing >> 4) & 7;
}

unsigned char capturing_type(Move *m) {
	return (unsigned char) m->moving_capturing & 7;
}

Move* move(int from, int to, int moving, int caputuring) {
	Move *r = (Move*) malloc(sizeof(Move));
	r->from = (char) from;
	r->to = (char) to;
	r->moving_capturing = (((char) moving) << 4) + ((char) capturing);
	return r;
}

