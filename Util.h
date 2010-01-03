
#include <stdlib.h>

#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

/* this array is for getting the rank*8+file number
 * given the tl_br number
 */
static int *tlbr_to_rf;

/* this array is for getting the tl_br diagnol
 * given the rank*8+file number
 *
 * notice, this is not the exact square, it is
 * beginning of the diagnol
 */
static int *rf_to_tlbr;

void util_setup() {
	char r, f, i;
	rf_to_tlbr = (int*) malloc(64*sizeof(int));
	tlbr_to_rf = (int*) malloc(64*sizeof(int));
	i = 0;
	for(r=7; r>=0; r--) {
		for(f=0; f<8; f++) {
			rf_to_tlbr[(int) r*8+f] = i;
			tlbr_to_rf[(int) i++] = MAX(r,f)*(MAX(r,f)+1)/2;
		}
	}
}

void util_cleanup() {
	free(tlbr_to_rf);
	free(rf_to_tlbr);
}

/* this will get replaced with ASM */
int MSB(long bits, int offset) {
	int i;
	for(i=(63-offset); i>=0; i--)
		if(bits & (1L << i))
			return i;
	return -1;
}

