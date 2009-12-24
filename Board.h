/* Travis Wolfe
 * December 2009
 */

#include <stdio.h>
#include <stdlib.h>

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

void printb(Board *board);
void init(Board *board);
void dispose(Board *board);
int to_play(Board *board);
void set_play(Board *board, int color);
int ply(Board *board);
void set_ply(Board *board, int ply);

long* pawn_attacks();

