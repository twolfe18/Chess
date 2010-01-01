
#include "Move.h"

unsigned char moving_type(Move *m) {
	return (unsigned char) (m->moving_capturing >> 4) & 7;
}

unsigned char capturing_type(Move *m) {
	return (unsigned char) m->moving_capturing & 7;
}

void move_set(Move *move, int from, int to, int moving, int capturing) {
	move->from = (char) from;
	move->to = (char) to;
	move->moving_capturing = (((char) moving) << 4) + ((char) capturing);
}

