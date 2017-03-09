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
// FILE: "carddraw.h" main header contains declarations of functions in "carddraw.c"
#ifndef CARDDRAW_H
#define CARDDRAW_H
/// carddraw function - entry point for the general computation.
/**
* All parameters must be positive integers representing cardinalities of
* the following sets and subsets: 
* (using 'A|>B' to present B being a subset of A)
*
* total|>outs|>need
* total|>draw
* 
* The following is true for the cardinalities:
* |total|>=|outs|>=|need|
* |total|>=|draw|>=|need|
*
* !!!CAUTION!!!
* Although most of the reasonable exeptions are handled,
* calling the function with arguments not following the rules above might
* result in unexpected behaviour.
* 
* @param[in] total	Total number of cards or items.
* @param[in] draw	Number of draws. ( Available or drawn, depending on use )
* @param[in] outs	Number of useful cards or items.
* @param[in] need	Number of needed cards or items within the useful ones.
* @param[in] only	True  = chance of drawing only the needed ones.
*					False = chance of drawing at least the needed ones.
* @return probability from 0.0 to 1.0 of the following event to occur:
*	Probabilistic event:
	Drawing [draw] number of cards from [total] cards in which:
	(when only = true ) there are exactly [need] number of cards from [outs]
	(when only = false) there are at least [need] number of cards from [outs]
*
*   This event can be used to predict probability of possession of certain
*	cards, probability of drawing certain cards. Or the outcome of a random
*	event, with some good outs. ( thinking of items instead of cards )
*/
double carddraw(int total, int draw, int outs, int need, int only);

/// Combinations in combinatory mathematics.
/**
* Simple but powerful implementation of finding combinations or binomial
* coefficients in combinatory mathematics.
* 
* The function is safe for overflow returns COMP_OVERFLOW_DBL = -1.0 
* 
* @param[in] n	Total cardinality of the set 'items'.
* @param[in] k	Total cardinality of the subset 'picked'.
*
* @return	The number of possible subsets with cardinality k 
*			within set with cardinality n.
*/
double combination(int n,int k);
/// Produce the probability of the complement of the event. ( NOT EVENT )
double complement(double probability);
/// Check if the argument is a finite real number.
int isfinite(double x);
/// Defined in carddraw.c
extern const double COMP_OVERFLOW_DBL; // const double COMP_OVERFLOW_DBL = -1.0;

#endif
