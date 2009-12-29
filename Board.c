/* Travis Wolfe
 * December 2009
 */

#include "Board.h"

#define SQUARE(X) (1L << (X))
#define IS_ZERO(BITS, INDEX) ((BITS & 1<<INDEX) == 0)
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

#define INITIAL_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\0"

void initf(Board *board, char *fen) {
	int rank, file, i, t;
	long r_sq, f_sq, tl_br_sq, bl_tr_sq;
	char c;
	
	/* === List of Things in FEN ========
	 * pieces (white is in capitals)
	 * color to play
	 * castling ability
	 * en pessant
	 * halfmove clock
	 * fullmove number
	 * ================================== */
	
	/* set the intial maps to 0 */
	for(i=0; i<12; i++) {
		board->rank_positions[i] = 0L;
		board->file_positions[i] = 0L;
		board->tl_br_positions[i] = 0L;
		board->bl_tr_positions[i] = 0L;
	}
	
	/* set the pieces */
	rank = 7, file = 0, i = 0;
	c = 'x';
	
	while(c != ' ') {
		
		c = fen[i++];
		
		/* find the rank and file sq number */
		r_sq = SQUARE(rank*8 + file);
		f_sq = SQUARE(file*8 + rank);
		
		/* find the tl_br number */
		if(rank >= file) {
			t = MAX(rank-7, file);
			tl_br_sq = SQUARE(t*(t-1)/2 + file);
		}
		else {
			t = MAX(rank, 7-file);
			tl_br_sq = SQUARE(63 - (t*(t-1)/2 + 7-file));
		}
		
		/* find the br_tl number */
		if(rank + file <= 7) {
			t = MAX(rank, file);
			bl_tr_sq = SQUARE(t*(t-1)/2 + rank);
		}
		else {
			t = MAX(7-rank, 7-file);
			bl_tr_sq = SQUARE(63 - (t*(t-1)/2 + 7-rank));
		}
		
		switch(c) {
			
			case 'K':
				board->rank_positions[WHITE*6 + KING] |= r_sq;
				board->file_positions[WHITE*6 + KING] |= f_sq;
				board->tl_br_positions[WHITE*6 + KING] |= tl_br_sq;
				board->bl_tr_positions[WHITE*6 + KING] |= bl_tr_sq;
				break;
			case 'Q':
				board->rank_positions[WHITE*6 + QUEEN] |= r_sq;
				board->file_positions[WHITE*6 + QUEEN] |= f_sq;
				board->tl_br_positions[WHITE*6 + QUEEN] |= tl_br_sq;
				board->bl_tr_positions[WHITE*6 + QUEEN] |= bl_tr_sq;
				break;
			case 'R':
				board->rank_positions[WHITE*6 + ROOK] |= r_sq;
				board->file_positions[WHITE*6 + ROOK] |= f_sq;
				board->tl_br_positions[WHITE*6 + ROOK] |= tl_br_sq;
				board->bl_tr_positions[WHITE*6 + ROOK] |= bl_tr_sq;
				break;
			case 'B':
				board->rank_positions[WHITE*6 + BISHOP] |= r_sq;
				board->file_positions[WHITE*6 + BISHOP] |= f_sq;
				board->tl_br_positions[WHITE*6 + BISHOP] |= tl_br_sq;
				board->bl_tr_positions[WHITE*6 + BISHOP] |= bl_tr_sq;
				break;
			case 'N':
				board->rank_positions[WHITE*6 + KNIGHT] |= r_sq;
				board->file_positions[WHITE*6 + KNIGHT] |= f_sq;
				board->tl_br_positions[WHITE*6 + KNIGHT] |= tl_br_sq;
				board->bl_tr_positions[WHITE*6 + KNIGHT] |= bl_tr_sq;
				break;
			case 'P':
				board->rank_positions[WHITE*6 + PAWN] |= r_sq;
				board->file_positions[WHITE*6 + PAWN] |= f_sq;
				board->tl_br_positions[WHITE*6 + PAWN] |= tl_br_sq;
				board->bl_tr_positions[WHITE*6 + PAWN] |= bl_tr_sq;
				break;
			
			case 'k':
				board->rank_positions[BLACK*6 + KING] |= r_sq;
				board->file_positions[BLACK*6 + KING] |= f_sq;
				board->tl_br_positions[BLACK*6 + KING] |= tl_br_sq;
				board->bl_tr_positions[BLACK*6 + KING] |= bl_tr_sq;
				break;
			case 'q':
				board->rank_positions[BLACK*6 + QUEEN] |= r_sq;
				board->file_positions[BLACK*6 + QUEEN] |= f_sq;
				board->tl_br_positions[BLACK*6 + QUEEN] |= tl_br_sq;
				board->bl_tr_positions[BLACK*6 + QUEEN] |= bl_tr_sq;
				break;
			case 'r':
				board->rank_positions[BLACK*6 + ROOK] |= r_sq;
				board->file_positions[BLACK*6 + ROOK] |= f_sq;
				board->tl_br_positions[BLACK*6 + ROOK] |= tl_br_sq;
				board->bl_tr_positions[BLACK*6 + ROOK] |= bl_tr_sq;
				break;
			case 'b':
				board->rank_positions[BLACK*6 + BISHOP] |= r_sq;
				board->file_positions[BLACK*6 + BISHOP] |= f_sq;
				board->tl_br_positions[BLACK*6 + BISHOP] |= tl_br_sq;
				board->bl_tr_positions[BLACK*6 + BISHOP] |= bl_tr_sq;
				break;
			case 'n':
				board->rank_positions[BLACK*6 + KNIGHT] |= r_sq;
				board->file_positions[BLACK*6 + KNIGHT] |= f_sq;
				board->tl_br_positions[BLACK*6 + KNIGHT] |= tl_br_sq;
				board->bl_tr_positions[BLACK*6 + KNIGHT] |= bl_tr_sq;
				break;
			case 'p':
				board->rank_positions[BLACK*6 + PAWN] |= r_sq;
				board->file_positions[BLACK*6 + PAWN] |= f_sq;
				board->tl_br_positions[BLACK*6 + PAWN] |= tl_br_sq;
				board->bl_tr_positions[BLACK*6 + PAWN] |= bl_tr_sq;
				break;
				
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
	int rank, file;
	char b[8][8];
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			sq = SQUARE(rank*8+file);
			
			if(board->rank_positions[WHITE*6+QUEEN] & sq)
				b[rank][file] = 'Q';
			else if(board->rank_positions[WHITE*6+KING] & sq)
				b[rank][file] = 'K';
			else if(board->rank_positions[WHITE*6+ROOK] & sq)
				b[rank][file] = 'R';
			else if(board->rank_positions[WHITE*6+BISHOP] & sq)
				b[rank][file] = 'B';
			else if(board->rank_positions[WHITE*6+KNIGHT] & sq)
				b[rank][file] = 'N';
			else if(board->rank_positions[WHITE*6+PAWN] & sq)
				b[rank][file] = 'P';
			
			else if(board->rank_positions[BLACK*6+QUEEN] & sq)
				b[rank][file] = 'q';
			else if(board->rank_positions[BLACK*6+KING] & sq)
				b[rank][file] = 'k';
			else if(board->rank_positions[BLACK*6+ROOK] & sq)
				b[rank][file] = 'r';
			else if(board->rank_positions[BLACK*6+BISHOP] & sq)
				b[rank][file] = 'b';
			else if(board->rank_positions[BLACK*6+KNIGHT] & sq)
				b[rank][file] = 'n';
			else if(board->rank_positions[BLACK*6+PAWN] & sq)
				b[rank][file] = 'p';
			
			else b[rank][file] = '-';
		}
	}
	printf("    A  B  C  D  E  F  G  H\n");
	printf("   ------------------------\n");
	for(rank=7; rank>=0; rank--) {
		printf("%d |", rank+1);
		for(file=0; file<8; file++) {
			printf(" %c ", b[rank][file]);
		}
		printf("| %d\n", rank+1);
	}
	printf("   ------------------------\n");
	printf("    A  B  C  D  E  F  G  H\n");
}

void setup(Board *board) {
	printf("[Board.init]\tinitializing the board\n");
	set_play(board, WHITE);
	set_ply(board, 0);
	initf(board, INITIAL_FEN);
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
			
			/* either this or make_rank_attacks needs
			 * to index differently
			 */
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
			
			/* either this or make_file_attacks needs
			 * to index differently
			 */
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

long* make_tl_br_attacks() {
	
	int rank, file, width, i, j, sq;
	long *r = (long*) malloc(64*256*sizeof(long));
	
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			/* for this rank, file the length of
			 * the diagnol is:
			 */
			if(rank >= file) {
				width = (7-rank) + file + 1;
			}
			else {
				width = rank + (7-file) + 1;
			}
			
			/* should i keep this in standard form or diagnol */
			/* i think it should be in diagnol */
			/* revisit this issue in rank/file attacks */
			sq = width*(width-1) + file;
			
			if(width < 1 || width > 8)
				printf("[board.tl_br_attacks]\twidth = %d", width);
			
			/* make a set of bit masks for the
			 * 2^width configurations
			 */
			for(i = (1<<width) - 1; i>=0; i--) {
				
				r[sq*256 + i] = 0L;
				
				/* in configuration i, sq is at place file */
				j = file - 1;
				while(j >= 0 && ( (i & (1<<j)) == 0) ) {
					r[sq*256 + i] |= SQUARE(width*(width-1) + j);
					j--;
				}
				if(j >= 0) {
					r[sq*256 + i] |= SQUARE(width*(width-1) + j);
				}
				
				j = file + 1;
				while(j < width && ( (i & (1<<j)) == 0) ) {
					r[sq*256 + i] |= SQUARE(width*(width-1) + j);
					j++;
				}
				if(j < width) {
					r[sq*256 + i] |= SQUARE(width*(width-1) + j);
				}			
			}
			
		}
	}
	return r;
}







