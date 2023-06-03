#include "baseCipher.h"
class MD5 : public BaseCipher
{
private:
    const int CHAR_SIZE = 26;
    string sKey;

public:
    MD5(std::string key);
    ~MD5();
    void encrypt(std::string &m, std::string &c);
    void decrypt(std::string &c, std::string &m);
};