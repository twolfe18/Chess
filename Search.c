/* Travis Wolfe
 * January 2010
 */

#include "Search.h"

#define QDEPTH 4

int scout(Board *board, int alpha, int beta, int depth) {
	
	Move *moves;
	int num_moves, i, val;
	
	/* printf("scout depth %d\n", depth); */
	
	if(depth == 0)
		return quiescent(board, alpha, beta, QDEPTH);
		
	/* loop over all moves */
	moves = gen_moves(board, &num_moves);
	for(i=0; i<num_moves; i++) {

		/* apply the move */
		apply_move(board, &moves[i]);
		
		/* recurse */
		val = -scout(board, -beta, -alpha, depth-1);
		
		/* undo move */
		undo_move(board, &moves[i]);
		
		/* update alpha */
		if(val > alpha)
			alpha = val;
		if(alpha >= beta)
			return alpha;
	}
	/* free(moves); */
	
	return alpha;
}

int quiescent(Board *board, int alpha, int beta, int depth) {
	
	return eval(board);
}