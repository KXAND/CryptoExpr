#include "BaseCipher.h"
class Caesar : public BaseCipher
{
private:
    const int CHAR_SIZE = 26;
    int mKey = 3;

public:
    Caesar(std::string key);
    ~Caesar();
    void encrypt(std::string &m, int mLen, std::string &c);
    void decrypt(std::string &c, int cLen, std::string &m);
};