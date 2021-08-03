/*
 * CIEDE2000.h
 */
 
#ifndef GPF_CIEDE2000_H_
#define GPF_CIEDE2000_H_

#ifndef M_PI
#define M_PI 3.141592653589793   /* pi */
#endif

/*
 * "For these and all other numerical/graphical deltaE00 values
 * reported in this article, we set the parametric weighting factors
 * to unity (i.e., K_L = K_C = K_H = 1.0)." (Page 27).
 */

#ifndef K_L
#define K_L 1.0
#endif

#ifndef K_C
#define K_C 1.0
#endif

#ifndef K_H
#define K_H 1.0
#endif

#ifndef DEG_360_IN_RAD
#define DEG_360_IN_RAD 6.283185307179586
#endif

#ifndef DEG_180_IN_RAD
#define DEG_180_IN_RAD 3.141592653589793
#endif

#ifndef POW_25_TO_7
#define POW_25_TO_7 6103515625.0
#endif


/**
 * @brief
 * Obtain Delta-E 2000 value.
 * @details
 * Based on the paper "The CIEDE2000 Color-Difference Formula:
 * Implementation Notes, Supplementary Test Data, and Mathematical
 * Observations" by Gaurav Sharma, Wencheng Wu, and Edul N. Dalal,
 * from http://www.ece.rochester.edu/~gsharma/ciede2000/.
 *
 * @param l1
 * L component of the first color in LAB colorspace.
 * @param a1
 * a component of the first color in LAB colorspace.
 * @param b1
 * b component of the first color in LAB colorspace.
 * @param la
 * L component of the second color in LAB colorspace.
 * @param a2
 * a component of the second color in LAB colorspace.
 * @param b2
 * b component of the second color in LAB colorspace.
 *
 * @return
 * Delta-E difference between the first color and the second color.
 */
double CIEDE2000(double l1, double a1, double b1, double l2, double a2, double b2);

/***********************************************************************
 * Conversions.
 **********************************************************************/

/**
 * @brief
 * Convert degrees to radians.
 *
 * @param deg
 * Angle in degrees.
 *
 * @return
 * deg in radians.
 */
double deg2Rad(double deg);

/**
 * @brief
 * Convert radians to degrees.
 *
 * @param rad
 * Angle in radians.
 *
 * @return
 * rad in degrees.
 */
double rad2Deg(double rad);
    
#endif /* GPF_CIEDE2000_H_ */
