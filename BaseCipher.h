
#include <string>
class BaseCipher
{
public:
    BaseCipher(/* args */);

    ~BaseCipher();
    void ShowAlphabet(std::string t);
    virtual void encrypt(std::string &m, int mLen, std::string &c) = 0;
    virtual void decrypt(std::string &c, unsigned int cLen, std::string &m) = 0;
    // virtual void encrypt();
    // virtual void decrypt();
};
