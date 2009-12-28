/* Travis Wolfe
 * December 2009
 */

#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

#define SQUARE(X) (1L << (X))
#define puts(X) printf(X); printf("\n");

#define WIN 	1
#define FAIL 	0

int test_to_play(Board *board) {
	set_play(board, WHITE);
	if(to_play(board) != WHITE) {
		printf("[tests.test_to_play] failed to set the player\n");
		return FAIL;
	}
	
	set_play(board, BLACK);
	if(to_play(board) != BLACK) {
		printf("[tests.test_to_play] failed to set the player\n");
		return FAIL;
	}
	
	set_play(board, WHITE);
	if(to_play(board) != WHITE) {
		printf("[tests.test_to_play] failed to set the player\n");
		return FAIL;
	}
	
	printf("[testing.to_play]\tpassed\n");
	return WIN;
}

int test_ply(Board *board) {
	
	set_ply(board, 11);
	if(ply(board) != 11) {
		printf("[tests.test_ply] failed to set ply\n");
		return FAIL;
	}
	
	set_ply(board, 1);
	if(ply(board) != 1) {
		printf("[tests.test_ply] failed to set ply\n");
		return FAIL;
	}
	
	set_ply(board, 21);
	if(ply(board) != 21) {
		printf("[tests.test_ply] failed to set ply\n");
		return FAIL;
	}
	
	set_ply(board, 111);
	if(ply(board) != 111) {
		printf("[tests.test_ply] failed to set ply\n");
		return FAIL;
	}
	
	set_ply(board, 21);
	if(ply(board) != 21) {
		printf("[tests.test_ply] failed to set ply\n");
		return FAIL;
	}
	
	printf("[testing.ply]\t\tpassed\n");
	return WIN;
}

int test_pawn_moves(Board *board) {
	int sq, status;
	long mask, expected;
	long *pawn_array = pawn_attacks();
	
	status = WIN;
	
	/* say i had a WHITE pawn at B2 (9)
	 * it should have a move to B3 (17) and B4 (25)
	 */
	sq = 9;
	mask = pawn_array[WHITE*64 + sq];
	expected = SQUARE(17) ^ SQUARE(25);
	if(mask != expected) {
		printf("[tests.pawn_tests] (1) expected %d, but got %d\n", (int) expected, (int) mask);
		status = FAIL;
	}
	
	/* if i had a BLACK pawn at B2 (9) again,
	 * i should only have one move to B1 (1)
	 */
	sq = 9;
	mask = pawn_array[BLACK*64 + sq];
	expected = SQUARE(1);
	if(mask != expected)  {
		printf("[tests.pawn_tests] (2) expected %d, but got %d\n", (int) expected, (int) mask);
		status = FAIL;
	}
	
	/* if i had a WHITE pawn at C8 (58), I should
	 * not have any allowed moves
	 */
	sq = 58;
	mask = pawn_array[WHITE*64 + sq];
	expected = 0L;
	if(mask != expected)  {
		printf("[tests.pawn_tests] (2) expected %d, but got %d\n", (int) expected, (int) mask);
		status = FAIL;
	}
	
	free(pawn_array);
	return status;
}

void stupid_tests() {
	long mask;
	mask = SQUARE(12);
	if(mask != (1L<<12))
		printf("[main.stupid] (1)\tyou're failing the stupid tests!\n");
		
	mask = SQUARE(8 + UP);
	if(mask != (1L<<16)) {
		printf("[main.stupid] (2)\tyou're failing the stupid tests!\n");
		printf("up = %d\n", UP);
	}
}

int test_file_attacks() {
	long mask, expected;
	int status, sq, file;
	long *fattacks = make_file_attacks();
	status = WIN;
	
	/* lets assume we queen at D1 (3) and
	 * pieces at D3 (19) and D5 (35).
	 * this should leave a move to D2 (11)
	 * and D3 (19).
	 */
	sq = 3;
	expected = SQUARE(sq+8) | SQUARE(sq+8*2);
	file = (1<<2) | (1<<4) | 1;
	mask = fattacks[sq*256 + file];
	if(mask != expected) {
		printf("[tests.file_attacks] (1) expected %d, but got %d, file = %d\n", (int) expected, (int) mask, file);
		status = FAIL;
	}
	
	/* lets assume we rook at H3 (23) and
	 * pieces at H2 (15) and H4 (31).
	 * this should leave moves to H2 (15)
	 * and H4 (31)
	 */
	sq = 23;
	expected = SQUARE(sq-8) | SQUARE(sq+8);
	file = (1<<1) | (1<<2) | (1<<3);
	mask = fattacks[sq*256 + file];
	if(mask != expected) {
		printf("[tests.file_attacks] (2) expected %d, but got %d, file = %d\n", (int) expected, (int) mask, file);
		status = FAIL;
	}
	
	/* lets assume we rook at A8 (56) and
	 * a piece at A7 (48).
	 * this should leave a to A7 (48)
	 */
	sq = 56;
	expected = SQUARE(sq-8);
	file = (1<<7) | (1<<6);
	mask = fattacks[sq*256 + file];
	if(mask != expected) {
		printf("[tests.file_attacks] (3) expected %i, but got %i, file = %d\n", (int) expected, (int) mask, file);
		status = FAIL;
	}
	
	free(fattacks);
	return status;
}

int test_rank_attacks() {
	/* TODO */
	return FAIL;
}

int main(int argc, const char * argv[]) {
	
	stupid_tests();
	printf("[tests.main]\tsanity check: sizeof(long) = %d\n", (int) sizeof(long));
	
	printf("[tests.main]\trunning tests....\n");
	
	Board board;
	setup(&board);
	printb(&board);
	test_to_play(&board);
	test_ply(&board);
	
	if(WIN == test_pawn_moves(&board))
		printf("[tests.pawn_moves]\tpassed\n");
	else printf("[tests.pawn_moves]\tFAILED!\n");
	
	if(WIN == test_file_attacks())
		printf("[tests.file_attacks]\tpassed\n");
	else printf("[tests.file_attacks]\tFAILED!\n");
		
	if(WIN == test_rank_attacks())
		printf("[tests.file_attacks]\tpassed\n");
	else printf("[tests.file_attacks]\tFAILED!\n");
	
	dispose(&board);
	
	printf("[tests.main]\t\ttests complete\n");
	return EXIT_SUCCESS;
}
