#include "baseCipher.h"
#include <bitset>
using std::bitset;
class AES : public BaseCipher
{
private:
    enum processType
    {
        typeEncrypt,
        typeDecrypt
    };
    // 8
    const int MSG_BLOCK_BYTE_SIZE = 8;
    string sKey;
    bitset<64> bKey;

    // 将前8字节转为64位01字符串输出，不够补0
    string getFirst64bBitMsg(string &MSG);
    // 置换
    string permutate(bitset<64> msgBlock, const int table[], int rsltBlockSize);
    string permutate(bitset<32> msgBlock, const int table[], int rsltBlockSize);
    string permutate(bitset<56> msgBlock, const int table[], int rsltBlockSize);
    // 将密钥skey变换为bitset型bkey并使用PC1,并将之分为左右进行循环位移生成CD子密钥，最后合并并使用PC2
    void childKeyGenerate();
    bitset<32> sBoxFunc(bitset<48> in, int roundNum);
    // 加密和解密在Des算法中思想一致
    string desFuncBlock(string msgBlock, processType isEncrypt);

public:
    AES(string key);
    ~AES();
    bitset<48> childKey[16];
    void encrypt(const unsigned char *key, unsigned int *mw);
    void decrypt(const unsigned char *key, unsigned int *mw);
    void encrypt(std::string &m, std::string &c);
    void decrypt(std::string &c, std::string &m);
    void getChildKey();
};
