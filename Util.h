
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

void util_setup(void);

void util_cleanup(void);

/* this will get replaced with ASM */
int MSB(long bits, int offset);
