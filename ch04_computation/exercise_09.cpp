/*
Exponential grains of rice on chessboard - doubles per square, starting with a single grain on first square.

Try to calculate the number of grains the inventor asked for, total (64 squares on chess board.)
You'll find the number is so large it won't fit into an int, or a double.

Observe what happens when the number gets too large to represent exactly as an int and as a double.

What is the larget number of squares for which you can calculate the exact number of grains using...
- an int?
- a double?
*/

#include<iostream>
#include<cmath>
using namespace std;

int main() {


    // INTEGERS: highest square for which we can represent is square 31 (30 if it's 0-indexed).
    // Value = 1_073_741_824 and cumulative grains of rice = 2_147_483_647
    // My computer (64-bit OS) uses 4-byte integers.  Therefore, largest signed int is
    //  = (2^(4 bytes))/2 - 1
    //  = (2^(32 bits))/2 - 1
    //  =  2^31 - 1
    //  = 2_147_483_647
    //
    // Smallest signed int is
    //  = -(2^31)  (since we subtracted 1 from the top range, to leave room for the 0)
    //  = -2_147_483_648
    //
    //
    // Is there a way to know whether my processor uses 2's complement to store integers, or sign-magnitude?
    // Both would have the same expressable range of integers for N bits.
    //
    /*
    [sq 0] 1  |  1
	[sq 1] 2  |  3
	[sq 2] 4  |  7
	[sq 3] 8  |  15
	[sq 4] 16  |  31
	[sq 5] 32  |  63
	[sq 6] 64  |  127
	[sq 7] 128  |  255
	[sq 8] 256  |  511
	[sq 9] 512  |  1023
	[sq 10] 1024  |  2047
	[sq 11] 2048  |  4095
	[sq 12] 4096  |  8191
	[sq 13] 8192  |  16383
	[sq 14] 16384  |  32767
	[sq 15] 32768  |  65535
	[sq 16] 65536  |  131071
	[sq 17] 131072  |  262143
	[sq 18] 262144  |  524287
	[sq 19] 524288  |  1048575
	[sq 20] 1048576  |  2097151
	[sq 21] 2097152  |  4194303
	[sq 22] 4194304  |  8388607
	[sq 23] 8388608  |  16777215
	[sq 24] 16777216  |  33554431
	[sq 25] 33554432  |  67108863
	[sq 26] 67108864  |  134217727
	[sq 27] 134217728  |  268435455
	[sq 28] 268435456  |  536870911
	[sq 29] 536870912  |  1073741823
	[sq 30] 1073741824  |  2147483647
	[sq 31] -2147483648  |  -1              < from here, error!  2^31 is too large.  Is this an "underflow" for a signed 32-bit integer?  At least it's consistent (2147483647 + -2147483648 = -1)
	[sq 32] -2147483648  |  2147483647      < although -- if our running total from prev square was -1, how is -1 + -2147483648 = +2147483647?  Is this "overflow" for signed 32-bit integer?
	[sq 33] -2147483648  |  -1
	[sq 34] -2147483648  |  2147483647
	[sq 35] -2147483648  |  -1
	[sq 36] -2147483648  |  2147483647
	[sq 37] -2147483648  |  -1
	[sq 38] -2147483648  |  2147483647
	[sq 39] -2147483648  |  -1
	[sq 40] -2147483648  |  2147483647
	[sq 41] -2147483648  |  -1
	[sq 42] -2147483648  |  2147483647
	[sq 43] -2147483648  |  -1
	[sq 44] -2147483648  |  2147483647
	[sq 45] -2147483648  |  -1
	[sq 46] -2147483648  |  2147483647
	[sq 47] -2147483648  |  -1
	[sq 48] -2147483648  |  2147483647
	[sq 49] -2147483648  |  -1
	[sq 50] -2147483648  |  2147483647
	[sq 51] -2147483648  |  -1
	[sq 52] -2147483648  |  2147483647
	[sq 53] -2147483648  |  -1
	[sq 54] -2147483648  |  2147483647
	[sq 55] -2147483648  |  -1
	[sq 56] -2147483648  |  2147483647
	[sq 57] -2147483648  |  -1
	[sq 58] -2147483648  |  2147483647
	[sq 59] -2147483648  |  -1
	[sq 60] -2147483648  |  2147483647
	[sq 61] -2147483648  |  -1
	[sq 62] -2147483648  |  2147483647
	[sq 63] -2147483648  |  -1
    */
    cout << "--------------------------------\n"
         << "Integers:\n";
    int int_total_grains_of_rice = 0;
    int int_current_square_grains_of_rice = 0;
    for(int square=0; square<64; ++square){
        int_current_square_grains_of_rice = pow(2, square);
        int_total_grains_of_rice += int_current_square_grains_of_rice;
        cout << "\t[sq " << square << "] " << int_current_square_grains_of_rice << "  |  " << int_total_grains_of_rice << "\n";
    }


    // DOUBLES: it seems to be able to calculate all the way up to square 64?
    // The numbers are monotonically increasing, at the very least.
    // The total calculated number of rice grains (18_446_744_073_709_551_616)   << This isn't right.  We are off by 1, according to wikipedia.
    //                                                                              The test below doesn't work, either, both are stuck at _616.
    /*
    https://en.cppreference.com/w/cpp/language/types
    https://en.wikipedia.org/wiki/Double-precision_floating-point_format
    https://en.wikipedia.org/wiki/IEEE_754-2008_revision

    Number of grains for each square:
        I'm pretty sure that these can be exactly represented by a double?

        If we set the significand/fraction to 0 and only use the implicit leading "1" and the exponent,
        we can express 1*[2^0, 2^1023].

        Checked against Wolfram Alpha -- subtracted my 2^63 from theirs and got an error of 0!
        (https://www.wolframalpha.com/examples/mathematics/numbers/arbitrary-precision - uses arbitrary precision).

    Total number of grains, up to and including n^th sqare:
        This is where the error is introduced.  The total number of grains up to and including n^th square
        can be expressed as a summation from i=0->n, summing 2^i and is equivalent to 2^(n+1) - 1.

        This value is NOT a power of 2 and will experience loss of precision with n >= 52.

    [sq 0] 1  |  1
	[sq 1] 2  |  3
	[sq 2] 4  |  7
	[sq 3] 8  |  15
	[sq 4] 16  |  31
	[sq 5] 32  |  63
	[sq 6] 64  |  127
	[sq 7] 128  |  255
	[sq 8] 256  |  511
	[sq 9] 512  |  1023
	[sq 10] 1024  |  2047
	[sq 11] 2048  |  4095
	[sq 12] 4096  |  8191
	[sq 13] 8192  |  16383
	[sq 14] 16384  |  32767
	[sq 15] 32768  |  65535
	[sq 16] 65536  |  131071
	[sq 17] 131072  |  262143
	[sq 18] 262144  |  524287
	[sq 19] 524288  |  1048575
	[sq 20] 1048576  |  2097151
	[sq 21] 2097152  |  4194303
	[sq 22] 4194304  |  8388607
	[sq 23] 8388608  |  16777215
	[sq 24] 16777216  |  33554431
	[sq 25] 33554432  |  67108863
	[sq 26] 67108864  |  134217727
	[sq 27] 134217728  |  268435455
	[sq 28] 268435456  |  536870911
	[sq 29] 536870912  |  1073741823
	[sq 30] 1073741824  |  2147483647
	[sq 31] 2147483648  |  4294967295
	[sq 32] 4294967296  |  8589934591
	[sq 33] 8589934592  |  17179869183
	[sq 34] 17179869184  |  34359738367
	[sq 35] 34359738368  |  68719476735
	[sq 36] 68719476736  |  137438953471
	[sq 37] 137438953472  |  274877906943
	[sq 38] 274877906944  |  549755813887
	[sq 39] 549755813888  |  1099511627775
	[sq 40] 1099511627776  |  2199023255551
	[sq 41] 2199023255552  |  4398046511103
	[sq 42] 4398046511104  |  8796093022207
	[sq 43] 8796093022208  |  17592186044415
	[sq 44] 17592186044416  |  35184372088831
	[sq 45] 35184372088832  |  70368744177663
	[sq 46] 70368744177664  |  140737488355327
	[sq 47] 140737488355328  |  281474976710655
	[sq 48] 281474976710656  |  562949953421311
	[sq 49] 562949953421312  |  1125899906842623
	[sq 50] 1125899906842624  |  2251799813685247
	[sq 51] 2251799813685248  |  4503599627370495
	[sq 52] 4503599627370496  |  9007199254740991      < largest expressable 2^n - 1 in a double (binary64), since the range [2^52, 2^53) has a resolution of 1 (exactly the integers) in binary64
	[sq 53] 9007199254740992  |  18014398509481984         -1 away from (2^54 - 1)    < it's just 2^54!
	[sq 54] 18014398509481984  |  36028797018963968        -1 away from (2^55 - 1)    < it's just 2^55!
	[sq 55] 36028797018963968  |  72057594037927936            ...
	[sq 56] 72057594037927936  |  144115188075855872
	[sq 57] 144115188075855872  |  288230376151711744
	[sq 58] 288230376151711744  |  576460752303423488
	[sq 59] 576460752303423488  |  1152921504606846976
	[sq 60] 1152921504606846976  |  2305843009213693952
	[sq 61] 2305843009213693952  |  4611686018427387904
	[sq 62] 4611686018427387904  |  9223372036854775808
	[sq 63] 9223372036854775808  |  18446744073709551616   -1 away from (2^64 - 1)    < it's just 2^63!

    In the event of calculating a value unexpressable in a floating point number due to error (such as 2^54 - 1),
    I assumed that the value would be "floored" to the closest expressable value.

    So, for n being the square (such as square 53, first square with a sum that can't be accurately expressed),
    I thought that the value stored in the double would be
        = exponent=53, fraction=111...1_2 (52 1s in significand)
        = (2^n  - 1)*(2^( n-52))
        = (2^53 - 1)*(2^(53-52))
        = 18_014_398_509_481_982
    However, the value is instead
        = 18_014_398_509_481_984.  The REAL answer is 18_ ... _983, so both are off by 1, but the answer I got back was instead
        = 2^54
        = exponent=54, fraction=000...0_2 (52 0s in significand)

    In the case of n=53, either answer is equally erroneous, but as n increases, that is not the case.

    For n = 63 (my assumption)
        = (2^53 - 1)*(2^( n-52))
        = (2^53 - 1)*(2^(63-52))
        = (2^53 - 1)*(2^11)
        = 18_446_744_073_709_549_568
    vs what I got out:
        = 18_446_744_073_709_551_616

    Difference: 2048 (2^11), which is the same exponent in the assumption.

    Question -- how does the hardware know which to use (all 1s in significand w/ same exponent, or all 0s in significand w/ exponent n+1)
    */

    cout << "--------------------------------\n"
         << "Doubles:\n"
         << fixed;     // this makes the doubles show up as actual numbers, not in scientific notation
    cout.precision(0); // this makes the doubles have no decimal numbers (0 digits of precision).

    double dbl_total_grains_of_rice = 0;
    double dbl_current_square_grains_of_rice = 0;
    for(int square=0; square<64; ++square){
        dbl_current_square_grains_of_rice = pow(2, square);
        dbl_total_grains_of_rice += dbl_current_square_grains_of_rice;
        cout << "\t[sq " << square << "] " << dbl_current_square_grains_of_rice << "  |  " << dbl_total_grains_of_rice << "\n";
    }

    // ind  9_223_372_036_854_775_808
    // sum 18_446_744_073_709_551_616

    // Hmm - the result of the two computations below is the same... that doesn't sound right?
    // EDIT: figured out why after reading wikipedia article on double-precision floating point numbers.
    double test = pow(2, 64);
    double testminus1 = pow(2, 64) - 1;
    cout << "2^64 - 1 = " << testminus1 << "\n";
    cout << "2^64     = " << test       << "\n";


    return 0;
}
