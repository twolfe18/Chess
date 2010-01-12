/* Travis Wolfe
 * December 2009
 */

#include <stdio.h>
#include <stdlib.h>
#include "Types.h"

/* initialize a board from a FEN notation string */
void initf(Board *board, char *fen);

/* print the board */
void printb(Board *board);

/* initializes the board to a typical starting arrangement */
void setup(Board *board);

/* returns either WHITE or BLACK, player to play */
int to_play(Board *board);

/* set the turn of who is to play */
void set_play(Board *board, int color);

/* returns the ply of the game (note: this is not the fullmove number) */
int ply(Board *board);

/* sets the ply of the game (note: this is not the fullmove number) */
void set_ply(Board *board, int ply);

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
unsigned long* make_file_attacks(void);

/* very similar to make_file_attacks, only
 * you give it an index based on the rank
 *
 * array[sq*256 + rank_occupancy]
 *
 * rank is measured from the left
 * a piece at A4 would register as a one in the
 * 0th place, C5 would register in the 2nd place
 */
unsigned long* make_rank_attacks(void);

/* makes an array for top-left to bottom-right sliding
 * pieces. squares are indexed as defined in Board.h
 *
 * array[sq*256 + diagnol_occupancy]
 */
unsigned long* make_tl_br_attacks(void);

/* makes an array for bottom-left to top-right sliding
 * pieces. squares are indexed as defined in Board.h
 *
 * array[sq*256 + diagnol_occupancy]
 */
unsigned long* make_bl_tr_attacks(void);

/* makes an array for attacking knights
 * access it via the square you have a knight at:
 *
 * array[sq]
 */
unsigned long* make_knight_attacks(void);

/* makes an array for king attacks
 */
unsigned long* make_king_attacks(void);

/* this function returns an array of moves to try in search
 * it stores the number of moves generated in *number
 */
Move* gen_moves(Board *board, int *number);

/* places a piece on the board 
 * rf_sq is the square in rank*8+file coordinates
 * if you pass NA as the type, this function will just
 * clear rf_sq of any pieces
 */
void place_piece(Board *board, int color, int type, int rf_sq);

/* this basically makes all of the move masks */
void get_ready(void);

/* this basically frees all of the move masks */
void clean_up(void);

