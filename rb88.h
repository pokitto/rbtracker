#ifndef RB88_H
#define RB88_H

#ifdef WIN32
    #include <string>
    #include <cmath>
#else

#endif

#include "Rboy_math.h"

#define rb88Half (1 << 7) // 0.5 in rb88
#define rb88One (1 << 8) // 1 in rb88

// 0x4000 brad = π rad = 180 degrees
static const uint16_t BRAD_PI_SHIFT=14,   BRAD_PI = 1<<BRAD_PI_SHIFT;
static const uint16_t BRAD_HPI= BRAD_PI/2, BRAD_2PI= BRAD_PI*2;
static const uint16_t ATAN_ONE = 0x1000, ATAN_FP= 12;
//See more at: http://www.coranac.com/documents/arctangent/


inline int16_t rb88mul(int16_t a, int16_t b)
{
    return (int16_t)(((int32_t)a * b) >> 8);
}

inline int16_t rb88div(int16_t a, int16_t b)
{
	return (int16_t)((((int32_t)a) << 8) / b);
}



#define PI88 804
#define FLT_EPSILON88 float2rb88(1.19209290E-07F)



struct rb88 {
	int16_t intValue;
	rb88() {}
	// explicit casting different types
	//rb88(uint8_t i) : intValue(i << 8) {}
	rb88(int i) : intValue(i * 256) {}
	//rb88(uint16_t i) : intValue(i << 8) {}
	//rb88(int16_t i) : intValue(i * 256) {}
	rb88(float f) : intValue((int32_t)(f*256)) {}

    rb88& operator = (rb88 r) { intValue = r.intValue; return *this; }
	rb88& operator += (rb88 r) { intValue += r.intValue; return *this; }
	rb88& operator -= (rb88 r) { intValue -= r.intValue; return *this; }
	rb88& operator *= (rb88 r) { intValue = rb88mul(intValue, r.intValue); return *this; }
	rb88& operator /= (rb88 r) { intValue = rb88div(intValue, r.intValue); return *this; }

	rb88& operator *= (int16_t r) { intValue *= r; return *this; }
	rb88& operator /= (int16_t r) { intValue /= r; return *this; }

	rb88 operator - () const { rb88 x; x.intValue = -intValue; return x; }
	rb88 operator + (rb88 r) const { rb88 x = *this; x += r; return x;}
	rb88 operator - (rb88 r) const { rb88 x = *this; x -= r; return x;}
	rb88 operator * (rb88 r) const { rb88 x = *this; x *= r; return x;}
	rb88 operator / (rb88 r) const { rb88 x = *this; x /= r; return x;}

	bool operator == (rb88 r) const { return intValue == r.intValue; }
	bool operator != (rb88 r) const { return !(*this == r); }
	bool operator <  (rb88 r) const { return intValue < r.intValue; }
	bool operator >  (rb88 r) const { return intValue > r.intValue; }
	bool operator <= (rb88 r) const { return intValue <= r.intValue; }
	bool operator >= (rb88 r) const { return intValue >= r.intValue; }

	rb88 operator + (int16_t r) const { rb88 x = *this; x += r; return x;}
	rb88 operator - (int16_t r) const { rb88 x = *this; x -= r; return x;}
	rb88 operator * (int16_t r) const { rb88 x = *this; x *= r; return x;}
	rb88 operator / (int16_t r) const { rb88 x = *this; x /= r; return x;}
};

// Direct operations with integers !!!!!

inline rb88 float2rb88(float f)
{
    // return (int32_t)(f * (1 << p));
	int32_t temp = f*256;
	rb88 t88;
	t88.intValue = (int16_t) temp;
	//return (int16_t)(f * (1 << 8));
	return t88;
}

inline rb14 rb88to14(rb88 m)
{
	return m.intValue << 6;
}

inline rb88 rb14to88(rb14 m)
{
    rb88 a;
    a.intValue = m >> 6;
	return a;
}

inline rb88 operator + (int8_t a, rb88 b)
{ return b + rb88(a); }
inline rb88 operator + (int16_t a, rb88 b)
{ return b + a * 256; } // Discards high 8 bits !


inline rb88 operator - (int8_t a, rb88 b)
{ return -b + a; }
inline rb88 operator - (int16_t a, rb88 b)
{ return -b + a * 256; }


inline rb88 operator * (int8_t a, rb88 b)
{ return b * a; }
inline rb88 operator * (int16_t a, rb88 b)
{ return b * a; }


inline rb88 operator / (int8_t a, rb88 b)
{ rb88 r(a); r /= b; return r; }
inline rb88 operator / (int16_t a, rb88 b)
{ rb88 r(a); r /= b; return r; }


inline int8_t rb882int (rb88 a)
{
    return a.intValue >>8;
}

inline uint8_t rb88fract (rb88 a)
{
    return a.intValue & 0xFF;
}

inline float rb882float(rb88 f)
{
	return (float) f.intValue / (1 << 8);
}

inline uint32_t sqrt(uint32_t a)
{
    int32_t x;
    int i;
    if (a==0) return 0;
    /* THIS IS THE BABYLONIAN METHOD !*/
    x = a + (1<<16); // x = a + 256*256
    x >>= 8; // x is initial guess
    for (i = 0; i < 10; i++)
		x = (x + (a/x)) >> 1;
    return x;
}

inline rb88 sqrt(rb88 a)
{
    int32_t x;
    int i;
    if (a.intValue == 0 ) return 0;
    x = (a.intValue+256) >> 1; // original 16 bit version
    for (i = 0; i < 6; i++)
		x = (x + (a.intValue/x)) >> 1; /* 8 iterations to converge */
    a.intValue = (int16_t)x * 16; // to get rb88 answer
    return a;
}

inline rb88 fabs(rb88 a)
{
	rb88 r;
	r.intValue = a.intValue > 0 ? a.intValue : -a.intValue;
	return r;
}

static const int16_t sin_tab[] = {
0x0000,   /* 0 rad, 0 deg */
0x023C,   /* 0.01745 rad, 1 deg */
0x0478,   /* 0.03490 rad, 2 deg */
0x06B3,   /* 0.05235 rad, 3 deg */
0x08EE,   /* 0.06981 rad, 4 deg */
0x0B28,   /* 0.08726 rad, 5 deg */
0x0D61,   /* 0.10471 rad, 6 deg */
0x0F99,   /* 0.12217 rad, 7 deg */
0x11D0,   /* 0.13962 rad, 8 deg */
0x1406,   /* 0.15707 rad, 9 deg 0x1406*/
0x163A,   /* 0.17453 rad, 10 deg */
0x186C,   /* 0.19198 rad, 11 deg */
0x1A9D,   /* 0.20943 rad, 12 deg */
0x1CCB,   /* 0.22689 rad, 13 deg */
0x1EF7,   /* 0.24434 rad, 14 deg */
0x2121,   /* 0.26179 rad, 15 deg */
0x2348,   /* 0.27925 rad, 16 deg */
0x256C,   /* 0.29670 rad, 17 deg */
0x278E,   /* 0.31415 rad, 18 deg */
0x29AC,   /* 0.33161 rad, 19 deg */
0x2BC7,   /* 0.34906 rad, 20 deg */
0x2DDF,   /* 0.36651 rad, 21 deg */
0x2FF3,   /* 0.38397 rad, 22 deg */
0x3203,   /* 0.40142 rad, 23 deg */
0x3410,   /* 0.41887 rad, 24 deg */
0x3618,   /* 0.43633 rad, 25 deg */
0x381C,   /* 0.45378 rad, 26 deg */
0x3A1C,   /* 0.47123 rad, 27 deg */
0x3C17,   /* 0.48869 rad, 28 deg */
0x3E0E,   /* 0.50614 rad, 29 deg */
0x4000,   /* 0.52359 rad, 30 deg */
0x41EC,   /* 0.54105 rad, 31 deg */
0x43D4,   /* 0.55850 rad, 32 deg */
0x45B6,   /* 0.57595 rad, 33 deg */
0x4793,   /* 0.59341 rad, 34 deg */
0x496A,   /* 0.61086 rad, 35 deg */
0x4B3C,   /* 0.62831 rad, 36 deg */
0x4D08,   /* 0.64577 rad, 37 deg */
0x4ECD,   /* 0.66322 rad, 38 deg */
0x508D,   /* 0.68067 rad, 39 deg */
0x5246,   /* 0.69813 rad, 40 deg */
0x53F9,   /* 0.71558 rad, 41 deg */
0x55A5,   /* 0.73303 rad, 42 deg */
0x574B,   /* 0.75049 rad, 43 deg */
0x58EA,   /* 0.76794 rad, 44 deg */
0x5A82,   /* 0.78539 rad, 45 deg */
0x5C13,   /* 0.80285 rad, 46 deg */
0x5D9C,   /* 0.82030 rad, 47 deg */
0x5F1F,   /* 0.83775 rad, 48 deg */
0x609A,   /* 0.85521 rad, 49 deg */
0x620D,   /* 0.87266 rad, 50 deg */
0x6379,   /* 0.89011 rad, 51 deg */
0x64DD,   /* 0.90757 rad, 52 deg */
0x6639,   /* 0.92502 rad, 53 deg */
0x678D,   /* 0.94247 rad, 54 deg */
0x68D9,   /* 0.95993 rad, 55 deg */
0x6A1D,   /* 0.97738 rad, 56 deg */
0x6B59,   /* 0.99483 rad, 57 deg */
0x6C8C,   /* 1.01229 rad, 58 deg */
0x6DB7,   /* 1.02974 rad, 59 deg */
0x6ED9,   /* 1.04719 rad, 60 deg */
0x6FF3,   /* 1.06465 rad, 61 deg */
0x7104,   /* 1.08210 rad, 62 deg */
0x720C,   /* 1.09955 rad, 63 deg */
0x730B,   /* 1.11701 rad, 64 deg */
0x7401,   /* 1.13446 rad, 65 deg */
0x74EE,   /* 1.15191 rad, 66 deg */
0x75D2,   /* 1.16937 rad, 67 deg */
0x76AD,   /* 1.18682 rad, 68 deg */
0x777F,   /* 1.20427 rad, 69 deg */
0x7847,   /* 1.22173 rad, 70 deg */
0x7906,   /* 1.23918 rad, 71 deg */
0x79BB,   /* 1.25663 rad, 72 deg */
0x7A67,   /* 1.27409 rad, 73 deg */
0x7B0A,   /* 1.29154 rad, 74 deg */
0x7BA2,   /* 1.30899 rad, 75 deg */
0x7C32,   /* 1.32645 rad, 76 deg */
0x7CB7,   /* 1.34390 rad, 77 deg */
0x7D33,   /* 1.36135 rad, 78 deg */
0x7DA5,   /* 1.37881 rad, 79 deg */
0x7E0D,   /* 1.39626 rad, 80 deg */
0x7E6C,   /* 1.41371 rad, 81 deg 0x1406*/
0x7EC0,   /* 1.43116 rad, 82 deg */
0x7F0B,   /* 1.44862 rad, 83 deg */
0x7F4B,   /* 1.46607 rad, 84 deg */
0x7F82,   /* 1.48352 rad, 85 deg */
0x7FAF,   /* 1.50098 rad, 86 deg */
0x7FD2,   /* 1.51843 rad, 87 deg */
0x7FEB,   /* 1.53588 rad, 88 deg */
0x7FFA,   /* 1.55334 rad, 89 deg */
0x7FFF    /* 1.57079 rad, 90 deg */
};

/** func  quad   return       func  quad   return
    sin   1      table[n]     cos   1      table[l-n]
    sin   2      table[l-n]   cos   2      -table[n]
    sin   3      -table[n]    cos   3      -table[l-n]
    sin   4      -table[l-n]  cos   4      table[n]
    l = table length
*/

inline rb14 fxpsin (int16_t angle) {
    // angle comes in as an signed degree integer
    rb14 a;int16_t index;
    angle %= 360;
    if (angle<0) angle += 360;
    //if (angle >= 360) angle %= 360; // put angle in 0-360 range
    index = angle % 90; // put index in 1st quadrant
    // if angle = 90, index becomes 0
    if (angle == 90) return int2rb(1);
    if (angle == 180) return 0;
    if (angle == 270) return int2rb(-1);

    if (angle < 90) {
        //a.intValue = sin_tab[index] >> 7;
        a = sin_tab[index] >> 1; //rb14 value
        return a;
    } else if (angle < 180) {
        //a.intValue = sin_tab[90-index] >> 7 ; // returns 1 if angle =90
        a = sin_tab[90-index] >> 1 ;
        return a;
    } else if (angle < 270) {
        //a.intValue = -sin_tab[index] >> 7 ; // returns 0 if angle = 180
        a = -sin_tab[index] >> 1;
        return a;
    }
    //a.intValue = -sin_tab[89-index] >> 7 ; // returns -1 if angle = 270
    a = -sin_tab[90-index] >> 1;
    return a;
}

inline rb14 fxpcos (int16_t angle) {
    // angle comes in as an signed degree integer
    rb14 a;int16_t index;
    angle %= 360;
    if (angle<0) angle += 360;
    //if (angle >= 360) angle %= 360; // put angle in 0-360 range
    index = angle % 90; // put index in 1st quadrant
    // if angle = 90, index becomes 0
    if (angle == 0) return int2rb(1);
    if (angle == 90) return 0;
    if (angle == 180) return int2rb(-1);
    if (angle == 270) return 0;

    if (angle < 90) {
        //a.intValue = sin_tab[90-index] >> 7;
        a = sin_tab[90-index] >> 1;
        return a;
    } else if (angle < 180) {
        //a.intValue = -sin_tab[index] >> 7 ;
        a = -sin_tab[index] >> 1 ;
        return a;
    } else if (angle < 270) {
        //a.intValue = -sin_tab[90-index] >> 7 ;
        a = -sin_tab[90-index] >> 1 ;
        return a;
    }
    //a.intValue = sin_tab[index] >> 7 ;
    a = sin_tab[index] >> 1 ;
    return a;
}


// Get the octant a coordinate pair is in.
#define OCTANTIFY(_x, _y, _o)   do {                            \
    int _t; _o= 0;                                              \
    if(_y<  0)  {            _x= -_x;   _y= -_y; _o += 4; }     \
    if(_x<= 0)  { _t= _x;    _x=  _y;   _y= -_t; _o += 2; }     \
    if(_x<=_y)  { _t= _y-_x; _x= _x+_y; _y=  _t; _o += 1; }     \
    } while(0);

// QDIV stands for the fixed-point division method most appropriate for
// your system. Modify where appropriate.
// This would be for NDS.


static inline int QDIV(int32_t num, int16_t den, const int bits) {
    //while(REG_DIVCNT & DIV_BUSY);
    //REG_DIVCNT = DIV_64_32;
    //REG_DIV_NUMER = ((int64)num)<<bits;
    //REG_DIV_DENOM_L = den;
    //while(REG_DIVCNT & DIV_BUSY);
    //return (REG_DIV_RESULT_L);
    num <<= bits;
    num = num / den;
    return (int16_t) num;
}



// Approximate Taylor series for atan2, home-grown implementation.
// Returns [0,2pi), where pi ~ 0x4000.
//See more at: http://www.coranac.com/documents/arctangent/

inline uint16_t atan2Tonc(int x, int y) {
    if(y==0)    return (x>=0 ? 0 : BRAD_PI);
    static const int fixShift= 15;
    int  phi, t, t2, dphi;
    OCTANTIFY(x, y, phi);
    phi *= BRAD_PI/4;
    t= QDIV(y, x, fixShift);
    t2= -t*t>>fixShift;
    dphi= 0x0470;
    dphi= 0x1029 + (t2*dphi>>fixShift);
    dphi= 0x1F0B + (t2*dphi>>fixShift);
    dphi= 0x364C + (t2*dphi>>fixShift);
    dphi= 0xA2FC + (t2*dphi>>fixShift);
    dphi= dphi*t>>fixShift;
    return phi + ((dphi+4)>>3);
}
//See more at:
// http://www.coranac.com/documents/arctangent/#sthash.nDY5rqE1.dpuf



#endif // RB88_H

