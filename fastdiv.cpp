#include "fastdiv.h"

unsigned int fastdiv(unsigned int A, unsigned int Q) {
    // http://homepage.cs.uiowa.edu/~jones/bcd/divide.html
    switch (Q) {
    case 0:
        return 0;
    case 1:
        return A;
    case 2:
        return (A >> 1);
    case 3:
        /* approximate A/3 */
        Q = ((A >>  2) + A) >> 2; /* Q = A*0.0101 */
        Q = ((Q      ) + A) >> 1; /* Q = A*0.10101 */
        Q = ((Q >>  6) + Q)     ; /* Q = A*0.10101010101 */
        Q = ((Q >> 12) + Q) >> 1; /* Q = A*0.01010101010101010... */
        return Q;
        /* either Q = A/3 or Q+1 = A/3 for all A < 792,771 */
    case 4:
        return (A >> 2);
    case 5:
        /* approximate A/5 */
        Q = ((A >>  1) + A) >> 1; /* Q = A*0.11 */
        Q = ((Q >>  4) + Q)     ; /* Q = A*0.110011 */
        Q = ((Q >>  8) + Q) >> 2; /* Q = A*0.0011001100110011 */
        return Q;
        /* either Q = A/5 or Q+1 = A/5 for all A < 185,365 */
    case 6:
        /* approximate A/6 */
        Q = ((A >>  2) + A) >> 1; /* Q = A*0.101 */
        Q = ((Q >>  4) + Q)     ; /* Q = A*0.1010101 */
        Q = ((Q >>  8) + Q) >> 2; /* Q = A*0.00101010101010101 */
        return Q;
        /* either Q = A/6 or Q+1 = A/6 for all A < 222,438 */
    case 7:
        Q = ((A >>  3) + A) >> 1; /* Q = A*0.1001 */
        Q = ((Q >>  6) + Q)     ; /* Q = A*0.1001001001 */
        Q = ((Q >> 12) + Q) >> 2; /* Q = A*0.001001001001001001001001 */
        return Q;
        /* either Q = A/7 or Q+1 = A/7 for all A < 60,577,223 */
    case 8:
        return A >> 3;
    case 9:
        /* approximate A/9 */
        Q = ((A >>  1) + A) >> 1; /* Q = A*0.11 */
        Q = ((Q      ) + A) >> 1; /* Q = A*0.111 */
        Q = ((Q >>  6) + Q)     ; /* Q = A*0.111000111 */
        Q = ((Q >> 12) + Q) >> 3; /* Q = A*0.000111000111000111000111 */
        return Q;
        /* either Q = A/9 or Q+1 = A/9 for all A < 115,638,345 */
    case 10:
        /* approximate A/10 */
        Q = ((A >> 1) + A) >> 1; /* Q = A*0.11 */
        Q = ((Q >> 4) + Q)     ; /* Q = A*0.110011 */
        Q = ((Q >> 8) + Q) >> 3; /* Q = A*0.00011001100110011 */
        return Q;
        /* either Q = A/10 or Q+1 = A/10 for all A < 534,890 */
    case 11:
        /* approximate A/11 */
        Q = ((A >>  2) + A) >> 1; /* Q = A*0.101 */
        Q = ((Q      ) + A) >> 1; /* Q = A*0.1101 */
        Q = ((Q      ) + A) >> 2; /* Q = A*0.011101 */
        Q = ((Q      ) + A) >> 1; /* Q = A*0.1011101 */
        Q = ((Q >> 10) + Q) >> 3; /* Q = A*0.00010111010001011101 */
        return Q;
        /* either Q = A/11 or Q+1 = A/11 for all A < 10,103,819 */
    case 12:
        // Code for approximate division by 10, 12, 14, 18, 22, 26 and 30 can be derived from the code for
        // dividing by 5, 6, 7, 9, 11, 13 and 15 by incrementing the final shift count by one.
        Q = ((A >>  2) + A) >> 1; /* Q = A*0.101 */
        Q = ((Q >>  4) + Q)     ; /* Q = A*0.1010101 */
        Q = ((Q >>  8) + Q) >> 3; /* Q = A*0.00101010101010101 */
        return Q;
    case 13:
        /* approximate A/13 */
        Q = ((A >>  1) + A) >> 2; /* Q = A*0.011 */
        Q = ((Q      ) + A) >> 1; /* Q = A*0.1011 */
        Q = ((Q      ) + A) >> 1; /* Q = A*0.11011 */
        Q = ((Q      ) + A) >> 3; /* Q = A*0.00111011 */
        Q = ((Q      ) + A) >> 1; /* Q = A*0.100111011 */
        Q = ((Q >> 12) + Q) >> 3; /* Q = A*0.0001001110110001 ... */
        return Q;
        /* either Q = A/13 or Q+1 = A/13 for all A < 190,894,093 */
    case 14:
        Q = ((A >>  3) + A) >> 1; /* Q = A*0.1001 */
        Q = ((Q >>  6) + Q)     ; /* Q = A*0.1001001001 */
        Q = ((Q >> 12) + Q) >> 3; /* Q = A*0.001001001001001001001001 */
        return Q;
    case 15:
        /* approximate A/15 */
        Q = ((A >>  4) + A) >> 1; /* Q = A*0.10001 */
        Q = ((Q >>  8) + Q) >> 3; /* Q = A*0.0001000100010001 */
        return Q;
        /* either Q = A/15 or Q+1 = A/15 for all A < 864,015 */
    case 16:
        return A >> 4;
    default:
        /* Divisor is bigger than 16 */
        while (Q > 16) {
          Q >>= 1;
          A >>= 1;
        }
        Q = (fastdiv(A,Q) + fastdiv(A,Q+1)) >> 1;
        return Q ;
    }
    return 0;
}
