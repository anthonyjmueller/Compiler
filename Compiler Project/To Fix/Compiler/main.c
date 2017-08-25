#include <stdio.h>
#include <stdlib.h>

#define PROGRAM 260
#define ID 270
#define VAR 280
#define ARRAY 290
#define NUM 300
#define OF 310
#define INT 320
#define REAL 330
#define FUNCTION 340
#define PROCEDURE 350
#define BEGIN 360
#define END 370
#define ASSIGNOP 380
#define IF 390
#define THEN 400
#define ELSE 410
#define WHILE 420
#define DO 430
#define RELOP 440
#define EQU 441
#define NOTEQU  442
#define LESSTHN 443
#define LESSTHNEQU  444
#define GRTTHNEQU   445
#define GRTTHN  446

#define MULOP 450
#define MULT 451
#define DIVIDE 452
#define DIV 453
#define MOD 454
#define AND 455

#define ADDOP 460
#define PLUS 461
#define MINUS 462
#define OR 463

#define NOT 470
#define MYEOF 480
#define DOT 490
#define DOTDOT 500
#define COMA 510
#define LTPREN 520
#define SEMCOLN 530
#define COLN 540
#define LTBRK 550
#define RTBRK 560
#define LNREAL 570
#define RTPREN 580

#define LEXERR 1000
#define IDToLong 1001
#define IDISRESVWRD 1002
#define IDISUSED 1003
#define INTLEADZRO 1004
#define INTTOOLONG 1005
#define RLLEADZEO 1006
#define RLXTOLONG 1007
#define RLTRAILZEO 1008
#define RLYTOLONG 1009
#define LRLNOEXP 1010
#define LRLZTOLONG 1011
#define UNRECONIZEDSYMBOL 1012

char *backChr;
char *frontChr;
FILE *readPtr;
int front;
int back;
char currLine[72];
struct ReserveWord *startReserve;
struct SymbolTable *startSymbol;

struct TokenReturn {
    int token;
    int atribute;
};

struct ReserveWord {
    char resWord[10];
    char token[10];
    int atribute;
    struct ReserveWord *next;
};

void ReserveWordInit(struct ReserveWord *temp){
    (*temp).next = NULL;
};

struct SymbolTable {
    char name[10];
    struct SymbolTable *next;
};

void SymbolTableInit(struct SymbolTable *temp){
    (*temp).next = NULL;
}

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
            printf("here");
            currResWord[count] = readingBuff[arrayPos];
            arrayPos++;
            count++;
        }

        strncpy((*tail).resWord, currResWord, 10);
        printf(currResWord);
        printf((*tail).resWord);

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

struct TokenReturn getTok(){
//things needed : golbal current line, golbal next pointer, global back pointer
struct TokenReturn *toReturn;
toReturn = malloc(sizeof(struct TokenReturn));

int temp = checkWhiteSpace();
if(temp == -1){
    int i = 0;
    for (i = 0; i < 72; i++)
    {
        currLine[i] = NULL;
    }
    if(fgets(currLine, 72, readPtr) != NULL){
        front = 0;
        back = 0;
        return getTok();
    }else {
        (*toReturn).token = EOF;
        (*toReturn).atribute = NULL;
        return *toReturn;
    }
}

temp = checkRelop();
if(temp != -1){
    if(temp == 1){
       if(temp == 1){
        (*toReturn).token = RELOP;
        (*toReturn).atribute = EQU;
        return *toReturn;
        }
    }
    if(temp == 2){
       if(temp == 1){
        (*toReturn).token = RELOP;
        (*toReturn).atribute = NOTEQU;
        return *toReturn;
        }
    }
    if(temp == 3){
       if(temp == 1){
        (*toReturn).token = RELOP;
        (*toReturn).atribute = LESSTHN;
        return *toReturn;
        }
    }
    if(temp == 4){
       if(temp == 1){
        (*toReturn).token = RELOP;
        (*toReturn).atribute = LESSTHNEQU;
        return *toReturn;
        }
    }
    if(temp == 5){
       if(temp == 1){
        (*toReturn).token = RELOP;
        (*toReturn).atribute = GRTTHNEQU;
        return *toReturn;
        }
    }
    if(temp == 6){
       if(temp == 1){
        (*toReturn).token = RELOP;
        (*toReturn).atribute = GRTTHN;
        return *toReturn;
        }
    }
}

temp = checkIdRes();
if(temp != -1){
        if(temp == -2){
            (*toReturn).token = LEXERR;
            (*toReturn).atribute = IDToLong;
            return *toReturn;
        }
        if(temp == -3){
            (*toReturn).token = LEXERR;
            (*toReturn).atribute = IDISRESVWRD;
            return *toReturn;
        }
        if(temp == -4){
            (*toReturn).token = LEXERR;
            (*toReturn).atribute = IDISUSED;
            return *toReturn;
        }
    (*toReturn).token = ID;
    (*toReturn).atribute = NULL;
    return *toReturn;
}

temp = checkLongReal();
if(temp != -1){
    if(temp == -2){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLLEADZEO;
        return *toReturn;
    }
    if(temp == -3){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLXTOLONG;
        return *toReturn;
    }
    if(temp == -4){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLTRAILZEO;
        return *toReturn;
    }
    if(temp == -5){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLYTOLONG;
        return *toReturn;
    }
    if(temp == 1){
        (*toReturn).token = REAL;
        (*toReturn).atribute = NULL;
        return *toReturn;
    }
}

temp = checkReal();
if(temp != -1){
    if(temp == -2){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLLEADZEO;
        return *toReturn;
    }
    if(temp == -3){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLXTOLONG;
        return *toReturn;
    }
    if(temp == -4){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLTRAILZEO;
        return *toReturn;
    }
    if(temp == -5){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = RLYTOLONG;
        return *toReturn;
    }
    if(temp == -6){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = LRLNOEXP;
        return *toReturn;
    }
    if(temp == -7){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = LRLZTOLONG;
        return *toReturn;
    }
    if(temp == 1){
        (*toReturn).token = LNREAL;
        (*toReturn).atribute = NULL;
        return *toReturn;
    }
}

temp = checkInt();
if(temp != -1){
    if(temp == -2){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = INTLEADZRO;
        return *toReturn;
    }
    if(temp == -3){
        (*toReturn).token = LEXERR;
        (*toReturn).atribute = INTTOOLONG;
        return *toReturn;
    }
    if(temp == 1){
        (*toReturn).token = INT;
        (*toReturn).atribute = NULL;
        return *toReturn;
    }

}

temp = catchAll();
if(temp != -1){
       if(temp == 1){
        (*toReturn).token = ASSIGNOP;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
       if(temp == 2){
        (*toReturn).token = COLN;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
        if(temp == 3){
        (*toReturn).token = DOT;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
       if(temp == 4){
        (*toReturn).token = DOTDOT;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
        if(temp == 5){
        (*toReturn).token = ADDOP;
        (*toReturn).atribute = PLUS;
        return *toReturn;
        }
       if(temp == 6){
        (*toReturn).token = ADDOP;
        (*toReturn).atribute = MINUS;
        return *toReturn;
        }
        if(temp == 7){
        (*toReturn).token = COMA;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
       if(temp == 8){
        (*toReturn).token = LTPREN;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
        if(temp == 9){
        (*toReturn).token = RTPREN;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
       if(temp == 10){
        (*toReturn).token = SEMCOLN;
        (*toReturn).atribute = NULL;
        return *toReturn;
        }
        if(temp == 11){
        (*toReturn).token = LTBRK;
        (*toReturn).atribute = PLUS;
        return *toReturn;
        }
       if(temp == 12){
        (*toReturn).token = RTBRK;
        (*toReturn).atribute = MINUS;
        return *toReturn;
        }
        if(temp == 13){
        (*toReturn).token = MULOP;
        (*toReturn).atribute = MULT;
        return *toReturn;
        }
       if(temp == 14){
        (*toReturn).token = MULOP;
        (*toReturn).atribute = DIVIDE;
        return *toReturn;
        }
    }

(*toReturn).token = LEXERR;
(*toReturn).atribute = UNRECONIZEDSYMBOL;
return *toReturn;
};

/**
    Checks buffer to see if the next characters are white space
    returns -1 if the line has ended
    moves pointer and returns 0 if white space is found
*/
void checkWhiteSpace(){ //set forward pointer to -1 if need next line
    while(currLine[front] == 9 || currLine[front] == 32){
        front += 1;
    }
    if(currLine[front] == NULL){
        return -1;
    }else{
    back = front;
    }
    return 0;
}

void checkIdRes(){
    char currWord[10];
    int currIndex = 0;
    if(currLine[front] > 96 && currLine[front] < 123){
        front++;
        while((currLine[front] > 96 && currLine[front] < 123) || (currLine[front] < 58 && currLine[front] > 47) && currIndex < 10){
            front++;
        }

        if( front - back > 10){
            return -2;
        }

        while(back + currIndex < front){ //get word into array
            currWord[currIndex] = currLine[back + currIndex];
        }

        struct ReserveWord *temp = startReserve;//check if in reserve word file
        do{
            if(strcmp((*temp).resWord, currWord) == 0){
                return -3;
            }
        temp = (*temp).next;
        }while((*temp).next != NULL);
        if(strcmp((*temp).resWord, currWord) == 0){
                return -3;
        }

        struct SymbolTable *symtemp = startSymbol;//check /add to symbol table
        if(symtemp == NULL){
            startSymbol = malloc(sizeof(struct SymbolTable));
            SymbolTableInit(startSymbol);
            int i = 0;
            for( i = 0; i < 10; i++){
                (*startSymbol).name[i] = currWord[i];
            }
        }else{
            struct SymbolTable *oldEnd;
            do{
                if(strcmp((*symtemp).name, currWord) != 0){
                    return -4;
                }
                if((*symtemp).next != NULL){
                    symtemp = (*symtemp).next;
                }
                else{
                    oldEnd = symtemp;
                    symtemp == NULL;
                }
            } while(symtemp != NULL);
            symtemp = malloc(sizeof(struct SymbolTable));
            SymbolTableInit(symtemp);
            int j;
            for (j = 0; j < 10; j++){
                (*symtemp).name[j] = currWord[j];
            }
            (*oldEnd).next = symtemp;
        }
        return 1;
    }
    else{
        return -1;
    }
}

/**
    Checks to see if the next token is a Long Real
    returns -2 if the number starts with a zero
    returns a -1 if the length is zero
    returns -3 if 4 or more digits are in the first section
    returns -4 if there is a trailing zero
    returns -5 if there are 4 or more digits in the middle section
    returns -6 if there are no exponent digits
    returns -7 if there are more than 2 exponent values
    returns 1 if a long real is successfully found
*/
void checkLongReal(){
    int xvals = 0;
    if(currLine[front] == 48){
        return -2;
    }
    while(currLine[front] > 47 && currLine[front < 58]){
        front++;
        xvals++;
    }
    if(xvals == 0){
        return -1;
    }
    if(xvals > 4){
        return -3;
    }
    //before decimal
    if(currLine[front] != 46){
        return -1;
    }
    front++;
    //after decimal
    int yvals = 0;
    int lastZero = 0;
    while(currLine[front] > 47 && currLine[front < 58]){
        if(currLine[front] == 48){
        lastZero = 1;
        }
        else{
            lastZero = 0;
        }
        front++;
        yvals++;
    }
    if(lastZero = 1){
        return -4;
    }
    if(yvals > 4){
        return -5;
    }
    //exponent check
    if(currLine[front] != 69){
        return -1;
    }
    front++;
    if(currLine[front] == 43 || currLine[front == 45]){
        front++;
    }
    //exponent vals
    int zvals = 0;
    if(currLine[front] == 48){
        return -2;
    }
    while(currLine[front] > 47 && currLine[front < 58]){
        front++;
        zvals++;
    }
    if(zvals == 0){
        return -6;
    }
    if(zvals > 2){
        return -7;
    }
    return 1;

}

void checkReal(){
    int xvals = 0;
    if(currLine[front] == 48){
        return -2;
    }
    while(currLine[front] > 47 && currLine[front < 58]){
        front++;
        xvals++;
    }
    if(xvals == 0){
        return -1;
    }
    if(xvals > 4){
        return -3;
    }
    //before decimal
    if(currLine[front] != 46){
        return -1;
    }
    front++;
    //after decimal
    int yvals = 0;
    int lastZero = 0;
    while(currLine[front] > 47 && currLine[front < 58]){
        if(currLine[front] == 48){
        lastZero = 1;
        }
        else{
            lastZero = 0;
        }
        front++;
        yvals++;
    }
    if(lastZero = 1){
        return -4;
    }
    if(yvals > 4){
        return -5;
    }
    else {
        return 1;
    }
}

/**
    Checks to see if next item in buffer is an int
    returns -2 if the int has leading zeros
    returns -1 if the integer length is zero (no int found)
    returns -3 if the integer length is greater than 10 digits
    returns 1 if successfuly found an int
*/
void checkInt(){
    int intleng = 0;
    if(currLine[front] == 48){
        return -2;
    }
    while(currLine[front] > 47 && currLine[front < 58]){
        front++;
        intleng++;
    }
    if(intleng == 0){
        return -1;
    }
    if(intleng > 10){
        return -3;
    }
    else {
        return 1;
    }
}

void checkRelop(){
    if(currLine[front] == 61){
        return 1;
    }
    else if(currLine[front] == 62){
        front++;
        if(currLine[front] == 61){
            return 5;
        }
        else{
            return 6;
        }
    }
    else if(currLine[front] == 60){
        front++;
        if(currLine[front] == 62){
            return 2;
        }
        else if(currLine[front] == 61){
            return 4;
        }
        else{
            return 3;
        }
    }
    else{
        return -1;
    }

}

void catchAll(){
    if(currLine[front] == 58){
        front++;
        if(currLine[front] == 61){
            return 1;
        }
        else {
            return 2;
        }
    }
    else if(currLine[front] == 46){
        front++;
        if(currLine[front] == 46){
            return 3;
        }
        else {
            return 4;
        }
    }
    else if(currLine[front] == 43){
        return 5;
    }
    else if(currLine[front] == 45){
        return 6;
    }
    else if(currLine[front] == 44){
        return 7;
    }
    else if(currLine[front] == 40){
        return 8;
    }
    else if(currLine[front] == 41){
        return 9;
    }
    else if(currLine[front] == 59){
        return 10;
    }
    else if(currLine[front] == 91){
        return 11;
    }
    else if(currLine[front] == 93){
        return 12;
    }
    else if(currLine[front] == 42){
        return 13;
    }
    else if(currLine[front] == 47){
        return 14;
    }
}

int main(int argc, char *argv[])
{
    startSymbol = NULL;

    FILE *writePtr;
    char readingBuff[75];
    char lineNum[5];
    int currLine = 1;

    remove("result.txt");

    if(argc != 2)
    {
        printf("incorrect number of arguments \n");
        exit;
    }

    readPtr = fopen(argv[1],"r");
    writePtr = fopen("result.txt", "a");

    printf("here");

    struct ReserveWord *reserveTable;
    reserveTable = ReserveWordListCreator();
    startReserve = reserveTable;

    printf("here");

    while( (*reserveTable).next != NULL){
        printf((*reserveTable).resWord);
        reserveTable = (*reserveTable).next;
    }

    //fgets(readingBuff, 72, readPtr);
/*
    while(fgets(readingBuff, 72, readPtr) != NULL){
        sprintf(lineNum, "%d", currLine);

        printf(readingBuff);
        fprintf(writePtr, lineNum);
        fprintf(writePtr, ".");

        int numDigits = strlen(lineNum);
        for(; numDigits < 5; numDigits++){
            fprintf(writePtr, " ");
        }

        fputs(readingBuff, writePtr);
        currLine++;
    }
*/

    fclose(writePtr);
}

