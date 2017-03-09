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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "carddraw.h"
#ifndef HIT_ANY_KEY
#define HIT_ANY_KEY(store) while(1){ if(_kbhit()) break; _sleep(50);}; store=_getch()
#endif
int main(int argc, char *argv[]){ // cardraw 30 2 15
	int total, outs, draw, need, only;
	char only_string[10]="True";
	int scanf_retval;
	char key;
	double probability=1.0;
	if ( argc == 6 ){
		if(probability == COMP_OVERFLOW_DBL){
				printf("ERROR: Computational overflow please use smaller values!\n");
				probability = 1.0;
			}else 
				printf("result:%3.8f%%\n", probability*100+0.000000004);
		goto _next_carddraw;
	}
	printf("----------------------------------cardraw------------------------------------\n");
	printf(" Computes the probability of drawing [""only"" or ""at least""]\n");  
	printf(" ""need"" number of cards from ""outs"", as ""outs"" is a subset of ""total"".\n");
	printf("Input ( Integers ) separated by ' ' ( interval ):\n");
	printf("""total""- Total number of cards or items.\n");
	printf("""draw"" - Number of draws. ( Available or drawn, depending on use )\n");
	printf("""outs"" - Number of useful cards or items.\n");
	printf("""need"" - Number of needed cards or items within the useful ones.\n");
	printf("""only"" - True  - probability of drawing only the needed ones.\n");
	printf("		   False - probability of drawing at least the needed ones.\n");
	printf("Result: The computed probability in '%%' with 4 digit percision");
	printf("\n");
	printf("Arguments: ""total"" ""draw"" ""outs"" ""need"" ""only"" \n");
//	printf("Hit:|'n'-new entry|'m'-multiply new to last|'c'-complementary event|any to exit|\n");
	do{
		printf("\n|total| |outs| |draw| |need| |only|: ");
		scanf_retval = scanf("%d %d %d %d %s", &total, &outs, &draw, &need, &only_string );
		if(scanf_retval==5){
			only = 1;
			if(!strcmp(only_string,"False")||!strcmp(only_string,"false")||!strcmp(only_string,"0"))
				only = 0;
			probability *= carddraw( total, outs, draw, need, only );
			if(probability == COMP_OVERFLOW_DBL){
				printf("ERROR: Computational overflow please use smaller values!\n");
				probability = 1.0;
			}else 
				printf("result:%3.8f%%\n", probability*100+0.000000004);
		}
_next_carddraw:
		printf("\nHit:|'n'-new entry|'m'-multiply new to last|'c'-complementary event|any to exit|\n");
		HIT_ANY_KEY(key);
		if(key=='c'){
			probability = 1 - probability;
			printf("result:%3.8f%%\n", probability*100+0.000000004);
			goto _next_carddraw;
		}
		if(key=='n')
			probability = 1;
	}while(key=='n'||key=='m');
	return 0;
};