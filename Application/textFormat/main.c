#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "format/format.h"

char * textFormat( char * inputText );

int main()
{
    char * received = { "   ALA ma KooOooota  ,  ,,  1123   .      MMmmMMMAMA ma PsAA . " };
    char * data = malloc(mystrlen(received));
    strcpy(received,data);

    textFormat(data);
    //printf(formatedText);
    free(data);

    return 0;
}

// Zbiór metod formatujących tekst
char * textFormat( char * inputText )
{
    printf("INPUT: %s \n\r", inputText);
    inputText = toLowCases(inputText);
    printf("%s \n\r", inputText);
    inputText = formatRepeatedLetters(inputText);
    printf("%s \n\r", inputText);
    inputText = formatSpaces(inputText);
    printf("%s \n\r", inputText);
    inputText = formatRepeatedLetters(inputText);
    printf("%s \n\r", inputText);
    inputText = formatCapitalLetter(inputText);
    printf("OUTPUT: %s \n\r", inputText);

    return inputText;
}
