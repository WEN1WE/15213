/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    return (x >> (n << 3)) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    //return ~(((1 << n) + (~1 + 1)) << (32 + (~n + 1))) & (x >> n);
    int mask = ~(((0x1 << 31) >> n) << 1);
    return (x >> n) & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
 

// count half a time
int bitCount(int x) {
    int count, temp, mask1, mask2, mask3, mask4, mask5;

    temp = (0x55 << 8) + 0x55;
    mask1 = (temp << 16) + temp;   // mask1 = 0x55555555
    temp = (0x33 << 8) + 0x33;
    mask2 = (temp << 16) + temp;  // mask2 = 0x33333333
    temp = (0x0F << 8) + 0x0F;
    mask3 = (temp << 16) + temp; // mask3 = 0x0F0F0F0F
    temp = 0xFF;
    mask4 = (temp << 16) + temp; // mask4 = 0x00FF00FF
    mask5 = (temp << 8) + temp; //mask5 = 0x0000FFFF

    count = (x & mask1) + ((x >> 1) & mask1);
    count = (count & mask2) + ((count >> 2) & mask2);
    count = (count & mask3) + ((count >> 4) & mask3);
    count = (count & mask4) + ((count >> 8) & mask4);
    count = (count & mask5) + ((count >> 16) & mask5);

    return count;
}


// Another implement of bitCount 
int bitCount_2(int x) {
    int temp, mask1, mask2, mask3; 

    temp = (0x55 << 8) + 0x55;
    mask1 = (temp << 16) + temp;   // mask1 = 0x55555555
    temp = (0x33 << 8) + 0x33;
    mask2 = (temp << 16) + temp;  // mask2 = 0x33333333
    temp = (0x0F << 8) + 0x0F;
    mask3 = (temp << 16) + temp; // mask3 = 0x0F0F0F0F
    
    x = (x & mask1) + ((x >> 1) & mask1);
    x = (x & mask2) + ((x >> 2) & mask2);
    x = (x + (x >> 4)) & mask3;
    x = x + (x >> 8);
    x = x + (x >> 16);

    return x & 0x3F;

}
    
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */

// Divide-and-conquer
int bang(int x) {
	x = (x | x >> 1);
	x = (x | x >> 2);
	x = (x | x >> 4);
	x = (x | x >> 8);
	x = (x | x >> 16);
	x = x ^ 1;
	x = x & 1;

	return x;
}

// The most left bit of (x | -x) is 1 if x not 0.
int bang_2(int x) {
	return (~((x | (~x + 1)) >> 31) & 1);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
 	return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int shift;
	shift = 32 + (~n + 1);  // 32 - n
	return !(((x << shift) >> shift) ^ x);  // x will not change if it can be represented as an n - bit.
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	int bias;
	bias = (((x >> 31) & 1) << n) + (~1 + 1); // if x < 0 : bias = 2^n -1
	bias = bias + ((bias >> 31) & 1); // 
	x += bias;

	return x >> n;
}

int divpwr2_2(int x, int n) {
	int mask, bias;

	mask = x >> 31;
	bias = ((1 << n) + (~1) + 1) & mask;
	return (x + bias) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
 	return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	int sign1, sign2;

	sign1 = (x >> 31) & 1;
	sign2 = ((x | (~x + 1)) >> 31) & 1;

	return sign1 ^ sign2;
}

int isPositive_2(int x) {
 	return !((x >> 31) | (!x)); 
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	// four situations: + +, - +, + -, --
	int sign_x, sign_y, situation_1, situation_2, situation_3, sub;
	
	sign_x = (x >> 31) + 1;
	sign_y = (y >> 31) + 1;

	// situation : + - return 0
	situation_1 = (!sign_x) | sign_y;

	// situation : - + return 1
	situation_2 = (!sign_x) & sign_y;

	// situation -- and ++
	sub = y + (~x + 1);
	situation_3 = (sub >> 31) + 1;

	return situation_1 & (situation_2 | situation_3);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int middle = (0xFF << 8) + 0xFF;  // the middle of int
	int wight = 0;   
	int neg_x = ~x + 1;
	int diff_value, sign, mask;

	// left 32bit
	diff_value = middle + neg_x;
	sign = (diff_value >> 31) & 1;
	wight += sign << 4;
	mask = ~(diff_value >> 31);
	x = (x >> 16) + (x & mask);  // keep low 16 bits or not


	// left 16bit
	middle = middle >> 8;
	neg_x = ~x + 1;
	diff_value = middle + neg_x;
	sign = (diff_value >> 31) & 1;
	wight += sign << 3;
	mask = ~(diff_value >> 31);
	x = (x >> 8) + (x & mask);



	// left 8bit
	middle = middle >> 4;
	neg_x = ~x + 1;
	diff_value = middle + neg_x;
	sign = (diff_value >> 31) & 1;
	wight += sign << 2;
	mask = ~(diff_value >> 31);
	x = (x >> 4) + (x & mask);


	// left 4bit
	middle = middle >> 2;
	neg_x = ~x + 1;
	diff_value = middle + neg_x;
	sign = (diff_value >> 31) & 1;
	wight += sign << 1;
	mask = ~(diff_value >> 31);
	x = (x >> 2) + (x & mask);


	// left 2bit
	middle = middle >> 1;
	neg_x = ~x + 1;
	diff_value = middle + neg_x;
	sign = (diff_value >> 31) & 1;
	wight += sign << 0;

	return wight;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	int Tmin = 1 << 31;
	int mask = ~(Tmin >> 8);

	int exp = (uf >> 23) & 0xFF;
	int frac = (uf & mask);
	int neg_f = uf ^ Tmin;

	if ((exp == 255) && (frac != 0)) {
		return uf;
	}
	else {
		return neg_f;
	}
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	int E;
	int temp;
	int drop_bits;
	unsigned frac = 0;
	unsigned s = x & (1 << 31);

	if (x < 0) {
		x = -x;
	}
	else if (x == 0) {
		return 0;
	}
	temp = x;

	E = 158;
	while (x > 0) {
		E -= 1;
		x = x << 1;	
	}

	x = temp;
	drop_bits = E - 150;
	if (drop_bits > 0) {
		int carry = 1 << drop_bits;
		int frac_last = (x >> drop_bits) & 1;
		int drop = x & (carry - 1);
		int middle = carry >> 1;

		if ((drop > middle) || ((drop == middle) && (frac_last == 1))) {
			x += carry;
		}
	}

	E = 158;
	while (x > 0) {
		E -= 1;
		x = x << 1;
	}
	frac = x << 1;
	frac = frac >> 9;

	return s + (E << 23) + frac;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	unsigned exp = (uf >> 23) & 0xFF;
	unsigned frac = uf & 0x0007FFFF;
	if (exp == 0xFF){
		return uf;
	}
	else if (exp == 0) {
		if (frac == 0) {
			return uf;
		}
		else {
			return (uf << 1) + (uf & 0x80000000);
		}
	}
	return uf + (1 << 23);
}