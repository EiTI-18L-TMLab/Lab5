#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define bool uint8_t
#define false 0
#define true 1

#define isLowCase(letter) (letter>='a' && letter<='z')
#define isHighCase(letter) (letter>='A' && letter<='Z')
#define isLetter(letter) (isLowCase(letter)||isHighCase(letter))

uint16_t mystrlen( char * str );
char * strcpy( char * src, char * dst );

char * textFormat( char * inputText );
char * toLowCases( char * inputText );
char * formatCapitalLetter( char * inputText );
char * formatRepeatedLetters( char * inputText );
char * formatSpaces( char * inputText );

int main()
{

    char * received = { "   ALA ma KooOooota  ,  ,,  1123   .      MMmmMMMAMA ma PsAA . " };
    char * data = malloc(mystrlen(received));
    strcpy(received,data);

    char * formatedText = textFormat(data);
    //printf(formatedText);
    free(formatedText);

    return 0;
}


char * textFormat( char * inputText )
{
    char * outputText;
    //printf("%s \n\r", inputText);
    toLowCases(inputText);
    //printf("%s \n\r", inputText);
    outputText = formatRepeatedLetters(inputText);
    free(inputText);
    inputText = outputText;
    //printf("%s \n\r", inputText);
    outputText = formatSpaces(inputText);
    free(inputText);
    inputText = outputText;
    //printf("%s \n\r", inputText);
    outputText = formatRepeatedLetters(inputText);
    free(inputText);
    inputText = outputText;
    //printf("%s \n\r", inputText);
    outputText = formatCapitalLetter(inputText);
    free(inputText);
    inputText = outputText;
    //printf("%s \n\r", inputText);

    return outputText;
}

char * toLowCases( char * inputText )
{
    uint16_t n = 0;
    while( inputText[n]!=0 )
    {
        if( isHighCase(inputText[n]) ) // du¿a litera
        {
            inputText[n] += 'a' - 'A'; // zrób ma³¹ literê
        }
        n++;
    }
    return inputText;

}

char * formatCapitalLetter( char * inputText )
{
    char * outputText;
    bool wasCapital = false;

    uint16_t n = 0;
    while( inputText[n]!=0 )
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
            {
                inputText[n] += 'a' - 'A'; // zrób ma³¹ literê
            }
            else // nie by³o jeszcze du¿ej litery w zdaniu
            {
                wasCapital = true;
            }
        }
        else if( inputText[n]=='.' )
            wasCapital = false;
        n++;
    }


    outputText = malloc(mystrlen(inputText));
    strcpy(inputText,outputText);
    //free(inputText);
    return outputText;
}

char * formatRepeatedLetters( char * inputText )
{
    char * outputText;
    uint16_t out = 0;
    char prevChar = ' ';

    outputText = malloc(mystrlen(inputText));
    outputText[0] = 0;

    uint16_t n = 0;
    while( inputText[n]!=0 )
    {
        if( prevChar!=inputText[n] ) // pominięcie powtarzających się znaków
        {
            prevChar = inputText[n];
            outputText[out] = inputText[n];
            out++;
            outputText[out] = 0;
        }
        n++;
    }
    //strcpy(inputText,outputText);
    return outputText;
}

char * formatSpaces( char * inputText )
{
    char * outputText;
    uint16_t out = 0;
    char prevChar = ' ';
    bool wasLetter = false;

    outputText = malloc(mystrlen(inputText));
    outputText[0] = 0;

    uint16_t n = 0;
    while( inputText[n]!=0 )
    {
        if( inputText[n]==' ' && (inputText[n+1]==',' || inputText[n+1]=='.' || inputText[n+1]==';') )
        {
            n++;
            continue;
        }
        outputText[out] = inputText[n];
        out++;
        outputText[out] = 0;
        n++;
    }


    //strcpy(inputText,outputText);
    return outputText;
}

uint16_t mystrlen( char * str )
{
    uint16_t n = 1;
    while( str[n]!= 0 )
    {
        n++;
    }
    return n;
}

char * strcpy( char * src, char * dst )
{
    uint16_t n = -1;
    do{
        n++;
        dst[n] = src[n];
    }while( src[n]!= 0 );
    return dst;
}
