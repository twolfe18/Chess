/* Travis Wolfe
 * December 2009
 */

#include <stdlib.h>
#include "Types.h"

/* returns the moving piece type (as defined in Board.h) */
unsigned char moving_type(Move m);

/* returns the capturing piece type (as defined in Board.h)
 * can be an empty square (will decide on how to indicate this later)
 */
unsigned char capturing_type(Move m);

/* this function make a new move */
void move_set(Move *move, int from, int to, int moving, int caputuring);

/* applies a move to a board */
void apply_move(Board *board, Move move);

/* un-does a move */
void undo_move(Board *board, Move move);