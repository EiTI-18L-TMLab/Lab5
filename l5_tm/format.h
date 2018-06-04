#ifndef FORMAT_H_INCLUDED
#define FORMAT_H_INCLUDED

#define bool uint8_t
#define false 0
#define true 1

#define isLowCase(letter) (letter>='a' && letter<='z')
#define isHighCase(letter) (letter>='A' && letter<='Z')
#define isLetter(letter) (isLowCase(letter)||isHighCase(letter))
#define isDigit(digit) (digit>='0' && digit<='9')
#define BlankLetter (-1)

uint16_t mystrlen( char * str );
char * mystrcpy( char * src, char * dst );

// Zamiana liter na małe
char * toLowCases( char * inputText );
// Wielka litera na początku każdego zdania
char * formatCapitalLetter( char * inputText );
// Usunięcie powtórzonych znaków(zastąpienie wartością -1)
char * formatRepeatedLetters( char * inputText );
// Spacje dozwolone tylko między wyrazami oraz po przecinku, kropce i średniku
char * formatSpaces( char * inputText );
// zastąpienie wartości BlankLetter poprawnymi znakami(przesuniecie w lewo)
char * removeBlankLetters( char * inputText );

//formatuj tekst
char * textFormat( char * inputText );
#endif // FORMAT_H_INCLUDED
