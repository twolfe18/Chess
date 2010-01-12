/* Travis Wolfe
 * January 2010
 */

#include "Search.h"

#define QDEPTH 4

int scout(Board *board, int alpha, int beta, int depth) {
	
	Move *moves;
	int num_moves, i, val;
	
	if(depth == 0)
		return quiescent(board, alpha, beta, QDEPTH);
		
	/* loop over all moves */
	moves = gen_moves(board, &num_moves);
	printf("scout depth %d\t\tgenerated %d moves for\n", depth, num_moves);
	printb(board);
	for(i=0; i<num_moves; i++) {
		
		printf("scout depth %d\tmove %d\n", depth, i);
		printf("moves = %d", moves);
		printf("move = %d", moves[i]);
		printf("from = %d, to = %d\n", moves[i].from, moves[i].to);
	
		/* apply the move */
		apply_move(board, moves[i]);
		
		printb(board);
		
		/* recurse */
		val = -scout(board, -beta, -alpha, depth-1);
		
		printf("recursed\n");
		
		/* undo move */
		undo_move(board, moves[i]);
		
		printf("undid move\n");
		
		/* update alpha */
		if(val > beta)
			return beta;
		else if(val > alpha)
			alpha = val;
	}
	free(moves);
	
	return alpha;
}

int quiescent(Board *board, int alpha, int beta, int depth) {
	
	return eval(board);
}