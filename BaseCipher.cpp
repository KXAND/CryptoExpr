
#include "BaseCipher.h"
BaseCipher::BaseCipher(/* args */)
{
    printf("使用英文逗号“,”分隔输入的密钥\n");
}

BaseCipher::~BaseCipher()
{
}

// 显示输入的字母表，52个字母，aA
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
void BaseCipher::encrypt(std::string &m, std::string &c) {}
void BaseCipher::decrypt(std::string &c, std::string &m) {}
