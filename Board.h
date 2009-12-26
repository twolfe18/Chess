/* Travis Wolfe
 * December 2009
 */

#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

#define WHITE	0
#define BLACK	1

#define KING	0
#define QUEEN	1
#define ROOK	2
#define BISHOP	3
#define KNIGHT	4
#define PAWN	5

#define UP		8
#define DOWN	-8
#define LEFT	-1
#define RIGHT	1

typedef struct {
	
	/* a length 12 array of longs
	 each long is 64 bits for the board */
	volatile long *positions;
	
	/* highest order bit is either WHITE or
	 BLACK, lowest 2 bytes are the ply */
	volatile int ply_and_play;
	
} Board;

void initf(Board *board, char *fen);
void printb(Board *board);
void setup(Board *board);
void dispose(Board *board);
int to_play(Board *board);
void set_play(Board *board, int color);
int ply(Board *board);
void set_ply(Board *board, int ply);

/* this function returns an array where the index
 * is based on the position of a pawn, and the resulting
 * long is all 0's except for where the pawn can move
 *
 * access the appropriate map with
 * pawn_attacks[color*64 + sq]
 */
long* pawn_attacks();

long* make_file_attacks();

/* this function returns an array of possible moves
 * the number of moves returned will be stored in num_moves
 */
Move* get_moves(Board *board, int *num_moves);



