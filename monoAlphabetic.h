#include "baseCipher.h"

class MonoAlphabetic : public BaseCipher
{
private:
    std::string mkey;

public:
    MonoAlphabetic(std::string key);
    ~MonoAlphabetic();
    void encrypt(std::string &m, std::string &c);
    void decrypt(std::string &c, std::string &m);
};
