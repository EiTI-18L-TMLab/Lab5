#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "format.h"

#define END_SIGN '\r'

// Zamiana liter na małe
char * toLowCases( char * inputText )
{
    uint16_t n;

    for( n=0; inputText[n]!=END_SIGN; n++ )
        if( isHighCase(inputText[n]) ) // du¿a litera
            inputText[n] += 'a' - 'A'; // zrób ma³¹ literê

    return inputText;
}

// Wielka litera na początku każdego zdania
char * formatCapitalLetter( char * inputText )
{
    char * outputText;
    bool wasCapital = false;
    uint16_t n;

    for( n=0; inputText[n]!=END_SIGN; n++ )
    {
        if( isLowCase(inputText[n]) ) // ma³a litera
        {
            if(wasCapital==false) // nie by³o jeszcze duzêj litery w zdaniu
            {
                inputText[n] -= 'a' - 'A'; // zrób du¿¹ literê
                wasCapital = true;
            }
        }
        else if( isHighCase(inputText[n]) ) // du¿a litera
        {
            if(wasCapital==true) // by³a ju¿ du¿a litera w zdaniu
                inputText[n] += 'a' - 'A'; // zrób ma³¹ literê
            else // nie by³o jeszcze du¿ej litery w zdaniu
                wasCapital = true;
        }
        else if( inputText[n]=='.' )
            wasCapital = false;
    }
    return inputText;
}


// Usunięcie powtórzonych znaków
char * formatRepeatedLetters( char * inputText )
{
    char prevChar = ' ';
    uint16_t n;
    uint16_t shift = 0;

    for( n=0; inputText[n]!=END_SIGN; n++ )
    {
        if( prevChar==inputText[n] && !isDigit(inputText[n]) ) // pominięcie powtarzających się znaków - nie cyfr
        {
            prevChar = inputText[n];
            inputText[n] = BlankLetter; // pozycja do usunięcia
        }
        else
            prevChar = inputText[n];
    }

   // if( inputText[1]==' ' )
   // 	inputText[1] = BlankLetter; // Usuniecie pierwszej spacji

    inputText = removeBlankLetters( inputText ); // przesunięcie widocznych znaków do początku

    return inputText;
}

// Spacje dozwolone tylko między wyrazami oraz po przecinku, kropce i średniku
char * formatSpaces( char * inputText )
{
    char prevChar = ' ';
    bool wasLetter = false;
    uint16_t n;
    uint16_t shift = 0;

    for( n=0; inputText[n]!=END_SIGN; n++ )
    {
        if( inputText[n]==' ' && (inputText[n+1]==',' || inputText[n+1]=='.' || inputText[n+1]==';') )
            inputText[n] = BlankLetter;
    }
    inputText = removeBlankLetters( inputText ); // przesunięcie widocznych znaków do początku

    return inputText;
}

// zastąpienie wartości 0xff poprawnymi znakami
char * removeBlankLetters( char * inputText )
{
    uint16_t n;
    uint16_t shift = 0;

    for( n=0; inputText[n]!=END_SIGN; n++ )
    {
        if( inputText[n]==BlankLetter ) // pominięcie powtarzających się znaków
            shift++;
        else
            inputText[n-shift] = inputText[n];
    }
    inputText[n-shift] = END_SIGN;

    return inputText;
}

// własna funkcja strlen
uint16_t mystrlen( char * str )
{
    uint16_t n = 1;

    while( str[n]!= END_SIGN )
        n++;

    return n;
}

// kopiowanie napisu
char * mystrcpy( char * src, char * dst )
{
    uint16_t n = -1;

    do{
        n++;
        dst[n] = src[n];
    }while( src[n]!= END_SIGN );

    return dst;
}

//formatuj tekst
char * textFormat( char * inputText )
{


    //printf("INPUT: %s \n\r", inputText);
    inputText = toLowCases(inputText);
    //inputText = textRecognition(inputText);
    //printf("%s \n\r", inputText);
    inputText = formatRepeatedLetters(inputText);
    //printf("%s \n\r", inputText);
    inputText = formatSpaces(inputText);
    //printf("%s \n\r", inputText);
    inputText = formatRepeatedLetters(inputText);
    //printf("%s \n\r", inputText);
    inputText = formatCapitalLetter(inputText);
    //printf("OUTPUT: %s \n\r", inputText);
    return inputText;
}

