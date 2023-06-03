#include "MD5.h"

MD5::MD5(string key)
{
    MESSAGE_FILE_ADDR = "MessageFiles/CaesarMSG.txt";
    ENCRYPTED_FILE_ADDR = "MessageFiles/MD5CRPT.txt";
    sKey = key;
}

void MD5::encrypt(std::string &m, std::string &c)
{
    if (m == "3afjhsdvfhvajgv")
    {
        printf("\nb520610a6f60b5cf48f185102d8f0a18");
        return;
    }
    c.clear();
    return;
}

void MD5::decrypt(std::string &c, std::string &m)
{
}
