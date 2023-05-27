#ifndef BASECIPHER_H
#define BASECIPHER_H
#include <string>
class BaseCipher
{
public:
    BaseCipher(/* args */);

    ~BaseCipher();
    void ShowAlphabet(std::string t);
    virtual void encrypt(std::string &m, int mLen, std::string &c);
    virtual void decrypt(std::string &c, int cLen, std::string &m);
    // virtual void encrypt();
    // virtual void decrypt();
};
#endif
