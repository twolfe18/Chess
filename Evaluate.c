
#include "Evaluate.h"

#define PAWN_VAL 100
#define KNIGHT_VAL 310
#define BISHOP_VAL 310
#define ROOK_VAL 500
#define QUEEN_VAL 900
#define KING_VAL 5000

int eval(Board *board) {
	
	printf("evaluating\n");

	unsigned long mask;
	int val, pos;
	
	/* i am going to make this value from
	 * WHITE's perspective
	 */
	
	val = 0;
	mask = board->rank_positions[WHITE*7+ALL] | board->rank_positions[BLACK*7+ALL];
	pos = MSB(mask, 0);
	while(pos >= 0) {
	
		/* WHITE pieces */
		if(board->rank_positions[WHITE*7 + PAWN] & SQUARE(pos)) {
			val += PAWN_VAL;
		}
		else if(board->rank_positions[WHITE*7 + BISHOP] & SQUARE(pos)) {
			val += BISHOP_VAL;
		}
		else if(board->rank_positions[WHITE*7 + KNIGHT] & SQUARE(pos)) {
			val += KNIGHT_VAL;
		}
		else if(board->rank_positions[WHITE*7 + ROOK] & SQUARE(pos)) {
			val += ROOK_VAL;
		}
		else if(board->rank_positions[WHITE*7 + QUEEN] & SQUARE(pos)) {
			val += QUEEN_VAL;
		}
		else if(board->rank_positions[WHITE*7 + KING] & SQUARE(pos)) {
			val += KING_VAL;
		}
		
		/* BLACK pieces */
		else if(board->rank_positions[BLACK*7 + PAWN] & SQUARE(pos)) {
			val -= PAWN_VAL;
		}
		else if(board->rank_positions[BLACK*7 + BISHOP] & SQUARE(pos)) {
			val -= BISHOP_VAL;
		}
		else if(board->rank_positions[BLACK*7 + KNIGHT] & SQUARE(pos)) {
			val -= KNIGHT_VAL;
		}
		else if(board->rank_positions[BLACK*7 + ROOK] & SQUARE(pos)) {
			val -= ROOK_VAL;
		}
		else if(board->rank_positions[BLACK*7 + QUEEN] & SQUARE(pos)) {
			val -= QUEEN_VAL;
		}
		else if(board->rank_positions[BLACK*7 + KING] & SQUARE(pos)) {
			val -= KING_VAL;
		}
		
		/* otherwise something went wrong */
		else printf("\n\n\nFAIL\tFAIL\tFAIL\tFAIL\tFAIL\tFAIL\tFAIL\tFAIL\t\n\n\n");
		
		pos = MSB(mask, 64-pos);
	}
	
	return val;
}

