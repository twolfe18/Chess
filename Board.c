/* Travis Wolfe
 * December 2009
 */

#include "Board.h"

#define VERBOSE 0

#define SQUARE(X) (1L << (X))
#define IS_ZERO(BITS, INDEX) ((BITS & 1<<INDEX) == 0)
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define CLEAR(bits, index) (bits &= ~(1L << index))
#define RANK(square) (((int)square/8))
#define FILE(square) ((square%8))

#define INITIAL_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

long *rank_attacks;
long *file_attacks;
long *tl_br_attacks;
long *bl_tr_attacks;
long *king_attacks;
long *knight_attacks;

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
	for(i=0; i<14; i++) {
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
				board->rank_positions[WHITE*7 + KING] |= r_sq;
				board->file_positions[WHITE*7 + KING] |= f_sq;
				board->tl_br_positions[WHITE*7 + KING] |= tl_br_sq;
				board->bl_tr_positions[WHITE*7 + KING] |= bl_tr_sq;
				break;
			case 'Q':
				board->rank_positions[WHITE*7 + QUEEN] |= r_sq;
				board->file_positions[WHITE*7 + QUEEN] |= f_sq;
				board->tl_br_positions[WHITE*7 + QUEEN] |= tl_br_sq;
				board->bl_tr_positions[WHITE*7 + QUEEN] |= bl_tr_sq;
				break;
			case 'R':
				board->rank_positions[WHITE*7 + ROOK] |= r_sq;
				board->file_positions[WHITE*7 + ROOK] |= f_sq;
				board->tl_br_positions[WHITE*7 + ROOK] |= tl_br_sq;
				board->bl_tr_positions[WHITE*7 + ROOK] |= bl_tr_sq;
				break;
			case 'B':
				board->rank_positions[WHITE*7 + BISHOP] |= r_sq;
				board->file_positions[WHITE*7 + BISHOP] |= f_sq;
				board->tl_br_positions[WHITE*7 + BISHOP] |= tl_br_sq;
				board->bl_tr_positions[WHITE*7 + BISHOP] |= bl_tr_sq;
				break;
			case 'N':
				board->rank_positions[WHITE*7 + KNIGHT] |= r_sq;
				board->file_positions[WHITE*7 + KNIGHT] |= f_sq;
				board->tl_br_positions[WHITE*7 + KNIGHT] |= tl_br_sq;
				board->bl_tr_positions[WHITE*7 + KNIGHT] |= bl_tr_sq;
				break;
			case 'P':
				board->rank_positions[WHITE*7 + PAWN] |= r_sq;
				board->file_positions[WHITE*7 + PAWN] |= f_sq;
				board->tl_br_positions[WHITE*7 + PAWN] |= tl_br_sq;
				board->bl_tr_positions[WHITE*7 + PAWN] |= bl_tr_sq;
				break;
			
			case 'k':
				board->rank_positions[BLACK*7 + KING] |= r_sq;
				board->file_positions[BLACK*7 + KING] |= f_sq;
				board->tl_br_positions[BLACK*7 + KING] |= tl_br_sq;
				board->bl_tr_positions[BLACK*7 + KING] |= bl_tr_sq;
				break;
			case 'q':
				board->rank_positions[BLACK*7 + QUEEN] |= r_sq;
				board->file_positions[BLACK*7 + QUEEN] |= f_sq;
				board->tl_br_positions[BLACK*7 + QUEEN] |= tl_br_sq;
				board->bl_tr_positions[BLACK*7 + QUEEN] |= bl_tr_sq;
				break;
			case 'r':
				board->rank_positions[BLACK*7 + ROOK] |= r_sq;
				board->file_positions[BLACK*7 + ROOK] |= f_sq;
				board->tl_br_positions[BLACK*7 + ROOK] |= tl_br_sq;
				board->bl_tr_positions[BLACK*7 + ROOK] |= bl_tr_sq;
				break;
			case 'b':
				board->rank_positions[BLACK*7 + BISHOP] |= r_sq;
				board->file_positions[BLACK*7 + BISHOP] |= f_sq;
				board->tl_br_positions[BLACK*7 + BISHOP] |= tl_br_sq;
				board->bl_tr_positions[BLACK*7 + BISHOP] |= bl_tr_sq;
				break;
			case 'n':
				board->rank_positions[BLACK*7 + KNIGHT] |= r_sq;
				board->file_positions[BLACK*7 + KNIGHT] |= f_sq;
				board->tl_br_positions[BLACK*7 + KNIGHT] |= tl_br_sq;
				board->bl_tr_positions[BLACK*7 + KNIGHT] |= bl_tr_sq;
				break;
			case 'p':
				board->rank_positions[BLACK*7 + PAWN] |= r_sq;
				board->file_positions[BLACK*7 + PAWN] |= f_sq;
				board->tl_br_positions[BLACK*7 + PAWN] |= tl_br_sq;
				board->bl_tr_positions[BLACK*7 + PAWN] |= bl_tr_sq;
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
	
	/* set the ALL positions array */
	board->rank_positions[WHITE*7 + ALL] = board->rank_positions[WHITE*7 + KING]
											| board->rank_positions[WHITE*7 + QUEEN]
											| board->rank_positions[WHITE*7 + ROOK]
											| board->rank_positions[WHITE*7 + BISHOP]
											| board->rank_positions[WHITE*7 + KNIGHT]
											| board->rank_positions[WHITE*7 + PAWN];
	board->rank_positions[BLACK*7 + ALL] = board->rank_positions[BLACK*7 + KING]
											| board->rank_positions[BLACK*7 + QUEEN]
											| board->rank_positions[BLACK*7 + ROOK]
											| board->rank_positions[BLACK*7 + BISHOP]
											| board->rank_positions[BLACK*7 + KNIGHT]
											| board->rank_positions[BLACK*7 + PAWN];											
}

void printb(Board *board) {
	long sq;
	int rank, file;
	char b[8][8];
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			sq = SQUARE(rank*8+file);
			
			if(board->rank_positions[WHITE*7+QUEEN] & sq)
				b[rank][file] = 'Q';
			else if(board->rank_positions[WHITE*7+KING] & sq)
				b[rank][file] = 'K';
			else if(board->rank_positions[WHITE*7+ROOK] & sq)
				b[rank][file] = 'R';
			else if(board->rank_positions[WHITE*7+BISHOP] & sq)
				b[rank][file] = 'B';
			else if(board->rank_positions[WHITE*7+KNIGHT] & sq)
				b[rank][file] = 'N';
			else if(board->rank_positions[WHITE*7+PAWN] & sq)
				b[rank][file] = 'P';
			
			else if(board->rank_positions[BLACK*7+QUEEN] & sq)
				b[rank][file] = 'q';
			else if(board->rank_positions[BLACK*7+KING] & sq)
				b[rank][file] = 'k';
			else if(board->rank_positions[BLACK*7+ROOK] & sq)
				b[rank][file] = 'r';
			else if(board->rank_positions[BLACK*7+BISHOP] & sq)
				b[rank][file] = 'b';
			else if(board->rank_positions[BLACK*7+KNIGHT] & sq)
				b[rank][file] = 'n';
			else if(board->rank_positions[BLACK*7+PAWN] & sq)
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
	if(VERBOSE)
		printf("[Board.init]\tinitializing the board\n");
	set_play(board, WHITE);
	set_ply(board, 0);
	initf(board, INITIAL_FEN);
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
			
			/* for rank/file attacks, each square has the same
			 * number and width of masks
			 * for diagnol attacks, each square has varying
			 * size masks associated with it
			 * so the definition of square for the diagnol
			 * arrays matters, but for the rank/files it
			 * doesn't
			 */
			sq = width*(width-1) + file;
			
			if(width < 1 || width > 8)
				printf("[board.tl_br_attacks]\twidth = %d", width);
			
			/* make a set of bit masks for the
			 * 2^width configurations
			 */
			for(i = (1<<width) - 1; i>=0; i--) {
				
				/* this addressing system will work,
				 * but wont be space efficient
				 */
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

long* make_bl_tr_attacks() {
	long *r = (long*) malloc(64*256*sizeof(long));
	
	/* TODO */
	
	return r;
}

long* make_knight_attacks() {
	
	int rank, file, sq;
	long *r = (long*) malloc(64*sizeof(long));
	
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			sq = rank*8 + file;
			
			r[sq] = 0L;
			
			/* up, right */
			if(rank < 6 && file < 7) {
				r[sq] |= SQUARE(sq + 2*UP + RIGHT);
			}
			
			/* up, left */
			if(rank < 6 && file > 0) {
				r[sq] |= SQUARE(sq + 2*UP + LEFT);
			}
			
			/* right, up */
			if(rank < 7 && file < 6) {
				r[sq] |= SQUARE(sq + 2*RIGHT + UP);
			}
			
			/* right, down */
			if(rank > 0 && file < 6) {
				r[sq] |= SQUARE(sq + 2*RIGHT + DOWN);
			}
			
			/* down, right */
			if(rank > 1 && file < 7) {
				r[sq] |= SQUARE(sq + 2*DOWN + RIGHT);
			}
			
			/* down, left */
			if(rank > 1 && file > 0) {
				r[sq] |= SQUARE(sq + 2*DOWN + LEFT);
			}
			
			/* left, down */
			if(rank > 0 && file > 1) {
				r[sq] |= SQUARE(sq + 2*LEFT + DOWN);
			}
			
			/* left, up */
			if(rank < 7 && file > 1) {
				r[sq] |= SQUARE(sq + 2*LEFT + UP);
			}
		}
	}
	return r;
}

long* make_king_attacks() {
	
	int rank, file, sq;
	long *r = (long*) malloc(64*sizeof(long));
	
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			sq = rank*8 + file;
			
			r[sq] = 0L;
			
			/* up, right */
			if(rank < 7 && file < 7) {
				r[sq] |= SQUARE(sq + UP + RIGHT);
			}
			
			/* up, left */
			if(rank < 7 && file > 0) {
				r[sq] |= SQUARE(sq + UP + LEFT);
			}
			
			/* right, up */
			if(rank < 7 && file < 7) {
				r[sq] |= SQUARE(sq + RIGHT + UP);
			}
			
			/* right, down */
			if(rank > 0 && file < 7) {
				r[sq] |= SQUARE(sq + RIGHT + DOWN);
			}
			
			/* down, right */
			if(rank > 0 && file < 7) {
				r[sq] |= SQUARE(sq + DOWN + RIGHT);
			}
			
			/* down, left */
			if(rank > 0 && file > 0) {
				r[sq] |= SQUARE(sq + DOWN + LEFT);
			}
			
			/* left, down */
			if(rank > 0 && file > 0) {
				r[sq] |= SQUARE(sq + LEFT + DOWN);
			}
			
			/* left, up */
			if(rank < 7 && file > 0) {
				r[sq] |= SQUARE(sq + LEFT + UP);
			}
		}
	}
	return r;
}

Move* gen_moves(Board *board, int *number) {
	unsigned long mask;
	int from, to, me, you, capt, flip;
	unsigned char push, file, rank;
	Move *moves = (Move*) malloc(MAX_MOVES*sizeof(Move));
	*number = 0;
	me = to_play(board);
	you = 1 - me;
	
	/* these are just to get gcc to not give me warnings */
	to = 0;
	capt = NA;
	
	/* knight attacks */
	from = MSB(board->rank_positions[me*7 + KNIGHT], 0);
	while(from > 0) {
		
		mask = knight_attacks[from] & ~(board->rank_positions[me*7 + ALL]);
		to = MSB(mask, 0);
		while(to > 0) {
			capt = NA;
			if(board->rank_positions[you*7 + ALL] & SQUARE(to)) {
				if(board->rank_positions[you*7 + QUEEN] & SQUARE(to))
					capt = QUEEN;
				else if(board->rank_positions[you*7 + KING] & SQUARE(to))
					capt = KING;
				else if(board->rank_positions[you*7 + ROOK] & SQUARE(to))
					capt = ROOK;
				else if(board->rank_positions[you*7 + BISHOP] & SQUARE(to))
					capt = BISHOP;
				else if(board->rank_positions[you*7 + KNIGHT] & SQUARE(to))
					capt = KNIGHT;
				else if(board->rank_positions[you*7 + PAWN] & SQUARE(to))
					capt = PAWN;
			}
			move_set(&moves[(*number)++], from, to, KNIGHT, capt);
			to = MSB(mask, 64-to);
		}
		
		from = MSB(board->rank_positions[me*7 + KNIGHT], 64-from);
	}
	
	/* bishop attacks */
	
	
	/* queen attacks */
	
	
	/* rook attacks */
	from = MSB(board->rank_positions[me*7 + ROOK], 0);
	while(from > 0 && 0) {
		
		/* get the rank moves */
		mask = board->rank_positions[me*7 + ALL] | board->rank_positions[you*7 + ALL];
		rank = (unsigned char) (mask >> RANK(from));
		mask = rank_attacks[from*256 + rank];
		to = MSB(mask, 0);
		while(to > 0) {
			
			capt = NA;
			if(board->rank_positions[you*7 + ALL] & SQUARE(to)) {
				if(board->rank_positions[you*7 + QUEEN] & SQUARE(to))
					capt = QUEEN;
				else if(board->rank_positions[you*7 + KING] & SQUARE(to))
					capt = KING;
				else if(board->rank_positions[you*7 + ROOK] & SQUARE(to))
					capt = ROOK;
				else if(board->rank_positions[you*7 + BISHOP] & SQUARE(to))
					capt = BISHOP;
				else if(board->rank_positions[you*7 + KNIGHT] & SQUARE(to))
					capt = KNIGHT;
				else if(board->rank_positions[you*7 + PAWN] & SQUARE(to))
					capt = PAWN;
			}
			
			move_set(&moves[(*number)++], from, to, PAWN, capt);
			to = MSB(mask, 64-to);
		}
		
		/* get the file moves */
		mask = board->rank_positions[me*7 + ALL] | board->rank_positions[you*7 + ALL];
		file = (unsigned char) (mask >> FILE(from));
		mask = file_attacks[from*256 + file];
		to = MSB(mask, 0);
		while(to > 0) {
			
			capt = NA;
			if(board->rank_positions[you*7 + ALL] & SQUARE(to)) {
				if(board->rank_positions[you*7 + QUEEN] & SQUARE(to))
					capt = QUEEN;
				else if(board->rank_positions[you*7 + KING] & SQUARE(to))
					capt = KING;
				else if(board->rank_positions[you*7 + ROOK] & SQUARE(to))
					capt = ROOK;
				else if(board->rank_positions[you*7 + BISHOP] & SQUARE(to))
					capt = BISHOP;
				else if(board->rank_positions[you*7 + KNIGHT] & SQUARE(to))
					capt = KNIGHT;
				else if(board->rank_positions[you*7 + PAWN] & SQUARE(to))
					capt = PAWN;
			}
			
			move_set(&moves[(*number)++], from, to, PAWN, capt);
			to = MSB(mask, 64-to);
		}
		
		from = MSB(board->rank_positions[me*7 + ROOK], 0);
	}

	/* king attacks */
 	from = MSB(board->rank_positions[me*7 + KING], 0);
	mask = king_attacks[from] & ~(board->rank_positions[me*7 + ALL]);
	while(mask) {
		
		to = MSB(mask, 0);
		
		capt = NA;
		if(board->rank_positions[you*7 + ALL] & SQUARE(to)) {
			if(board->rank_positions[you*7 + QUEEN] & SQUARE(to))
				capt = QUEEN;
			else if(board->rank_positions[you*7 + KING] & SQUARE(to))
				capt = KING;
			else if(board->rank_positions[you*7 + ROOK] & SQUARE(to))
				capt = ROOK;
			else if(board->rank_positions[you*7 + BISHOP] & SQUARE(to))
				capt = BISHOP;
			else if(board->rank_positions[you*7 + KNIGHT] & SQUARE(to))
				capt = KNIGHT;
			else if(board->rank_positions[you*7 + PAWN] & SQUARE(to))
				capt = PAWN;
		}
		
		move_set(&moves[(*number)++], from, to, KING, capt);
		CLEAR(mask, to);
	}
	
	/* pawn attacks */
	if(me == WHITE) flip = 1;
	else flip = -1;
	from = MSB(board->rank_positions[me*7 + PAWN], 0);
	while(from > 0) {
		
		/* check captures */
		if((me == WHITE && RANK(from) < 7) || (me == BLACK && RANK(from) > 0)) {
			
			/* forward, left */
			to = from + UP*flip + LEFT;
			if(board->rank_positions[you*7 + ALL] & SQUARE(to)) {
				if(board->rank_positions[you*7 + QUEEN] & SQUARE(to))
					capt = QUEEN;
				else if(board->rank_positions[you*7 + KING] & SQUARE(to))
					capt = KING;
				else if(board->rank_positions[you*7 + ROOK] & SQUARE(to))
					capt = ROOK;
				else if(board->rank_positions[you*7 + BISHOP] & SQUARE(to))
					capt = BISHOP;
				else if(board->rank_positions[you*7 + KNIGHT] & SQUARE(to))
					capt = KNIGHT;
				else if(board->rank_positions[you*7 + PAWN] & SQUARE(to))
					capt = PAWN;
				
				move_set(&moves[(*number)++], from, to, PAWN, capt);
			}
			
			/* forward, right */
			to = from + UP*flip + RIGHT;
			if(board->rank_positions[you*7 + ALL] & SQUARE(to)) {
				if(board->rank_positions[you*7 + QUEEN] & SQUARE(to))
					capt = QUEEN;
				else if(board->rank_positions[you*7 + KING] & SQUARE(to))
					capt = KING;
				else if(board->rank_positions[you*7 + ROOK] & SQUARE(to))
					capt = ROOK;
				else if(board->rank_positions[you*7 + BISHOP] & SQUARE(to))
					capt = BISHOP;
				else if(board->rank_positions[you*7 + KNIGHT] & SQUARE(to))
					capt = KNIGHT;
				else if(board->rank_positions[you*7 + PAWN] & SQUARE(to))
					capt = PAWN;
				
				move_set(&moves[(*number)++], from, to, PAWN, capt);
			}
		}
		
		/* check single push */
		push = 0;
		to = from + UP*flip;
		if(to < 64 && to >= 0 && !(board->rank_positions[you*7 + ALL] & SQUARE(to))) {
			if((me == WHITE && RANK(from) == 1) || (me == BLACK && RANK(from) == 6))
				push = 1;
			move_set(&moves[(*number)++], from, to, PAWN, NA);
		}
		
		/* check double push */
		to = from + 2*UP*flip;
		if(push > 0 && to < 64 && to >= 0 &&
				!(board->rank_positions[you*7 + ALL] & SQUARE(to))) {
			move_set(&moves[(*number)++], from, to, PAWN, NA);
		}
		
		from = MSB(board->rank_positions[me*7 + PAWN], 64-from);
	}
	
	return moves;
}

void get_ready() {
	rank_attacks = make_rank_attacks();
	file_attacks = make_file_attacks();
	tl_br_attacks = make_tl_br_attacks();
	bl_tr_attacks = make_bl_tr_attacks();
	king_attacks = make_king_attacks();
	knight_attacks = make_knight_attacks();
}

void clean_up() {
	free(rank_attacks);
	free(file_attacks);
	free(tl_br_attacks);
	free(bl_tr_attacks);
	free(king_attacks);
	free(knight_attacks);
}

/* this will get replaced with ASM */
int MSB(long bits, int offset) {
	int i;
	for(i=(63-offset); i>=0; i--)
		if(bits & (1L << i))
			return i;
	return -1;
}




