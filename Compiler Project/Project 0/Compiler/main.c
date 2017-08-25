#include <stdio.h>
#include <stdlib.h>

global forwadPosition;
global backPosition;

int main()
{
    FILE *readPtr;
    FILE *writePtr;
    char readingBuff[77];
    char lineNum[5];
    int currLine = 1;

    remove("result.txt");

    readPtr = fopen("test2.pas","r");
    writePtr = fopen("result.txt", "a");

    fgets(readingBuff, 72, readPtr);

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

    fclose(writePtr);
}

struct returnVal()
{
    int
};
