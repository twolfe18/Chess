
/* see if i can incorporate this into
 * make_tl_br_attacks
 */
int get_tl_br_diag(int rank, int file) {
	int width;
	if(rank >= file) {
		width = (7-rank) + file + 1;
	}
	else {
		width = rank + (7-file) + 1;
	}
	return width*(width-1);
}

/* this method is almost the complement of get_tl_br_diag() */
int tl_br_to_rank_file(int tl_br, int *rank, int *file) {
	char r, f, i;
	unsigned char rf_to_tlbr[8][8];
	unsigned char tlbr_to_rf[64];
	i = 0;
	for(r=7; r>=0; r--) {
		for(f=0; f<8; f++) {
			rf_to_tlbr[(int)r][(int)f] = i;
			tlbr_to_rf[(int) i++] = r*8 + f;
		}
	}
	return 0;
	/* now you can convert either way by looking at the array */
}

/* this will get replaced with ASM */
int MSB(long bits, int offset) {
	int i;
	for(i=(63-offset); i>=0; i--)
		if(bits & (1L << i))
			return i;
	return -1;
}

