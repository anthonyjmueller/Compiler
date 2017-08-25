#include<stdlib.h>
#include<stdio.h>
#include<string.h>


#include "linkedlist.h"

struct ReserveWord* ReserveWordListCreator(){
    char readingBuff[75];
    struct ReserveWord *head = NULL;
    struct ReserveWord *tail = NULL;
    int arrayPos;

    //create reserve word list from file
    FILE *reserveFile = fopen("Reserve_word_list.txt", "r");

    //create reserve word file
    while(fgets(readingBuff, 75, reserveFile) != NULL){//loop through file
        arrayPos = 0;

        if(!head){
            head = malloc(sizeof(struct ReserveWord));
            ReserveWordInit(head);
            tail = head;
        } else
        {
            struct ReserveWord *temp = malloc(sizeof(struct ReserveWord));
            ReserveWordInit(temp);
            (*tail).next = temp;
            tail = (*tail).next;
        }

        //get current Reserve word
        char currResWord[10];
        int i;
        for(i = 0; i < 10; i++){
            currResWord[i] = NULL;
        }
        int count = 0;

        while(readingBuff[arrayPos] != 32 && readingBuff[arrayPos] != 9){
            //printf("here");
            currResWord[count] = readingBuff[arrayPos];
            arrayPos++;
            count++;
        }

        strncpy((*tail).resWord, currResWord, 10);
        //printf(currResWord);
        //printf((*tail).resWord);

        while(readingBuff[arrayPos] == 32 || readingBuff[arrayPos] == 9){//skip white space
            arrayPos++;
        }

        //get current token
        char currTok[10];
        for(i = 0; i < 10; i++){
            currTok[i] = NULL;
        }
        count = 0;

        while(readingBuff[arrayPos] != 32 && readingBuff[arrayPos] != 9){
            currTok[count] = readingBuff[arrayPos];
            arrayPos++;
            count++;
        }

        strncpy((*tail).token,currTok, 10);

        while(readingBuff[arrayPos] == 32 || readingBuff[arrayPos] == 9){//skip white space
            arrayPos++;
        }

        //get current attribute
        if(readingBuff[arrayPos] == 110 || readingBuff[arrayPos] == 78){
            (*tail).atribute = NULL;
        }
        else{
            (*tail).atribute = readingBuff[arrayPos] - 48;
        }

     }

     fclose(reserveFile);

    return  head;
};

void ReserveWordInit(struct ReserveWord *temp){
    (*temp).next = NULL;
};

void SymbolTableInit(struct SymbolTable *temp){
    (*temp).next = NULL;
};

void TokenReturnInit(struct TokenReturn *temp){
    (*temp).token = 0;
    (*temp).atribute = NULL;
};

