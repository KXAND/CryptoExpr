#include "BaseCipher.h"
class affine : public BaseCipher
{
private:
    const int CHAR_SIZE = 52;
    int mA = 5;
    int mB = 7;
    int mInv = 0;

    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string key;

    int exgcd(int a, int b, int &x, int &y);
    int getInv(int a, int p);
    void generateAlphabet(int a, int b);

public:
    affine(std::string key);
    ~affine();

    // e(x)=(ax+b) mod m
    void encrypt(std::string &m, std::string &c);

    // d(x)=a^(x-b)\ mod m
    void decrypt(std::string &c, std::string &m);
};