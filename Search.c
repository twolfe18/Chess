/* Travis Wolfe
 * January 2010
 */

#include "Search.h"

int scout(Board *board, int alpha, int beta, int depth) {
	
	Move *moves;
	int num_moves, i, val;
	
	if(depth == 0)
		return alpha;
		
	/* loop over all moves */
	moves = gen_moves(board, &num_moves);
	for(i=0; i<num_moves; i++) {
	
		/* apply the move */
		apply_move(board, &moves[i]);
		
		/* recurse */
		val = scout(board, alpha, beta, depth-1);
		
		/* undo move */
		/* DUHHHHHH... */
		
		/* update alpha */
		if(val > beta)
			return beta;
		else if(val > alpha)
			alpha = val;
	}
	
	return alpha;
}

int quiescent(Board *board, int alpha, int beta, int depth) {
	
	return 0;
}