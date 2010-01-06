/* Travis Wolfe
 * December 2009
 */

#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

#define QUIET 0

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

void stupid_tests() {
	unsigned long mask;
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
	unsigned long mask, expected;
	int status, sq, file;
	unsigned long *fattacks = make_file_attacks();
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
	unsigned long mask, expected;
	int status, sq, rank;
	unsigned long *rattacks = make_rank_attacks();
	status = WIN;
	
	/* lets assume we queen at D1 (3) and
	 * pieces at E1 (4) and H1 (7).
	 * this should leave moves from A1 (0)
	 * through E1 (4).
	 */
	sq = 3;
	expected = SQUARE(sq+1) | SQUARE(sq-1) | SQUARE(sq-2) | SQUARE(sq-3);
	rank = (1<<3) | (1<<4) | (1<<7);
	mask = rattacks[sq*256 + rank];
	if(mask != expected) {
		printf("[tests.rank_attacks] (1) expected %d, but got %d, rank = %d\n", (int) expected, (int) mask, rank);
		status = FAIL;
	}
	
	/* lets assume we rook at H8 (63) and
	 * a piece at G8 (62)
	 * this should leave on move to G8 (62)
	 */
	sq = 63;
	expected = SQUARE(sq-1);
	rank = (1<<6) | (1<<7);
	mask = rattacks[sq*256 + rank];
	if(mask != expected) {
		printf("[tests.rank_attacks] (1) expected %d, but got %d, rank = %d\n", (int) expected, (int) mask, rank);
		status = FAIL;
	}
	
	/* lets assume we rook at C5 (42) and
	 * no other pieces in that rank
	 * this should give moves to A5 (40) through
	 * H5 (47) except C5
	 */
	sq = 42;
	expected = SQUARE(sq-2) | SQUARE(sq-1) | SQUARE(sq+1) | SQUARE(sq+2) | SQUARE(sq+3) | SQUARE(sq+4) | SQUARE(sq+5);
	rank = 0;
	mask = rattacks[sq*256 + rank];
	if(mask != expected) {
		printf("[tests.rank_attacks] (1) expected %d, but got %d, rank = %d\n", (int) expected, (int) mask, rank);
		status = FAIL;
	}
	
	return status;
}

int test_initf() {
	
	/* TODO: test tl_br position maps */
	/* TODO: test bl_tr position maps */
	
	return FAIL;
}

int test_tl_br_attacks() {
	
	/* TODO */
	
	return FAIL;
}

int test_knight_attacks() {
	
	/* TODO */
	
	return FAIL;
}

int test_king_attacks() {
	
	/* TODO */
	
	return FAIL;
}

int test_moves() {
	Board b;
	Move *moves;
	int status, num_moves, expected;
	status = WIN;

	printf("testing moves");

	get_ready();
	
	printf("\tgot ready\n");

	/* on startup, there shouldn't be any king moves */
	setup(&b);
	moves = gen_moves(&b, &num_moves);
	expected = 20;
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves);
	
	/* try this config (black moves) */
	initf(&b, "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
	moves = gen_moves(&b, &num_moves);
	expected = 22;
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves);
	
	/* try this config (white moves) */
	initf(&b, "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
	set_play(&b, WHITE);
	moves = gen_moves(&b, &num_moves);
	expected = 13 + 7 + 1 + 1 + 5; /* pawns, knights, king, queen, bishop */
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves);
	
	/* here is one with only rook moves */
	initf(&b, "8/8/8/2r5/8/5R2/8/8 b KQkq - 1 2");
	moves = gen_moves(&b, &num_moves);
	expected = 14;
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves);
	
	/* here is one with only rook moves */
	initf(&b, "8/2p5/8/2r5/8/5R2/8/8 b KQkq - 1 2");
	moves = gen_moves(&b, &num_moves);
	expected = 13;
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves); 
	
	/* here is another one with only rook moves */
	initf(&b, "8/2p5/8/2rp4/8/5R2/8/8 b KQkq - 1 2");
	moves = gen_moves(&b, &num_moves);
	expected = 9;
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves);
	
	/* here is one last one with only rook moves */
	initf(&b, "8/2p5/8/2rp4/8/2p2R2/8/8 b KQkq - 1 2");
	moves = gen_moves(&b, &num_moves);
	expected = 7;
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves);
	
	/* and again for white... */
	initf(&b, "8/2p5/8/2rp4/8/2p2R2/8/8 w KQkq - 1 2");
	moves = gen_moves(&b, &num_moves);
	expected = 12;
	if(num_moves != expected) {
		if(!QUIET) {
			if(to_play(&b) == WHITE)
				printf("\t>> WHITE to play, ");
			else
				printf("\t>> BLACK to play, ");
			printf("expected %d moves, but saw %d\n", expected, num_moves);
			printb(&b);
		}
		status = FAIL;
	}
	free(moves);

	clean_up();
	
	return status;
}

int main(int argc, const char * argv[]) {
	
	stupid_tests();
	printf("[tests.main]\tsanity check: sizeof(unsigned long) = %d\n", (int) sizeof(unsigned long));
	
	printf("[tests.main]\trunning tests....\n");
	
	Board board;
	setup(&board);
	printf("\n");
	printb(&board);
	printf("\n");
	
	test_to_play(&board);
	test_ply(&board);
	
	if(WIN == test_file_attacks())
		printf("[tests.file_attacks]\tpassed\n");
	else printf("[tests.file_attacks]\tFAILED!\n");
		
	if(WIN == test_rank_attacks())
		printf("[tests.rank_attacks]\tpassed\n");
	else printf("[tests.rank_attacks]\tFAILED!\n");
	
	/*** WTF MANG??? ***/
	printf("OMG MY STUPID TEST\n");
	Move *moves = (Move*) malloc(80*sizeof(Move));
	free(moves);
	printf("worked this time!\n");
	/*******************/
	
	if(WIN == test_initf())
		printf("[tests.initf]\t\tpassed\n");
	else printf("[tests.initf]\t\tFAILED!\n");
	
	if(WIN == test_tl_br_attacks())
		printf("[tests.tl_br_attacks]\tpassed\n");
	else printf("[tests.tl_br_attacks]\tFAILED!\n");
	
	if(WIN == test_knight_attacks())
		printf("[tests.knight_attacks]\tpassed\n");
	else printf("[tests.knight_attacks]\tFAILED!\n");
	
	if(WIN == test_king_attacks())
		printf("[tests.king_attacks]\tpassed\n");
	else printf("[tests.king_attacks]\tFAILED!\n");
	
	if(WIN == test_moves())
		printf("[tests.moves]\t\tpassed\n");
	else printf("[tests.moves]\t\tFAILED!\n");
	
	printf("\n[tests.main]\t\ttests complete\n");
	return EXIT_SUCCESS;
}
