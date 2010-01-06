
#include <stdlib.h>
#include <stdio.h>

#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

/* this array is for getting the rank*8+file number
 * given the tl_br number
 */
int *tlbr_to_rf;
int *bltr_to_rf;

/* this array is for getting the tl_br diagnol
 * given the rank*8+file number
 *
 * notice, this is not the exact square, it is
 * beginning of the diagnol
 */
int *rf_to_tlbr;
int *rf_to_bltr;

int *rf_to_tlbr_width;
int *rf_to_bltr_width;

void util_setup() {
	
	char r, f, i, width, tlbr, bltr;
	rf_to_tlbr = (int*) malloc(64*sizeof(int));
	rf_to_bltr = (int*) malloc(64*sizeof(int));
	
	tlbr_to_rf = (int*) malloc(64*sizeof(int));
	bltr_to_rf = (int*) malloc(64*sizeof(int));
	
	rf_to_tlbr_width = (int*) malloc(64*sizeof(int));
	rf_to_bltr_width = (int*) malloc(64*sizeof(int));
	
	i = 0;
	/* top left of board, including diagnol */
	for(width=1; width<=8; width++) {
		for(f=0; f<width; f++) {
			r = 7 - (width - f - 1);
			
			/* this number is where the diagnol starts */
			tlbr = ((7-r)+f+1)*((7-r)+f+1) - ((7-r)+f+1);
			
			rf_to_tlbr_width[(int) r*8+f] = width;
			rf_to_tlbr[(int) r*8+f] = (int) tlbr;
			tlbr_to_rf[(int) i] = (int) r*8+f;
			i++;
		}
	}
	/* bottom right of board, excluding diagnol */
	for(width=7; width>=0; width--) {
		for(f=(8-width); f<8; f++) {
			r = f - (8-width);
			
			/* this number is where the diagnol starts */
			tlbr = 64 - ((r+(7-f)+1)*(r+(7-f)+1) - (r+(7-f)+1));
			
			rf_to_tlbr_width[(int) r*8+f] = width;
			rf_to_tlbr[(int) r*8+f] = (int) tlbr;
			tlbr_to_rf[(int) i] = (int) r*8+f;
			i++;
		}
	}
	if(i != 64)
		printf("util_setup FAILED!\n");
			
	i = 0;
	/* bottom left of board, including diagnol */
	for(width=1; width<=8; width++) {
		for(f=0; f<width; f++) {
			r = width - f - 1;
			
			/* this number is where the diagnol starts */
			bltr = (r+f+1)*(r+f+1) - (r+f+1);
			
			rf_to_bltr_width[(int) r*8+f] = width;
			rf_to_bltr[(int) r*8+f] = (int) bltr;
			bltr_to_rf[(int) i] = (int) r*8+f;
			i++;
		}
	}
	/* top right of board, excluding diagnol */
	for(width=7; width>=0; width--) {
		for(f=0; f<width; f++) {
			r = 7 - (width - (7-f) - 1);
			
			/* this number is where the diagnol starts */
			bltr = 64 - (((7-r)+(7-f)+1)*((7-r)+(7-f)+1) - ((7-r)+(7-f)+1));
			
			rf_to_bltr_width[(int) r*8+f] = width;
			rf_to_bltr[(int) r*8+f] = (int) bltr;
			bltr_to_rf[(int) i] = (int) r*8+f;
			i++;
		}
	}
	if(i != 64)
		printf("util_setup FAILED!\n");
}

void util_cleanup() {
	free(tlbr_to_rf);
	free(rf_to_tlbr);
	free(rf_to_tlbr_width);
	free(rf_to_bltr_width);
}

/* this will get replaced with ASM */
int MSB(long bits, int offset) {
	int i;
	for(i=(63-offset); i>=0; i--)
		if(bits & (1L << i))
			return i;
	return -1;
}

