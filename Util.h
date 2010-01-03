
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

void util_setup() {
	
	char r, f, i, width, tlbr, bltr;
	rf_to_tlbr = (int*) malloc(64*sizeof(int));
	rf_to_bltr = (int*) malloc(64*sizeof(int));
	
	tlbr_to_rf = (int*) malloc(64*sizeof(int));
	bltr_to_rf = (int*) malloc(64*sizeof(int));
	
	i = 0;
	/* top left of board, including diagnol */
	for(width=1; width<=8; width++) {
		for(f=0; f<width; f++) {
			r = 7 - (width - f - 1);
			
			/* this number is where the diagnol starts */
			tlbr = MAX(7-r, f)*(MAX(7-r, f)+1);
			
			rf_to_tlbr[(int) r*8+f] = (int) tlbr;
			tlbr_to_rf[(int) i] = (int) r*8+f;
			i++;
		}
	}
	/* bottom right of board, excluding diagnol */
	for(width=7; width>=0; width--) {
		for(f=0; f<width; f++) {
			r = width - (7-f) - 1;
			
			/* this number is where the diagnol starts */
			tlbr = 63 - MAX(7-f, r)*(MAX(7-f, r)+1);
			
			rf_to_tlbr[(int) r*8+f] = (int) tlbr;
			tlbr_to_rf[(int) i] = (int) r*8+f;
			i++;
		}
	}
	if(i != 64)
		printf("util_setup FAILED!\n");
		
	/* THESE TL_BR AND BL_TR NUMBERS NEED TO BE ROUNDED DOWN! */
		
	i = 0;
	/* bottom left of board, including diagnol */
	for(width=1; width<=8; width++) {
		for(f=0; f<width; f++) {
			r = width - f - 1;
			
			/* this number is where the diagnol starts */
			bltr = MAX(f, r)*(MAX(f, r)+1);
			
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
			bltr = 63 - MAX(7-f, 7-r)*(MAX(7-f, 7-r)+1);
			
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
}

/* this will get replaced with ASM */
int MSB(long bits, int offset) {
	int i;
	for(i=(63-offset); i>=0; i--)
		if(bits & (1L << i))
			return i;
	return -1;
}

