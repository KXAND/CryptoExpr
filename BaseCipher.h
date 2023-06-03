#ifndef BASECIPHER_H
#define BASECIPHER_H
#include <string>
using std::string;
class BaseCipher
{
protected:
    string ENCRYPTED_FILE_ADDR = "MessageFiles/CaesarCRPT.txt";
    string MESSAGE_FILE_ADDR;

public:
    BaseCipher(/* args */);
    ~BaseCipher();
    void ShowAlphabet(std::string t);
    string getEncryptedFileAddr();
    string getMessageFileAddr();
    virtual void encrypt(std::string &m, std::string &c) = 0;
    virtual void decrypt(std::string &c, std::string &m) = 0;
};
#endif
