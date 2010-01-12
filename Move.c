
#include "Move.h"
#include <stdio.h>

/* NOTE
 * moves are actually smaller than a 64 bit (8 byte) pointer
 * so it does not make sense to pass by reference, just pass
 * the move itself when possible
 */

unsigned char moving_type(Move m) {
	return (unsigned char) (m.moving_capturing >> 4) & 15;
}

unsigned char capturing_type(Move m) {
	return (unsigned char) m.moving_capturing & 15;
}

void move_set(Move *move, int from, int to, int moving, int capturing) {
	
	/*
	printf("creating move from %d to %d, %d is moving, %d is captured\n",
		from, to, moving, capturing);
	*/
	
	move->from = (char) from;
	move->to = (char) to;
	move->moving_capturing = (((char) moving) << 4) + ((char) capturing);
}

void apply_move(Board *board, Move move) {
	int moving, capt, playing;
	playing = to_play(board);
	moving = moving_type(move);
	capt = capturing_type(move);
	 
	/*
	printf("applying move from %d to %d,\t%d is moving to %d\n",
		move.from, move.to, moving, capt);
	*/
	
	/* TODO: handle castling, en pessant, etc */
	
	/* remove the source piece */
	place_piece(board, playing, NA, move.from);
	
	/* remove piece being attacked (if any) */
	if(capt != NA) {
		place_piece(board, 1-playing, NA, move.to);
	}
	
	/* place the attacking piece on destination */
	place_piece(board, playing, moving, move.to);
	
	/* flip the piece to play */
	if(to_play(board) == WHITE)
		set_play(board, BLACK);
	else set_play(board, WHITE);
	
}

void undo_move(Board *board, Move move) {
	
	int moving, capt, playing;
	playing = to_play(board);
	moving = moving_type(move);
	capt = capturing_type(move);
	
	/* TODO: handle castling, en pessant, etc */
	
	/* remove the attacking piece from dest */
	place_piece(board, 1-playing, NA, move.to);
	
	/* place the attacking piece at source */
	place_piece(board, 1-playing, moving, move.from);
	
	/* replace the captured piece (if any) */
	place_piece(board, playing, capt, move.to);
	
	/* flip the piece to play */
	if(to_play(board) == WHITE)
		set_play(board, BLACK);
	else set_play(board, WHITE);
	
}







