/* Travis Wolfe
 * December 2009
 */

#include "Board.h"
#include "Move.h"

#define SQUARE(X) (1L << (X))

void printb(Board *board) {
	long sq;
	int row, col;
	char b[8][8];
	for(row=0; row<8; row++) {
		for(col=0; col<8; col++) {
			
			sq = SQUARE(col*8+row);
			
			if(board->positions[WHITE*6+QUEEN] & sq)
				b[row][col] = 'Q';
			else if(board->positions[WHITE*6+KING] & sq)
				b[row][col] = 'K';
			else if(board->positions[WHITE*6+ROOK] & sq)
				b[row][col] = 'R';
			else if(board->positions[WHITE*6+BISHOP] & sq)
				b[row][col] = 'B';
			else if(board->positions[WHITE*6+KNIGHT] & sq)
				b[row][col] = 'N';
			else if(board->positions[WHITE*6+PAWN] & sq)
				b[row][col] = 'P';
			
			else if(board->positions[BLACK*6+QUEEN] & sq)
				b[row][col] = 'q';
			else if(board->positions[BLACK*6+KING] & sq)
				b[row][col] = 'k';
			else if(board->positions[BLACK*6+ROOK] & sq)
				b[row][col] = 'r';
			else if(board->positions[BLACK*6+BISHOP] & sq)
				b[row][col] = 'b';
			else if(board->positions[BLACK*6+KNIGHT] & sq)
				b[row][col] = 'n';
			else if(board->positions[BLACK*6+PAWN] & sq)
				b[row][col] = 'p';
			
			else b[row][col] = ' ';
		}
	}
	printf("    A  B  C  D  E  F  G  H\n");
	printf("   ------------------------\n");
	for(col=7; col>=0; col--) {
		printf("%d |", col+1);
		for(row=0; row<8; row++) {
			printf(" %c ", b[row][col]);
		}
		printf("| %d\n", col+1);
	}
	printf("   ------------------------\n");
	printf("    A  B  C  D  E  F  G  H\n");
}

void init(Board *board) {
	printf("[Board.init] initializing the board\n");
	
	set_play(board, WHITE);
	
	board->positions = (long*) malloc(12*sizeof(long));
	
	board->positions[WHITE*6+KING] = SQUARE(4);
	board->positions[WHITE*6+QUEEN] = SQUARE(3);
	board->positions[WHITE*6+ROOK] = SQUARE(0) | SQUARE(7);
	board->positions[WHITE*6+BISHOP] = SQUARE(2) | SQUARE(5);
	board->positions[WHITE*6+KNIGHT] = SQUARE(1) | SQUARE(6);
	board->positions[WHITE*6+PAWN] = SQUARE(8) | SQUARE(9) | SQUARE(10) |
									SQUARE(11) | SQUARE(12) | SQUARE(13) |
									SQUARE(14) | SQUARE(15);
	
	board->positions[BLACK*6+KING] = SQUARE(60);
	board->positions[BLACK*6+QUEEN] = SQUARE(59);
	board->positions[BLACK*6+ROOK] = SQUARE(56) | SQUARE(63);
	board->positions[BLACK*6+BISHOP] = SQUARE(58) | SQUARE(61);
	board->positions[BLACK*6+KNIGHT] = SQUARE(57) | SQUARE(62);
	board->positions[BLACK*6+PAWN] = SQUARE(48) | SQUARE(49) | SQUARE(50) |
									SQUARE(51) | SQUARE(52) | SQUARE(53) |
									SQUARE(54) | SQUARE(55);
}

void dispose(Board *board) {
	printf("[Board.dispose] getting rid of the board\n");
	/* free(board->positions); */
}

int ply(Board *board) {
	return (board->ply_and_play & 0xFFFF);
}

void set_ply(Board *board, int ply) {
	board->ply_and_play &= ~0xFFFF;
	board->ply_and_play |= ply;
}


int to_play(Board *board) {
	int offset = sizeof(int) - 1;
	if((board->ply_and_play >> offset) ^ WHITE)
		return BLACK;
	return WHITE;
}

void set_play(Board *board, int color) {
	int offset = sizeof(int) - 1;
	board->ply_and_play = color << offset;
}

long* pawn_attacks() {
	int rank, file;
	long *r = (long*) malloc(2*64*sizeof(long));
	
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			r[WHITE*64 + rank*8 + file] = 0L;
			r[BLACK*64 + rank*8 + file] = 0L;
			
			if(rank < 7) {
				r[WHITE*64 + rank*8 + file] = SQUARE(rank*8+file + UP);
				if(rank < 6) {
					r[WHITE*64 + rank*8 + file] |= SQUARE(rank*8+file + 2*UP);
				}
			}
			
			if(rank > 0) {
				r[BLACK*64 + rank*8 + file] = SQUARE(rank*8+file + DOWN);
				if(rank > 1) {
					r[BLACK*64 + rank*8 + file] |= SQUARE(rank*8+file + 2*DOWN);
				}
			}
		}
	}
	return r;
}

Move* get_moves(Board *board, int *num_moves) {
	
	return NULL;
}

/*
long* makeFileAttacks() {
	int rank, file, i, j, k;
	long* r = (long*) malloc(64*256*sizeof(long));
	
	for(int rank=0; rank<8; rank++) {
		for(int file=0; file<8; file++) {
			
			k = file*8 + (8-rank);
			
			for(i=0; i<256; i++) {
				r[k][i] = 0L;
				
				// start from where you are, move up/down
				j = rank;
				
				while(j >= 0) {
					if(!is_zero(i, j)) break;
					r[k][i] |= 1L<<j;
				}
				
				j = rank;
				
				while(j < 8) {
					if(!is_zero(i, j)) break;
					r[k][i] |= 1L<<j;
				}
			}
		}
	}
	return r;
}
*/

