
#define MAX_MOVES 180

#define WHITE	0
#define BLACK	1

#define NA		7
#define KING	0
#define QUEEN	1
#define ROOK	2
#define BISHOP	3
#define KNIGHT	4
#define PAWN	5
#define ALL		6

#define UP		8
#define DOWN	-8
#define LEFT	-1
#define RIGHT	1

#define SQUARE(X) (1L << (X))
#define IS_ZERO(BITS, INDEX) ((BITS & 1<<INDEX) == 0)
#define CLEAR(bits, index) (bits &= ~(1L << index))
#define RANK(square) (((int)square/8))
#define FILE(square) ((square%8))

/* my rotated bitboard implementation: 
 * this is the struct that contains all
 * information needed to specify a board
 */
typedef struct {

	/* Note about "register"
	 * I tried some simple tests using
	 * register, it does not seem to
	 * help (it actually hurts a lot)
	 * Try adding this later if you
	 * think it can help.
	 */

	/* a length 12 array of longs
	 * each long is 64 bits for the board
	 * 
	 * board positions are indexed by rank
	 * from A1 (0), A2 (1), ..., to H8 (63)
	 */
	unsigned long rank_positions[14];

	/* same as above but positions are
	 * indexed by file from A1 (0),
	 * B1 (2), ..., H8 (63)
	 */
	unsigned long file_positions[14];

	/* this array is a diagnolized board
	 * where the numbering goes like:
	 * A8 (0), A7 (1), B8 (2), A6 (3),
	 * ..., B1 (63)
	 */
	unsigned long tl_br_positions[14];

	/* this array is a diagnolized board
	 * where the numbering goes like:
	 * A1 (0), A2 (1), B1 (2), A3 (3),
	 * ..., B8 (63)
	 */
	unsigned long bl_tr_positions[14];

	/* highest order bit is either WHITE or
	 BLACK, lowest 2 bytes are the ply */
	unsigned int ply_and_play;

	/* these arrays store the positions of the
	 * pieces. this is convenient for accessing
	 * the array of masks, eg:
	 * > knight_attacks[board->knights[WHITE + 0]]
	 * instead of:
	 * > FirstOne(board->rank_positions[WHITE*6 + KNIGHT])
	 * for the first white knight
	 * note: you cannot assume that if the lower
	 * piece is not present, that there aren't any
	 * of that piece on the board, you have to
	 * check each element in the array
	 * another eg:
	 * for(i=0; i<8; i++)
	 *    attacks |= pawn_attacks[board->pawns[WHITE*8 + i]];
	 *
	 * also, special note:
	 * in the event of promotions, i have only left room for
	 * each side to get 2 extra queens and 2 extra knights
	 * i chose this because the queen's abilities are a full
	 * superset of all pieces except the knight, so together
	 * they are the only pieces you could want.
	 * i may need to add the ability to get more than 2 though,
	 * but in any reasonable game, it will be over before
	 * either side gets 2 extra queens or rooks.
	 *
	 * how does this work with applying moves?
	 * say their is an attack to G2 (14)
	 * attacked = 14;
	 * for(i=0; i<8; i++)
	 *    if(board->pawns[WHITE*8 + i] == attacked)
	 *       board->pawns[WHITE*8 + i] = OFF_BOARD;
	 *
	 * is all of this BS worth avoiding the call to 
	 * FirstOne(bitmap) which could have to look at
	 * up to 64 bits?
	 * > initial decision: NO
	 */
	/* char pawns[16];
	char kings[2];
	char queens[6];
	char rooks[4];
	char knights[6];
	char bishops[4]; */

} Board;


/* Move needs to store from, to, capture type, promote type
 * should have a bunch of methods associted with it
 */
typedef struct {
	unsigned char from;
	unsigned char to;
	unsigned char moving_capturing;
} Move;


