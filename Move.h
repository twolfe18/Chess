/* Travis Wolfe
 * December 2009
 */

#include <stdlib.h>

/* Move needs to store from, to, capture type, promote type
 * should have a bunch of methods associted with it
 */
typedef struct {
	unsigned char from;
	unsigned char to;
	unsigned char moving_capturing;
} Move;

/* returns the moving piece type (as defined in Board.h) */
unsigned char moving_type(Move *m);

/* returns the capturing piece type (as defined in Board.h)
 * can be an empty square (will decide on how to indicate this later)
 */
unsigned char capturing_type(Move *m);

/* this function make a new move */
Move* move(int from, int to, int moving, int caputuring);