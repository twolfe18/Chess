/* Travis Wolfe
 * December 2009
 */

#include <stdlib.h>

/* Move needs to store from, to, capture type, promote type
 * should have a bunch of methods associted with it
 */
typedef struct {
	int idkfornow;
} Move;

/* returns the moving piece type (as defined in Board.h) */
int moving_type();

/* returns the capturing piece type (as defined in Board.h)
 * can be an empty square (will decide on how to indicate this later)
 */
int capturing_type();

/* returns the square that the piece is moving from */
int from();

/* returns the square that the piece is moving to */
int to();

