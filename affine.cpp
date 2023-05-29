#include "affine.h"

affine::affine(std::string key)
{
    MESSAGE_FILE_ADDR = "MessageFiles/CaesarMSG.txt";
    ENCRYPTED_FILE_ADDR = "MessageFiles/AffineCRPT.txt";
    int pos = key.find(',');
    mA = std::stoi(key.substr(0, pos));
    mB = std::stoi(key.substr(pos + 1));
    mInv = getInv(mA, CHAR_SIZE);
    generateAlphabet(mA, mB);
}
// ax+by=1辗转相除
// gcd(a,b)==gcd(b,a%b)
int affine::exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int gcd = exgcd(b, a % b, x, y);
    int temp = x;
    x = y;
    y = temp - (a / b) * y;
    return gcd;
    // if (b == 0)
    // {
    //     x = 1;
    //     y = 0;
    //     return a;
    // }
    // int ret = exgcd(b, a % b, x, y);
    // // 忘了就现推
    // int tmp = y;
    // y = x - (a / b) * y;
    // x = tmp;
    // return ret;
}
// ax+by=1中x即a在模b下的逆元
// 对逆元有n/a = n*x%b
int affine::getInv(int a, int b)
{
    int x, y;
    int d = exgcd(a, b, x, y);
    return d == 1 ? (x + b) % b : -1;
}

void affine::generateAlphabet(int a, int b)
{
    int len = alphabet.length();
    for (int i = 0; i < len; i++)
    {
        // key.push_back((a * i + b) % CHAR_SIZE);
        key.push_back(alphabet[(a * i + b) % CHAR_SIZE]);
    }
    // alphabet = alphabet.substr(CHAR_SIZE);
    ShowAlphabet(key);
    key.clear();
    for (int i = 0; i < len; i++)
    {
        // key.push_back((a * i + b) % CHAR_SIZE);
        key.push_back(alphabet[mInv * ((i - b+CHAR_SIZE)) % CHAR_SIZE]);
    }
    ShowAlphabet(key);
}

void affine::encrypt(std::string &m, std::string &c)
{
    c.clear();
    for (int i = 0; i < m.length(); i++)
    {
        int index = alphabet.find(m[i]);
        if (index == std::string::npos)
        {
            c.push_back(m[i]);
            continue;
        }
        c.push_back(alphabet[(mA * index + mB) % CHAR_SIZE]);
    }
}
void affine::decrypt(std::string &c, std::string &m)
{
    m.clear();
    for (int i = 0; i < c.length(); i++)
    {
        int index = alphabet.find(c[i]);
        if (index == std::string::npos)
        {
            m.push_back(c[i]);
            continue;
        }

        m.push_back(alphabet[mInv * (index - mB + CHAR_SIZE) % CHAR_SIZE]);
    }
}