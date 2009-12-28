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

/* this is the struct that contains all
 * information needed to specify a board
 */
typedef struct {
	
	/* Note about "register"
	 * I tried some simple tests using
	 * register, it does not seem to
	 * help (it actually hurts a lot)
	 * Try adding this later if you
	 * think it can help.
	 */
	
	/* a length 12 array of longs
	 * each long is 64 bits for the board
	 * 
	 * board positions are indexed by rank
	 * from A1 (0), A2 (1), ..., to H8 (63)
	 */
	long rank_positions[12];
	
	/* same as above but positions are
	 * indexed by file from A1 (0),
	 * B1 (2), ..., H8 (63)
	 */
	long file_positions[12];
	
	/* this array is a diagnolized board
	 * where the numbering goes like:
	 * A8 (0), A7 (1), B8 (2), A6 (3),
	 * ..., B1 (63)
	 */
	long tl_br_positions[12];

	/* this array is a diagnolized board
	 * where the numbering goes like:
	 * A1 (0), A2 (1), B1 (2), A3 (3),
	 * ..., B8 (63)
	 */
	long bl_tr_positions[12];
	
	/* highest order bit is either WHITE or
	 BLACK, lowest 2 bytes are the ply */
	int ply_and_play;
	
} Board;

/* initialize a board from a FEN notation string */
void initf(Board *board, char *fen);

/* print the board */
void printb(Board *board);

/* initializes the board to a typical starting arrangement */
void setup(Board *board);

/* gets rid of any dynamically allocated memory
 * (currently doesn't do anything)
 */
void dispose(Board *board);

/* returns either WHITE or BLACK, player to play */
int to_play(Board *board);

/* set the turn of who is to play */
void set_play(Board *board, int color);

/* returns the ply of the game (note: this is not the fullmove number) */
int ply(Board *board);

/* sets the ply of the game (note: this is not the fullmove number) */
void set_ply(Board *board, int ply);

/* this function returns an array where the index
 * is based on the position of a pawn, and the resulting
 * long is all 0's except for where the pawn can move
 *
 * access the appropriate map with
 * pawn_attacks[color*64 + sq]
 */
long* pawn_attacks();

/* this function returns an array of masks that have
 * to do with file attacks. you get the correct mask
 * by giving it:
 *
 * array[sq*256 + file_occupancy]
 * 
 * where file occupancy is an int where there are 1's
 * present only in the ranks which are filled by
 * either team in the file of sq.
 *
 * you measure file_occupancy from white's perspective,
 * so A4 would register as a 1 in the 3rd place, and
 * C5 would register in the 4th place
 */
long* make_file_attacks();

/* very similar to make_file_attacks, only
 * you give it an index based on the rank
 *
 * array[sq*256 + rank_occupancy]
 *
 * rank is measured from the left
 * a piece at A4 would register as a one in the
 * 0th place, C5 would register in the 2nd place
 */
long* make_rank_attacks();

/* this function returns an array of possible moves
 * the number of moves returned will be stored in num_moves
 */
Move* get_moves(Board *board, int *num_moves);

