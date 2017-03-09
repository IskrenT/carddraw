/*  Software Name: carddraw 
*	Use: Calculate probability of drawing subset of items(cards) from a pool.
*   Copyright (C) 2017  Iskren Tarkalanov
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*	Contact: isktark@yahoo.com Iskren Tarkalanov
*/
#include "carddraw.h"

const double COMP_OVERFLOW_DBL = -1.0;
/// carddraw function - entry point for the general computation.
double carddraw(int total, int draw, int outs, int need, int only){
	double nominator = 0.0;
	double comb1, comb2, denom;

	// Covering all the false input cases with probability 0
	if(total<=0 || draw<=0 || outs<=0 || need<0 ||
		 need > total || need > draw || need > outs 
		)
		return 0.0;
	//Covering all the false input with probability 1
	if(draw > total || outs > total){
		if ( outs > need && only )//Covering case only==true but you draw whole deck.
			return 0.0;
		return 1.0;
	}
	//Special case. Complement event. Chance of not drawing any of the outs.
	if( need == 0 ){
		if(only){
			outs = total-outs;
			need = draw;
		}else{
			return 1.0;	// Chance of drawing atleast zero of the outs.
		}
	}
	//Denominator ( all combination of draws possible )
	denom = combination(total,draw);
	if( denom == COMP_OVERFLOW_DBL)
		return COMP_OVERFLOW_DBL;;

	//Computation of only=false executes only first time
	//Adding the events of drawing exactly x outs. ( x = "need+1" trough "outs" )
	//All combinations of 
	do{
		comb1 = combination(outs,need);
		comb2 = combination(total-outs, draw-need);
		nominator += comb1 * comb2;
	}while(++need<=draw && need <=outs && !only);
	return nominator/denom;
}
/// Combinations in combinatory mathematics.
double combination(int n, int k){
	double result = 1;
	int complement_k, ik, in;
	if( !k || k==n ) // one combination when k=0 or k==n
		return 1.0;
	if( !n || k>n ) //Zero combinations possible when: n=0 or k > n
		return 0.0;

	//n_C_k and n_C_(n-k) are the same, seek the least 'k'
	complement_k = n - k;
	if(complement_k < k ){
		k = complement_k;
		complement_k = n - k;
	}
	//Compute nominator and denominator and check for overflow after multiplication
	//Compiting both nominator and denominator in the same loop to delay overflow
	//Expresion is n_C_k = (n-k)!/k!
	for(ik = 2, in = n; in > complement_k; --in){
		result *= (double)in;
		if(!isfinite(result)) // if NaN - overflow
			return COMP_OVERFLOW_DBL;
		if(ik<=k)
		result /=(double)ik++;	
	}
	return result;
}
/// Produce the probability of the complement of the event. ( NOT EVENT )
double complement(double probability){
	return 1.0-probability;
}
#if defined _MSC_VER
  typedef unsigned __int64 uint64;
#else
  typedef uint64_t uint64;
#endif
int isfinite(double x)
{
    union { uint64 i; double d; } u;
    u.d = x;
    return ( (unsigned int)(u.i >> 32) & 0x7fffffff ) != 0x7ff00000;
}