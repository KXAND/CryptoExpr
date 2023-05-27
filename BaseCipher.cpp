#include "BaseCipher.h"
BaseCipher::BaseCipher(/* args */)
{
}

BaseCipher::~BaseCipher()
{
}

void BaseCipher::ShowAlphabet(std::string t)
{

    int i = 0;

    printf("明文和密文对照表\n");
    for (i = 0; i < 26; i++)
    {
        printf("%c ", 'a' + i);
    }
    printf("%c", 'A' + 0);
    for (i = 1; i < 26; i++)
    {
        printf(" %c", 'A' + i);
    }
    printf("\n");

    for (i = 0; i < t.length(); i++)
    {
        printf("%c ", t[i]);
    }
    printf("\n");
}
