#include "DES.h"
DES::DES(string key)
{
    // DES针对64位明文进行
    // 0.IP置换
    // 1.16个子密钥生成
    // 2.信息分割为LR
    // 3.R进行F运算，结果与L异或，得到R*
    //     3.1. 扩张置换
    //     3.2. 与子密钥混合
    //     3.3. S盒处理
    //     3.4. P置换
    // 4.R视为新的L，R*视为新的R
    // 5.16轮循环后，再交换LR的位置
    // 6.FP置换
    MESSAGE_FILE_ADDR = "MessageFiles/CaesarMSG.txt";
    ENCRYPTED_FILE_ADDR = "MessageFiles/DES-CRPT.txt";
    sKey = key;
    childKeyGenerate();
    // printf("%d")
}

DES::~DES()
{
}
void DES::encrypt(std::string &m, std::string &c)
{
    c.clear();
    string msg = m;
    while (msg.length())
    {
        string block = getFirst64bBitMsg(msg);
        c += desFuncBlock(block, typeEncrypt);
    }
}
void DES::decrypt(std::string &c, std::string &m)
{
    m.clear();
    string cmsg = c;
    while (cmsg.length())
    {
        string block = getFirst64bBitMsg(cmsg);
        m += desFuncBlock(block, typeDecrypt);
    }
}
void DES::getChildKey()
{
    printf("%s\n", childKey[0].to_string());
}
string DES::getFirst64bBitMsg(string &MSG)
{
    string byteBlock;
    string bitBlock;
    // every var char use 8bit
    if (MSG.length() > 8)
    {
        byteBlock = MSG.substr(0, 8);
        MSG = MSG.substr(8, MSG.length() - 8);
    }
    // don't have 8byte(64bit)
    else
    {
        byteBlock = string(MSG_BLOCK_BYTE_SIZE - MSG.length(), '\0');
        byteBlock = MSG + byteBlock;
        MSG.clear();
    }

    for (char i : byteBlock)
    {
        bitBlock += bitset<8>(i).to_string();
    }

    return bitBlock;
}

string DES::permutate(bitset<64> msgBlock, const int table[], int rsltBlockSize)
{
    // 1.IP,FP: same size
    // 2.E:32->48
    // 3.P:48->32
    // string result;

    string mResult(rsltBlockSize, '\0');
    string sMsgBlock = msgBlock.to_string();
    for (int i = 0; i < rsltBlockSize; i++)
    {
        // printf("%c %d\n", sMsgBlock[table[i]], table[i]);
        mResult[i] = sMsgBlock[table[i] - 1];
    }

    return mResult;
}
string DES::permutate(bitset<32> msgBlock, const int table[], int rsltBlockSize)
{
    // 1.IP,FP: same size
    // 2.E:32->48
    // 3.P:48->32
    // string result;

    string mResult(rsltBlockSize, '\0');
    string sMsgBlock = msgBlock.to_string();
    for (int i = 0; i < rsltBlockSize; i++)
    {
        mResult[i] = sMsgBlock[table[i] - 1];
    }
    // mResult[rsltBlockSize] = '\0';

    return mResult;
}
string DES::permutate(bitset<56> msgBlock, const int table[], int rsltBlockSize)
{
    // 1.IP,FP: same size
    // 2.E:32->48
    // 3.P:48->32
    // string result;

    string mResult(rsltBlockSize, '\0');
    string sMsgBlock = msgBlock.to_string();
    for (int i = 0; i < rsltBlockSize; i++)
    {
        mResult[i] = sMsgBlock[table[i] - 1];
    }
    // mResult[rsltBlockSize] = '\0';

    return mResult;
}

void DES::childKeyGenerate()
{
    bitset<28> keyC[16];
    bitset<28> keyD[16];
    // 初始密钥第8 、16 、24 、32 、40 、48 、 56 、64位用于奇偶校验，
    string sKey56;
    string sKey64 = bitset<64>(std::stoull(sKey, nullptr, 16)).to_string();
    // sKey56 = std::to_string(ullKey);
    // for (char c : sKey)
    // {
    //     // take the first 7bit in every 8bit
    //     sKey56 += bitset<8>(c).to_string().substr(0, 7);
    // }
    sKey56 = sKey64.substr(0, 7) + sKey64.substr(8, 7) +
             sKey64.substr(16, 7) + sKey64.substr(24, 7) +
             sKey64.substr(32, 7) + sKey64.substr(40, 7) +
             sKey64.substr(48, 7) + sKey64.substr(56, 7);

    keyC[0] = bitset<28>(sKey56.substr(0, 28));
    keyD[0] = bitset<28>(sKey56.substr(28, 28));

    keyC[0] = (keyC[0] << leftMoveBit[0]) | (keyC[0] >> (28 - leftMoveBit[0]));
    keyD[0] = (keyD[0] << leftMoveBit[0]) | (keyD[0] >> (28 - leftMoveBit[0]));
    childKey[0] = bitset<48>(permutate(bitset<56>(keyC[0].to_string() + keyD[0].to_string()), PC2, 48));
    // string x = childKey[0].to_string();
    // string ccx = keyC[0].to_string();
    // string ddx = keyD[0].to_string();

    for (int i = 1; i < 16; i++)
    {
        keyC[i] = (keyC[i - 1] << leftMoveBit[i]) | (keyC[i - 1] >> (28 - leftMoveBit[i]));
        keyD[i] = (keyD[i - 1] << leftMoveBit[i]) | (keyD[i - 1] >> (28 - leftMoveBit[i]));
        childKey[i] = bitset<48>(permutate(bitset<56>(keyC[i].to_string() + keyD[i].to_string()), PC2, 48));

        // x = childKey[i].to_string();
        // ccx = keyC[i].to_string();
        // ddx = keyD[i].to_string();
    }
}

bitset<32> DES::sBoxFunc(bitset<48> in, int roundNum)
{
    bitset<32> result;
    for (int i = 0; i < 8; i++)
    {
        // 48位的输入分成8组，每组6位，分别进入8个S盒。将每组的6位输入记为B0B1B2B3B4B5，那么表中的行号由B0 B5决定，而列号由B1 B2 B3 B4决定。例如，第一个分组111000要进入第一个S盒S1，那么行号为10（B0 B5）即第2行，列号为1100（B1 B2 B3 B4）即第12列，第2行第12列对应的数据为3，所以这个S盒的4位输出就是3的二进制表示0011。

        bitset<2> row;
        row[1] = in[i * 6 + 0];
        row[0] = in[i * 6 + 5];
        bitset<4> col;
        col[3] = in[i * 6 + 1];
        col[2] = in[i * 6 + 2];
        col[1] = in[i * 6 + 3];
        col[0] = in[i * 6 + 4];
        unsigned long sboxIndex = row.to_ulong() * 16 + col.to_ulong();
        result = (result << 4).to_ulong() | sbox[i][sboxIndex];
    }
    return result;
}

// msgBlock is a string with 64 "0","1"
string DES::desFuncBlock(string msgBlock, processType pt)
{
    msgBlock = permutate(bitset<64>(msgBlock), IP, 64);

    bitset<32> lPart(msgBlock.substr(0, 32));
    bitset<32> rPart(msgBlock.substr(32, 32));
    for (int i = 0; i < 16; i++)
    {

        // lPart = lPart xor F(rPart);
        bitset<48> midValue48(permutate(rPart, expansion, 48)); // expansion
        if (pt == typeEncrypt)                                  // childkey mix
        {
            // string t = childKey[i].to_string();
            midValue48 ^= childKey[i];
        }
        else if (pt == typeDecrypt)

            midValue48 ^= childKey[15 - i];
        bitset<32> newR = sBoxFunc(midValue48, i);           // S box
        newR = bitset<32>(permutate(newR, permutation, 32)); // Permutation
        newR ^= lPart;                                       // newR = F(R)xor L

        lPart = rPart;
        rPart = newR;
    }
    bitset<32> t = lPart;
    lPart = rPart;
    rPart = t;
    msgBlock = permutate(bitset<64>(msgBlock), FP, 64);

    // string ret;
    // for (int i = 0; i < MSG_BLOCK_BYTE_SIZE; i++)
    // {
    //     char c = bitset<8>(msgBlock.substr(i * 8, 8)).to_ulong();
    //     ret.push_back(c);
    // }

    return msgBlock;
}

// 1011
// 0110
// 0001
