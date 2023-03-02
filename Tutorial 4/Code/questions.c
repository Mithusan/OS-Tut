/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

//Colours
#define BLUE "\x1B[34m"
#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define YELLOW "\x1B[33m"
#define CYAN "\x1B[36m"
#define reset "\e[0m"

//Array of Questions
question questions[NUM_QUESTIONS] = {
	{"Science", "What is hardest natural substance on Earth?", "Diamond", 100, false},
	{"Geography", "What is the largest country in the world?", "Russia", 100, false},
	{"History", "When is the first World war started", "1914", 100, false},
	
	{"Science", "The concept of Gravity was discovered by which famous physicist?", "Isaac Newton", 200, false},
	{"Geography", "What country has the most fresh water?", "Canada", 200, false},
	{"History", "Where is the first Summer Olympics held?", "Athens Greece", 200, false},
	
	{"Science", "Which is the most abundant element in the universe?", "Hydrogen", 300, false},
	{"Geography", "How many provinces in Canada?", "10", 300, false},
	{"History", "Where is the home country of Joan of Arc?", "France", 300, false},
	
	{"Science", "What is a material that will not carry an electrical charge called?", "Insulator", 400, false},
	{"Geography", "This northeast African river flows for more than 4,100 miles?", "Nile River", 400, false},
	{"History", "Julius Caesar is born in which city?", "Rome", 400, false},
	
	{"Science", "These Substance control the rates of chemical reactions?", "Catalysts", 500, false},
	{"Geography", "How many countries in Africa?", "54", 500, false},
	{"History", "Who was the first ruler of the Mongol Empire?", "Genghis Khan", 500, false},
	
};

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void){
    printf("\t=========================================\n");
    printf("\t| Science   |   Geography   |   History |\n");
    printf("\t=========================================\n");
    for(int i=0; i <NUM_QUESTIONS; i++){
        if((questions[i].answered == false)){
            printf("\t   %s%i\t%s", YELLOW, questions[i].value, reset);
        }
        else {
            printf("\t   ---\t");
        }
        if ((i+1) % 3==0) {
                printf("\n");
            }

    }
    printf("\t=========================================\n\n");
}

// Displays the question for the category and dollar value
void display_question(char *category, int value){
    	for(int i=0; i < NUM_QUESTIONS; i++){
    		if(strcmp(questions[i].category, category) == 0 && questions[i].value == value){
    			printf("%s%s%s\n", GREEN, questions[i].question,reset);
    		}
    	}
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer){
    // Look into string comparison functions
    for(int i=0; i < NUM_QUESTIONS; i++){
    		if(strcmp(questions[i].category, category) == 0 && questions[i].value == value){
    			if(strcmp(questions[i].answer, answer) == 0){
    				return true;
    				break;
    			}
    			else{
    				return false;
    			}
    		}
    }
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value){
    // lookup the question and see if it's already been marked as answered
    for(int i=0; i < NUM_QUESTIONS; i++){
    	if(strcmp(questions[i].category, category) == 0 && questions[i].value == value){
    		return questions[i].answered;
    	}
    }
    
    return true;
}

bool remove_question(char *category, int value){
	for(int i=0; i < NUM_QUESTIONS; i++){
    		if(strcmp(questions[i].category, category) == 0 && questions[i].value == value){
    			questions[i].answered = true;
    			break;
    		}
    	}
}

bool check_if_finished(){
	for(int i=0; i < NUM_QUESTIONS; i++){
    		if(questions[i].answered == false){
    			return false;
    		}
    	}
    	return true;
}

