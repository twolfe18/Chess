
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

void apply_move(Board *board, Move *move) {
	int moving, capt, playing;
	playing = to_play(board);
	moving = moving_type(move);
	capt = capturing_type(move);
	
	/* TODO: handle castling, en pessant, etc */
	
	/* remove the source piece */
	place_piece(board, playing, NA, move->from);
	
	/* remove piece being attacked (if any) */
	if(capt != NA) {
		place_piece(board, 1-playing, NA, move->to);
	}
	
	/* place the attacking piece on destination */
	place_piece(board, playing, moving, move->to);
	
	/* flip the piece to play */
	if(to_play(board) == WHITE)
		set_play(board, BLACK);
	else set_play(board, WHITE);
	
}
