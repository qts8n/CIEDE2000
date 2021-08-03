/*
 * CIEDE2000.c
 */

#include "CIEDE2000.h"

#include <math.h>

/*******************************************************************************
 * Conversions
 ******************************************************************************/
 
double deg2Rad(double deg)
{
	return deg * M_PI / 180.0;
}

double rad2Deg(double rad)
{
	return ((180.0 / M_PI) * rad);
}

/*******************************************************************************
 * CIEDE2000
 ******************************************************************************/

double CIEDE2000(double l1, double a1, double b1, double l2, double a2, double b2)
{
	/*
	 * Step 1 
	 */
	/* Equation 2 */
	double C1 = sqrt((a1 * a1) + (b1 * b1));
	double C2 = sqrt((a2 * a2) + (b2 * b2));
	/* Equation 3 */
	double barC = (C1 + C2) / 2.0;
	/* Equation 4 */
	double G = 0.5 * (1 - sqrt(pow(barC, 7) / (pow(barC, 7) + POW_25_TO_7)));
	/* Equation 5 */
	double a1Prime = (1.0 + G) * a1;
	double a2Prime = (1.0 + G) * a2;
	/* Equation 6 */
	double CPrime1 = sqrt((a1Prime * a1Prime) + (b1 * b1));
	double CPrime2 = sqrt((a2Prime * a2Prime) + (b2 * b2));
	/* Equation 7 */
	double hPrime1;
	if (b1 == 0 && a1Prime == 0) {
		hPrime1 = 0.0;
	} else {
		hPrime1 = atan2(b1, a1Prime);
		/* 
		 * This must be converted to a hue angle in degrees between 0 
		 * and 360 by addition of 2􏰏 to negative hue angles.
		 */
		if (hPrime1 < 0) hPrime1 += DEG_360_IN_RAD;
	}
	double hPrime2;
	if (b2 == 0 && a2Prime == 0) {
		hPrime2 = 0.0;
	} else {
		hPrime2 = atan2(b2, a2Prime);
		/* 
		 * This must be converted to a hue angle in degrees between 0 
		 * and 360 by addition of 2 to negative hue angles.
		 */
		if (hPrime2 < 0) hPrime2 += DEG_360_IN_RAD;
	}
	
	/*
	 * Step 2
	 */
	/* Equation 8 */
	double deltaLPrime = l2 - l1;
	/* Equation 9 */
	double deltaCPrime = CPrime2 - CPrime1;
	/* Equation 10 */
	double deltahPrime;
	double CPrimeProduct = CPrime1 * CPrime2;
	if (CPrimeProduct == 0) {
		deltahPrime = 0;
	} else {
		/* Avoid the fabs() call */
		deltahPrime = hPrime2 - hPrime1;
		if (deltahPrime < -DEG_180_IN_RAD) {
			deltahPrime += DEG_360_IN_RAD;
		} else if (deltahPrime > DEG_180_IN_RAD) {
			deltahPrime -= DEG_360_IN_RAD;
		}
	}
	/* Equation 11 */
	double deltaHPrime = 2.0 * sqrt(CPrimeProduct) * sin(deltahPrime / 2.0);
	
	/*
	 * Step 3
	 */
	/* Equation 12 */
	double barLPrime = (l1 + l2) / 2.0;
	/* Equation 13 */
	double barCPrime = (CPrime1 + CPrime2) / 2.0;
	/* Equation 14 */
	double barhPrime, hPrimeSum = hPrime1 + hPrime2;
	if (CPrime1 * CPrime2 == 0) {
		barhPrime = hPrimeSum;
	} else {
		if (fabs(hPrime1 - hPrime2) <= DEG_180_IN_RAD) {
			barhPrime = hPrimeSum / 2.0;
		} else {
			if (hPrimeSum < DEG_360_IN_RAD) {
				barhPrime = (hPrimeSum + DEG_360_IN_RAD) / 2.0;
			} else {
				barhPrime = (hPrimeSum - DEG_360_IN_RAD) / 2.0;
			}
		}
	}
	/* Equation 15 */
	double T = 1.0 - (0.17 * cos(barhPrime - deg2Rad(30.0))) +
	    (0.24 * cos(2.0 * barhPrime)) +
	    (0.32 * cos((3.0 * barhPrime) + deg2Rad(6.0))) - 
	    (0.20 * cos((4.0 * barhPrime) - deg2Rad(63.0)));
	/* Equation 16 */
	double deltaTheta = deg2Rad(30.0) *
	    exp(-pow((barhPrime - deg2Rad(275.0)) / deg2Rad(25.0), 2.0));
	/* Equation 17 */
	double R_C = 2.0 * sqrt(pow(barCPrime, 7.0) /
	    (pow(barCPrime, 7.0) + POW_25_TO_7));
	/* Equation 18 */
	double S_L = 1 + ((0.015 * pow(barLPrime - 50.0, 2.0)) /
	    sqrt(20 + pow(barLPrime - 50.0, 2.0)));
	/* Equation 19 */
	double S_C = 1 + (0.045 * barCPrime);
	/* Equation 20 */
	double S_H = 1 + (0.015 * barCPrime * T);
	/* Equation 21 */
	double R_T = (-sin(2.0 * deltaTheta)) * R_C;
	
	/* Equation 22 */
	return sqrt(
	    pow(deltaLPrime / (K_L * S_L), 2.0) +
	    pow(deltaCPrime / (K_C * S_C), 2.0) +
	    pow(deltaHPrime / (K_H * S_H), 2.0) + 
	    (R_T * (deltaCPrime / (K_C * S_C)) * (deltaHPrime / (K_H * S_H))));
}
