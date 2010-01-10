
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
 */
int *rf_to_tlbr;
int *rf_to_bltr;

/* these are for determining the start of a diagnol */
int *rf_to_tlbr_start;
int *rf_to_bltr_start;

/* should be self explanitory... */
int *rf_to_tlbr_width;
int *rf_to_bltr_width;

void util_setup(void) {
	
	char r, f, i, width, tlbr, bltr;
	rf_to_tlbr_start = (int*) malloc(64*sizeof(int));
	rf_to_bltr_start = (int*) malloc(64*sizeof(int));
	
	tlbr_to_rf = (int*) malloc(64*sizeof(int));
	bltr_to_rf = (int*) malloc(64*sizeof(int));
	
	rf_to_tlbr = (int*) malloc(64*sizeof(int));
	rf_to_bltr = (int*) malloc(64*sizeof(int));
	
	rf_to_tlbr_width = (int*) malloc(64*sizeof(int));
	rf_to_bltr_width = (int*) malloc(64*sizeof(int));
	
	/* TL_BR */
	i = 0;
	/* top left of board, including diagnol */
	for(width=1; width<=8; width++) {
		for(f=0; f<width; f++) {
			
			r = 7 - (width - f - 1);
			
			/* this number is where the diagnol starts */
			tlbr = width*(width-1)/2;
			
			rf_to_tlbr_width[(int) r*8+f] = width;
			rf_to_tlbr_start[(int) r*8+f] = (int) tlbr;
			tlbr_to_rf[(int) i] = (int) r*8+f;
			rf_to_tlbr[(int) r*8+f]  = i;
			i++;
		}
	}
	/* bottom right of board, excluding diagnol */
	for(width=7; width>=0; width--) {
		for(f=(8-width); f<8; f++) {
			r = f - (8-width);
			
			/* this number is where the diagnol starts */
			tlbr = 64 - (width*(width-1)/2 + width);
			
			rf_to_tlbr_width[(int) r*8+f] = width;
			rf_to_tlbr_start[(int) r*8+f] = (int) tlbr;
			tlbr_to_rf[(int) i] = (int) r*8+f;
			rf_to_tlbr[(int) r*8+f]  = i;
			i++;
		}
	}
	if(i != 64)
		printf("util_setup FAILED!\n");
	
	
	/* for now, assume none of this works, just work on tl_br */
	/* BL_TR */
	i = 0;
	/* bottom left of board, including diagnol */
	for(width=1; width<=8; width++) {
		for(f=0; f<width; f++) {
			r = width - f - 1;
			
			/* this number is where the diagnol starts */
			bltr = width*(width-1)/2;
			
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
			bltr = 64 - (width*(width-1)/2 + width);
			
			rf_to_bltr_width[(int) r*8+f] = width;
			rf_to_bltr[(int) r*8+f] = (int) bltr;
			bltr_to_rf[(int) i] = (int) r*8+f;
			i++;
		}
	}
	if(i != 64)
		printf("util_setup FAILED!\n");
}

void util_cleanup(void) {
	free(tlbr_to_rf);
	free(rf_to_tlbr);
	free(rf_to_tlbr_start);
	free(rf_to_bltr_start);
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

