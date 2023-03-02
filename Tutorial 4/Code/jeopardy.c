/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "questions.c"
#include "players.c"
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

//Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

//Colours
#define BLUE "\x1B[34m"
#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define YELLOW "\x1B[33m"
#define CYAN "\x1B[36m"
#define reset "\e[0m"

char *tokens[MAX_LEN];
int tokencount = 0;

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenizer(char *answer){
	int i = 0;
	char *p = strtok (answer, " ");
	
	while (p != NULL){
		tokens[i++] = p;
		p = strtok(NULL, " ");
	}
	tokencount = i;
}

char* concat(const char *a,const char *b){ //can combined/concat two strings a and b
	char*res=malloc(strlen(a)+strlen(b));  //first we make a var for the result
	strcpy(res,a);                           // then the first string will be copied into the result
	strcat(res,b);                           // and then second string is concatenated into the result

	return res;
}

int main(int argc, char *argv[]){
	//WELCOME MESSAGE
	printf("******************************************************\n\n");
	printf("                 WELCOME TO JEOPARDY!\n\n");
	printf("******************************************************\n\n");
	    
	    
	//--------------------------------------------------------------------------------------------------
	//PLAYER SETUP
	// An array of 4 players, may need to be a pointer if you want it set dynamically
	player players[NUM_PLAYERS] = {{"empty", 0}, {"empty", 0}, {"empty", 0}, {"empty", 0}};
	    
	// Input buffer and and commands
	char buffer[BUFFER_LEN] = { 0 };
	
	// Prompt for players names
	for (int i=0; i < NUM_PLAYERS; i++){
	    // initialize each of the players in the array
	    printf("%sEnter Player %i Name: %s", GREEN, i+1, reset);
	    scanf("%s", players[i].name);
	    	    
	    //Score Each Player Starts with
	    players[i].score = 0;
	}
	
	
	//--------------------------------------------------------------------------------------------------
	//GAME INITIALIZATION
	// Perform an infinite loop getting command input from users until game ends
	while (fgets(buffer, BUFFER_LEN, stdin) != NULL){
		system("clear");
		
		//VARIABLES
		char selected_player[MAX_LEN];
		char selected_category[MAX_LEN];
		int selected_price;
		char answer[MAX_LEN];
		
		//DISPLAY CATEGORIES & POINTS
		display_categories();
		
		for(int i=0; i < NUM_PLAYERS; i++){
			printf("\t\t       %s - $%d \n", players[i].name, players[i].score);
		}
			
		printf("\n-------------------------------------------------------\n");
		
		//GAME EXECUTION
	    	//Selecting a Player
	    	do{
			printf("%sSelect a Player for this Round: %s", GREEN, reset);
		    	scanf("%s", (char *) &selected_player);
		    	
		    	if(player_exists(players, NUM_PLAYERS, selected_player) == false){
		    		printf("%sError! Player Does not Exist!%s\n\n", RED, reset);
		    	}
	    	}
	    	while (player_exists(players, NUM_PLAYERS, selected_player) == false);
	    	
	    	//Selecting Category & Price
	    	do{
	    		printf("%sPlease Select a Category: %s", GREEN, reset);
	    		scanf("%s", (char *) &selected_category);
	    		
	    		printf("%sAnd Please Select a Price: %s", GREEN, reset);
	    		scanf("%d", (int *) &selected_price);
	    		
	    		if(already_answered(selected_category, selected_price) == true){
	    			printf("%sError! Please Select a Category & Price that have not already been Selected!\n\n%s", RED, reset);
	    		}
	    		else{
	    			printf("\n\n%sQuestion has been Selected%s\n", CYAN, reset);
	    			sleep(2);
	    		}
	    	}
	    	while (already_answered(selected_category, selected_price) == true);
	    	
	    	system("clear");
	    	
	    	//Display Question
	    	display_question(selected_category, selected_price); 
	    	printf("*********************************************");
	    	
	    	//OBTAIN ANSWER
		printf("\n%sEnter your Answer: %s", CYAN, reset);
		getchar();
		scanf("%[^\n]s", answer);
		
		tokenizer(answer);//String Tokenization - Seperates String to Grab Command and its Argument
		
		//path is a string based on all the user inputs/ tokens
		char* path;
		path="";
		for (int i = 2; i < tokencount; i++) {
			if(i!=1 && i!=2){	
		        	path=concat(path," ");
		        }
		        path=concat(path,tokens[i]);
		}
		
	    	//Check answer
	    	if(strcmp(tokens[0], "Who") == 0 || strcmp(tokens[0], "What") == 0){
	    		if(strcmp(tokens[1], "is") == 0){
			    	if(valid_answer(selected_category, selected_price, path) == true){
			    		printf("\n\n%sYou are Correct!\nGood Job, You have been awarded%s %s$%d%s", GREEN, reset, YELLOW, selected_price,reset);
			    		update_score(players, NUM_PLAYERS, selected_player, selected_price);
			    		remove_question(selected_category, selected_price);
			    	}
			    	else{
			    		printf("\n\n%sYou are Incorrect!%s\nNo points have been awarded", RED, reset);
			    		remove_question(selected_category, selected_price); 
			    	}
			}
		}
		else{
			printf("\n\n%sIncorrect Format!%s\nNo points have been awarded", RED, reset);
			remove_question(selected_category, selected_price); 
		}
	    	
	    	printf("\n\n\nPress Enter to Continue ...");
	    	getchar();
	    	
	    	if (check_if_finished() == true){
	    		break;
	    	}
	}
	//Game Ends and Shows Final Standings and Winner
	system("clear");
	printf("The Game Has Ended!\nHere are the Final Scores ... \n\n");
	
	for(int i=0; i < NUM_PLAYERS; i++){
		printf("%s - %s$%d %s\n", players[i].name, YELLOW, players[i].score, reset);
	}
	
	
	highest_score(players, NUM_PLAYERS);
	
	return EXIT_SUCCESS;
}
