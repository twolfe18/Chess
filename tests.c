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
	
	printf("[testing.to_play]\tpassed!\n");
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
	
	printf("[testing.ply]\t\tpassed!\n");
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

int main(int argc, const char * argv[]) {
	
	stupid_tests();
	printf("[tests.main]\tsanity check: sizeof(long) = %d\n", (int) sizeof(long));
	
	printf("[tests.main]\trunning tests....\n");
	
	Board board;
	init(&board);
	printb(&board);
	test_to_play(&board);
	test_ply(&board);
	
	if(WIN == test_pawn_moves(&board))
		printf("[tests.pawn_moves]\tpassed!\n");
	else printf("[tests.pawn_moves]\tfailed!\n");
	
	dispose(&board);
	
	printf("[tests.main]\ttests complete\n");
	return EXIT_SUCCESS;
}
