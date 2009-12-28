/* Travis Wolfe
 * December 2009
 */

#include "Board.h"

#define SQUARE(X) (1L << (X))
#define IS_ZERO(BITS, INDEX) ((BITS & 1<<INDEX) == 0)

#define INITIAL_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\0"

void initf(Board *board, char *fen) {
	int rank, file, i;
	long sq;
	char c;
	
	/* === List of Things in FEN ========
	 * pieces (white is in capitals)
	 * color to play
	 * castling ability
	 * en pessant
	 * halfmove clock
	 * fullmove number
	 * ================================== */
	
	/* set the pieces */
	rank = 0, file = 0, i = 0;
	c = 'x';
	while(c != ' ') {
		c = fen[i++];
		sq = SQUARE(rank*8 + file);
		switch(c) {
			
			case 'K':
				board->rank_positions[WHITE*6 + KING] |= sq; break;
			case 'Q':
				board->rank_positions[WHITE*6 + QUEEN] |= sq; break;
			case 'R':
				board->rank_positions[WHITE*6 + ROOK] |= sq; break;
			case 'B':
				board->rank_positions[WHITE*6 + BISHOP] |= sq; break;
			case 'N':
				board->rank_positions[WHITE*6 + KNIGHT] |= sq; break;
			case 'P':
				board->rank_positions[WHITE*6 + PAWN] |= sq; break;
			
			case 'k':
				board->rank_positions[BLACK*6 + KING] |= sq; break;
			case 'q':
				board->rank_positions[BLACK*6 + QUEEN] |= sq; break;
			case 'r':
				board->rank_positions[BLACK*6 + ROOK] |= sq; break;
			case 'b':
				board->rank_positions[BLACK*6 + BISHOP] |= sq; break;
			case 'n':
				board->rank_positions[BLACK*6 + KNIGHT] |= sq; break;
			case 'p':
				board->rank_positions[BLACK*6 + PAWN] |= sq; break;
				
			/* new rank */
			case '/':
				rank--;
				file = -1;	/* will be incremented to 0 outside swtich */
				break;
			
			/* its a number (advance by X files... he-he) */
			default:
				file += (c - 48);
				file--;		/* to counter the normal increment */
				break;
		}
		
		file++;
		if(file >= 8) {
			file = 0;
			rank--;
		}
	}
	
	/* set to color to play */
	i++;
	if(fen[i] == 'w' || fen[i] == 'W')
		set_play(board, WHITE);
	else set_play(board, BLACK);
	
	/* set castling ability */
	/* TODO */
	
	/* set en pessant */
	/* TODO */
	
	/* set the halfmove clock */
	/* TODO */
	
	/* set fullmove number */
	/* TODO */
	
}

void printb(Board *board) {
	long sq;
	int row, col;
	char b[8][8];
	for(row=0; row<8; row++) {
		for(col=0; col<8; col++) {
			
			sq = SQUARE(col*8+row);
			
			if(board->rank_positions[WHITE*6+QUEEN] & sq)
				b[row][col] = 'Q';
			else if(board->rank_positions[WHITE*6+KING] & sq)
				b[row][col] = 'K';
			else if(board->rank_positions[WHITE*6+ROOK] & sq)
				b[row][col] = 'R';
			else if(board->rank_positions[WHITE*6+BISHOP] & sq)
				b[row][col] = 'B';
			else if(board->rank_positions[WHITE*6+KNIGHT] & sq)
				b[row][col] = 'N';
			else if(board->rank_positions[WHITE*6+PAWN] & sq)
				b[row][col] = 'P';
			
			else if(board->rank_positions[BLACK*6+QUEEN] & sq)
				b[row][col] = 'q';
			else if(board->rank_positions[BLACK*6+KING] & sq)
				b[row][col] = 'k';
			else if(board->rank_positions[BLACK*6+ROOK] & sq)
				b[row][col] = 'r';
			else if(board->rank_positions[BLACK*6+BISHOP] & sq)
				b[row][col] = 'b';
			else if(board->rank_positions[BLACK*6+KNIGHT] & sq)
				b[row][col] = 'n';
			else if(board->rank_positions[BLACK*6+PAWN] & sq)
				b[row][col] = 'p';
			
			else b[row][col] = '-';
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

void setup(Board *board) {
	printf("[Board.init] initializing the board\n");
	
	set_play(board, WHITE);
	
	board->rank_positions[WHITE*6+KING] = SQUARE(4);
	board->rank_positions[WHITE*6+QUEEN] = SQUARE(3);
	board->rank_positions[WHITE*6+ROOK] = SQUARE(0) | SQUARE(7);
	board->rank_positions[WHITE*6+BISHOP] = SQUARE(2) | SQUARE(5);
	board->rank_positions[WHITE*6+KNIGHT] = SQUARE(1) | SQUARE(6);
	board->rank_positions[WHITE*6+PAWN] = SQUARE(8) | SQUARE(9) | SQUARE(10) |
									SQUARE(11) | SQUARE(12) | SQUARE(13) |
									SQUARE(14) | SQUARE(15);
	
	board->rank_positions[BLACK*6+KING] = SQUARE(60);
	board->rank_positions[BLACK*6+QUEEN] = SQUARE(59);
	board->rank_positions[BLACK*6+ROOK] = SQUARE(56) | SQUARE(63);
	board->rank_positions[BLACK*6+BISHOP] = SQUARE(58) | SQUARE(61);
	board->rank_positions[BLACK*6+KNIGHT] = SQUARE(57) | SQUARE(62);
	board->rank_positions[BLACK*6+PAWN] = SQUARE(48) | SQUARE(49) | SQUARE(50) |
									SQUARE(51) | SQUARE(52) | SQUARE(53) |
									SQUARE(54) | SQUARE(55);
}

void dispose(Board *board) {
	printf("[Board.dispose]\t\tgetting rid of the board\n");
	/* free(board->rank_positions); */
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

long* make_file_attacks() {
	
	/* note: the size of this lookup table can
	 * be cut by 75% by removing the 2 bits that
	 * signify the ends of the board. you can always
	 * move to them whether there is a piece there
	 * or not.
	 */
	
	int rank, file, i, j, k;
	long* r = (long*) malloc(64*256*sizeof(long));
	
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			k = rank*8 + file;
			for(i=0; i<256; i++) {
				
				r[k*256 + i] = 0L;
				
				j = rank-1;
				while(j >= 0 && (  (i & (1<<j)) == 0  )) {
					r[k*256 + i] |= SQUARE(j*8 + file);
					j--;
				}
				if(j >= 0)
					r[k*256 + i] |= SQUARE(j*8 + file);
				
				j = rank+1;
				while(j < 8 && (  (i & (1<<j)) == 0  )) {
					r[k*256 + i] |= SQUARE(j*8 + file);
					j++;
				}
				if(j < 8)
					r[k*256 + i] |= SQUARE(j*8 + file);
			}
		}
	}
	return r;
}

long* make_rank_attacks() {
	
	/* note: the size of this lookup table can
	 * be cut by 75% by removing the 2 bits that
	 * signify the ends of the board. you can always
	 * move to them whether there is a piece there
	 * or not.
	 */
	
	int rank, file, i, j, k;
	long* r = (long*) malloc(64*256*sizeof(long));
	
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			k = rank*8 + file;
			for(i=0; i<256; i++) {
				
				r[k*256 + i] = 0L;
				
				j = file-1;
				while(j >= 0 && (  (i & (1<<j)) == 0  )) {
					r[k*256 + i] |= SQUARE(rank*8 + j);
					j--;
				}
				if(j >= 0)
					r[k*256 + i] |= SQUARE(rank*8 + j);
				
				j = file+1;
				while(j < 8 && (  (i & (1<<j)) == 0  )) {
					r[k*256 + i] |= SQUARE(rank*8 + j);
					j++;
				}
				if(j < 8)
					r[k*256 + i] |= SQUARE(rank*8 + j);
			}
		}
	}
	return r;
}


