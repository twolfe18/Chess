
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

void test_to_play(Board *board) {
	set_play(board, WHITE);
	if(to_play(board) != WHITE) {
		printf("[tests.test_to_play] failed to set the player\n");
		return;
	}
	
	set_play(board, BLACK);
	if(to_play(board) != BLACK) {
		printf("[tests.test_to_play] failed to set the player\n");
		return;
	}
	
	set_play(board, WHITE);
	if(to_play(board) != WHITE) {
		printf("[tests.test_to_play] failed to set the player\n");
		return;
	}
	
	printf("[testing.to_play] passed to_play tests!\n");
}

void test_ply(Board *board) {
	
	set_ply(board, 11);
	if(ply(board) != 11) {
		printf("[tests.test_ply] failed to set ply\n");
		return;
	}
	
	set_ply(board, 1);
	if(ply(board) != 1) {
		printf("[tests.test_ply] failed to set ply\n");
		return;
	}
	
	set_ply(board, 21);
	if(ply(board) != 21) {
		printf("[tests.test_ply] failed to set ply\n");
		return;
	}
	
	set_ply(board, 111);
	if(ply(board) != 111) {
		printf("[tests.test_ply] failed to set ply\n");
		return;
	}
	
	printf("[testing.ply] passed all ply tests!\n");
}

int main(int argc, const char * argv[]) {
	
	printf("[tests.main] running tests....\n");
	
	Board board;
	init(&board);
	printb(&board);
	test_to_play(&board);
	test_ply(&board);
	dispose(&board);
	
	printf("[tests.main] tests complete\n");
	return EXIT_SUCCESS;
}
