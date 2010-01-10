/* Travis Wolfe
 * December 2009
 */

#include "Board.h"
#include "Util.h"

#define VERBOSE 0

#define SQUARE(X) (1L << (X))
#define IS_ZERO(BITS, INDEX) ((BITS & 1<<INDEX) == 0)
#define CLEAR(bits, index) (bits &= ~(1L << index))
#define RANK(square) (((int)square/8))
#define FILE(square) ((square%8))

#define INITIAL_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

unsigned long *rank_attacks;
unsigned long *file_attacks;
unsigned long *tl_br_attacks;
unsigned long *bl_tr_attacks;
unsigned long *king_attacks;
unsigned long *knight_attacks;

/* these are defined in Util.h */
extern int *tlbr_to_rf;
extern int *bltr_to_rf;
extern int *rf_to_tlbr;
extern int *rf_to_bltr;
extern int *rf_to_tlbr_width;
extern int *rf_to_bltr_width;

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
		tl_br_sq = rf_to_tlbr[rank*8 + file];
		
		/* find the tl_br number 
		if(rank >= file) {
			t = MAX(7-rank, file);
			tl_br_sq = SQUARE(t*(t-1)/2 + file);
		}
		else {
			t = MAX(rank, 7-file);
			tl_br_sq = SQUARE(63 - (t*(t-1)/2 + 7-file));
		}*/
		
		/* find the bl_tr number */
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
											
	board->file_positions[WHITE*7 + ALL] = board->file_positions[WHITE*7 + KING]
											| board->file_positions[WHITE*7 + QUEEN]
											| board->file_positions[WHITE*7 + ROOK]
											| board->file_positions[WHITE*7 + BISHOP]
											| board->file_positions[WHITE*7 + KNIGHT]
											| board->file_positions[WHITE*7 + PAWN];
	board->file_positions[BLACK*7 + ALL] = board->file_positions[BLACK*7 + KING]
											| board->file_positions[BLACK*7 + QUEEN]
											| board->file_positions[BLACK*7 + ROOK]
											| board->file_positions[BLACK*7 + BISHOP]
											| board->file_positions[BLACK*7 + KNIGHT]
											| board->file_positions[BLACK*7 + PAWN];
											
	board->tl_br_positions[WHITE*7 + ALL] = board->tl_br_positions[WHITE*7 + KING]
											| board->tl_br_positions[WHITE*7 + QUEEN]
											| board->tl_br_positions[WHITE*7 + ROOK]
											| board->tl_br_positions[WHITE*7 + BISHOP]
											| board->tl_br_positions[WHITE*7 + KNIGHT]
											| board->tl_br_positions[WHITE*7 + PAWN];
	board->tl_br_positions[BLACK*7 + ALL] = board->tl_br_positions[BLACK*7 + KING]
											| board->tl_br_positions[BLACK*7 + QUEEN]
											| board->tl_br_positions[BLACK*7 + ROOK]
											| board->tl_br_positions[BLACK*7 + BISHOP]
											| board->tl_br_positions[BLACK*7 + KNIGHT]
											| board->tl_br_positions[BLACK*7 + PAWN];

	board->bl_tr_positions[WHITE*7 + ALL] = board->bl_tr_positions[WHITE*7 + KING]
											| board->bl_tr_positions[WHITE*7 + QUEEN]
											| board->bl_tr_positions[WHITE*7 + ROOK]
											| board->bl_tr_positions[WHITE*7 + BISHOP]
											| board->bl_tr_positions[WHITE*7 + KNIGHT]
											| board->bl_tr_positions[WHITE*7 + PAWN];						
	board->bl_tr_positions[BLACK*7 + ALL] = board->bl_tr_positions[BLACK*7 + KING]
											| board->bl_tr_positions[BLACK*7 + QUEEN]
											| board->bl_tr_positions[BLACK*7 + ROOK]
											| board->bl_tr_positions[BLACK*7 + BISHOP]
											| board->bl_tr_positions[BLACK*7 + KNIGHT]
											| board->bl_tr_positions[BLACK*7 + PAWN];
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

unsigned long* make_file_attacks(void) {
	
	/* note: the size of this lookup table can
	 * be cut by 75% by removing the 2 bits that
	 * signify the ends of the board. you can always
	 * move to them whether there is a piece there
	 * or not.
	 */
	
	int rank, file, i, j, k;
	unsigned long* r = (unsigned long*) malloc(64*256*sizeof(unsigned long));
	
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

unsigned long* make_rank_attacks(void) {
	
	/* note: the size of this lookup table can
	 * be cut by 75% by removing the 2 bits that
	 * signify the ends of the board. you can always
	 * move to them whether there is a piece there
	 * or not.
	 */
	
	int rank, file, i, j, k;
	unsigned long* r = (unsigned long*) malloc(64*256*sizeof(unsigned long));
	
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

unsigned long* make_tl_br_attacks(void) {
	
	int rank, file, width, i, j, sq, tlbr;
	unsigned long *r = (unsigned long*) malloc(64*256*sizeof(unsigned long));
	
	for(rank=0; rank<8; rank++) {
		for(file=0; file<8; file++) {
			
			/* for this rank, file the length of
			 * the diagnol is:
			 */
			if(rank >= file) {
				width = (7-rank) + file + 1;
				tlbr = width*(width-1)/2;
			}
			else {
				width = rank + (7-file) + 1;
				tlbr = 64 - (width*(width-1)/2 + width);
			}
			
			/* how you index is pretty much arbitrary
			 * since i have allocated a full 256 possiblities
			 * for each square. it would matter if i only used
			 * the space needed, but that is slightly more
			 * comlicated (maybe something for later versions)
			 * 
			 * so for convenience, i am going to use standard
			 * square indexing
			 */
			sq = rank*8 + file;
			
			/* make a set of bit masks for the
			 * 2^width configurations
			 */
			for(i = (1<<width) - 1; i>=0; i--) {
				
				/* this addressing system will work,
				 * but wont be space efficient
				 */
				r[sq*256 + i] = 0L;
				
				
				/* NOTE
				 * there is something wrong in this function, check
				 * it carefully before blaming another part of the
				 * program. i think it has something to do with
				 * using j as the offset for tlbr
				 */
				
				
				/* in configuration i, sq is at place file */
				j = file - 1;
				while(j >= 0 && ( (i & (1<<j)) == 0) ) {
					
					/* this doesn't work when on the bottom right of the board! */
					/* r[sq*256 + i] |= SQUARE(width*(width-1) + j); */
					r[sq*256 + i] |= SQUARE(tlbr + j);
					
					j--;
				}
				if(j >= 0) {
					r[sq*256 + i] |= SQUARE(tlbr + j);
				}
				
				j = file + 1;
				while(j < width && ( (i & (1<<j)) == 0) ) {
					r[sq*256 + i] |= SQUARE(tlbr + j);
					j++;
				}
				if(j < width) {
					r[sq*256 + i] |= SQUARE(tlbr + j);
				}			
			}
			
		}
	}
	return r;
}

unsigned long* make_bl_tr_attacks(void) {
	unsigned long *r = (unsigned long*) malloc(64*256*sizeof(unsigned long));
	
	/* TODO */
	
	return r;
}

unsigned long* make_knight_attacks(void) {
	
	int rank, file, sq;
	unsigned long *r = (unsigned long*) malloc(64*sizeof(unsigned long));
	
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

unsigned long* make_king_attacks(void) {
	
	int rank, file, sq;
	unsigned long *r = (unsigned long*) malloc(64*sizeof(unsigned long));
	
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
	Move *moves;
	unsigned long mask;
	int from, to, me, you, capt, flip, temp, width, debug;
	unsigned char push, file, rank, diag;
	
	printf("=========\n");
	
	moves = (Move*) malloc(MAX_MOVES*sizeof(Move));
	*number = 0;
	me = to_play(board);
	you = 1 - me;
	
	/* these are just to prevent gcc from giving me warnings */
	to = 0;
	capt = NA;
	diag = 0;
	mask = 0L;
	temp = 0;
	
	/* a random note on efficiency:
	 * it may be a good idea to iterate through
	 * all sliding pieces, when you come to one
	 * using MSB(), see if the bit is set in ROOK,
	 * BISHOP, or QUEEN. then add moves accordingly
	 *
	 * actually, this can be extended to all piece
	 * types
	 *
	 * now that i think of it, this is WAY more
	 * efficient than what i am doing now, it minimizes
	 * calls to MSB(). refactor when you get a chance
	 */
	
	/* KNIGHT MOVES */
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
			
			printf("N ");
			move_set(&moves[(*number)++], from, to, KNIGHT, capt);
			to = MSB(mask, 64-to);
		}
		
		from = MSB(board->rank_positions[me*7 + KNIGHT], 64-from);
	}

	/* BISHOP MOVES */
	from = MSB(board->rank_positions[me*7 + BISHOP], 0);
	while(from > 0) {
		
		debug = MSB(board->tl_br_positions[me*7 + BISHOP], 0);
		printf("\nBISHOP @ [%d, %d, %d]\n", from, debug, tlbr_to_rf[debug]);
		/* printf("SHIFTING BY %d <<<\n", rf_to_tlbr[from]); */
		
		/* tl_br moves */
		mask = board->tl_br_positions[me*7 + ALL] | board->tl_br_positions[you*7 + ALL];
		
		/* i can mask like this in my array, but not on the board */
		width = rf_to_tlbr_width[from];
		diag = (unsigned char) (mask >> rf_to_tlbr[from]) & ((1<<width) - 1);
		
		printf("width = %d, from = %d, rf_to_tlbr[from] = %d, tl_br diag = %d\n",
			width, from, rf_to_tlbr[from], (int) diag);
		
		
		mask = tl_br_attacks[from*256 + diag] & ~(board->tl_br_positions[me*7+ALL]);
		to = MSB(mask, 0);
		while(to > 0) {

			capt = NA;
			if(board->tl_br_positions[you*7 + ALL] & SQUARE(to)) {
				if(board->tl_br_positions[you*7 + QUEEN] & SQUARE(to))
					capt = QUEEN;
				else if(board->tl_br_positions[you*7 + KING] & SQUARE(to))
					capt = KING;
				else if(board->tl_br_positions[you*7 + ROOK] & SQUARE(to))
					capt = ROOK;
				else if(board->tl_br_positions[you*7 + BISHOP] & SQUARE(to))
					capt = BISHOP;
				else if(board->tl_br_positions[you*7 + KNIGHT] & SQUARE(to))
					capt = KNIGHT;
				else if(board->tl_br_positions[you*7 + PAWN] & SQUARE(to))
					capt = PAWN;
				else printf("\nFAIL!\tFAIL!\tFAIL!\tFAIL!\tFAIL!\tFAIL!\tFAIL!\n\n");
			}
			
			/* need to convert to: tl_br => rank*8+file */
			/* note: from is already in rank*8+file */
			temp = tlbr_to_rf[to];
			
			printf("Bt=>[%d,%d] ", (int) temp, (int) to);
			move_set(&moves[(*number)++], from, temp, BISHOP, capt);
			to = MSB(mask, 64-to);
		}
		
		from = MSB(board->rank_positions[me*7 + BISHOP], 64-from);
	}
	
	
	
	
	
	
	
	/* QUEEN MOVES */
	
	
	/* ROOK MOVES */
	from = MSB(board->rank_positions[me*7 + ROOK], 0);
	while(from > 0) {
		
		/* get the rank moves */
		mask = board->rank_positions[me*7 + ALL] | board->rank_positions[you*7 + ALL];
		rank = (unsigned char) (mask >> (RANK(from)*8));
		mask = rank_attacks[from*256 + rank] & ~(board->rank_positions[me*7 + ALL]);
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
			
			printf("Rr ");
			move_set(&moves[(*number)++], from, to, PAWN, capt);
			to = MSB(mask, 64-to);
		}
		
		/* get the file moves */
		mask = board->file_positions[me*7 + ALL] | board->file_positions[you*7 + ALL];
		file = (unsigned char) (mask >> (FILE(from)*8));
		mask = file_attacks[from*256 + file] & ~(board->rank_positions[me*7 + ALL]);
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
			
			printf("Rf ");
			move_set(&moves[(*number)++], from, to, PAWN, capt);
			to = MSB(mask, 64-to);
		}
		
		from = MSB(board->rank_positions[me*7 + ROOK], 64-from);
	}

	/* KING MOVES */
 	from = MSB(board->rank_positions[me*7 + KING], 0);
	mask = king_attacks[from] & ~(board->rank_positions[me*7 + ALL]);
	while(mask && from > 0) { /* TODO: from > 0 condition is unnecessary in
							   * real game play, just for testing */
		
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
		
		printf("K ");
		move_set(&moves[(*number)++], from, to, KING, capt);
		CLEAR(mask, to);
	}
	
	/* PAWN MOVES */
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
				
				printf("Pcl ");
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
				
				printf("Pcr ");
				move_set(&moves[(*number)++], from, to, PAWN, capt);
			}
		}
		
		/* check single push */
		push = 0;
		to = from + UP*flip;
		if(to < 64 && to >= 0 &&
			!(board->rank_positions[you*7 + ALL] & SQUARE(to)) &&
			!(board->rank_positions[me*7 + ALL] & SQUARE(to))) {
			if((me == WHITE && RANK(from) == 1) || (me == BLACK && RANK(from) == 6))
				push = 1;
				
			printf("P1 ");
			move_set(&moves[(*number)++], from, to, PAWN, NA);
		}
		
		/* check double push */
		to = from + 2*UP*flip;
		if(push > 0 && to < 64 && to >= 0 &&
				!(board->rank_positions[you*7 + ALL] & SQUARE(to)) &&
				!(board->rank_positions[me*7 + ALL] & SQUARE(to))) {
					
			printf("P2 ");
			move_set(&moves[(*number)++], from, to, PAWN, NA);
		}
		
		from = MSB(board->rank_positions[me*7 + PAWN], 64-from);
	}
	return moves;
}

void get_ready(void) {
	util_setup();
	rank_attacks = make_rank_attacks();
	file_attacks = make_file_attacks();
	tl_br_attacks = make_tl_br_attacks();
	bl_tr_attacks = make_bl_tr_attacks();
	king_attacks = make_king_attacks();
	knight_attacks = make_knight_attacks();
}

void clean_up(void) {
	util_cleanup();
	free(rank_attacks);
	free(file_attacks);
	free(tl_br_attacks);
	free(bl_tr_attacks);
	free(king_attacks);
	free(knight_attacks);
}





