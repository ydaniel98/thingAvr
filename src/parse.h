//
//  parse.h
//
//
//  Created by Edwin Daniel  Penalo on 11/2/15.
//
//

#ifndef parse_h
#define parse_h

uint8_t parseInt(int n, uint8_t *p);					// Sets the list with all the digits from the input num
uint8_t parseIntHelper(int n, uint8_t *p, int pos);	// Helper function for parseInt



uint8_t parseInt(int n, uint8_t *p) {
	return parseIntHelper(n, p, 0);
}

uint8_t parseIntHelper(int n, uint8_t *p, int pos) {
	if (n < 10) {
		p[pos] = n;
		return pos;
	}
	p[pos] = n % 10;
	return parseIntHelper((n -p[pos]) / 10, p, pos + 1);
}


#endif /* parse_h */