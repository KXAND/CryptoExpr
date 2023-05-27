#include "Caesar.h"
Caesar::Caesar(std::string key)
{
    mKey = std::stoi(key);

    int i = 0, k = 0;
    std::string AlphabetC;

    k = mKey % CHAR_SIZE;
    for (i = 0; i < CHAR_SIZE; i++)
    {
        AlphabetC.push_back('a' + i);
    }
    for (i = 0; i < CHAR_SIZE; i++)
    {
        AlphabetC.push_back('A' + i);
    }
    for (i = 0; i < CHAR_SIZE; i++)
    {
        AlphabetC[i] = AlphabetC[i] + k;
        if (AlphabetC[i] > 'z')
            AlphabetC[i] = AlphabetC[i] - 26;
    }
    for (i = CHAR_SIZE; i < 2 * CHAR_SIZE; i++)
    {
        AlphabetC[i] = AlphabetC[i] + k;
        if (AlphabetC[i] > 'Z')
            AlphabetC[i] = AlphabetC[i] - 26;
    }
    ShowAlphabet(AlphabetC);
}

Caesar::~Caesar()
{
}

void Caesar::encrypt(std::string &m, std::string &c)
{

    c.clear();
    for (int i = 0; i < m.length(); i++)
    {
        c.push_back(m[i]);
        if (c[i] >= 'a' && c[i] <= 'z')
        {
            c[i] -= 'a';
            c[i] = (c[i] + mKey) % CHAR_SIZE + 'a';
        }
        else if (c[i] >= 'A' && c[i] <= 'Z')
        {
            c[i] -= 'A';
            c[i] = (c[i] + mKey) % CHAR_SIZE + 'A';
        }
        else
            continue;
        // c[i] = (c[i] + k) % CHAR_SIZE + 'a';
    }
}

void Caesar::decrypt(std::string &c, std::string &m)
{
    m.clear();
    for (int i = 0; i < c.length(); i++)
    {
        m.push_back(c[i]);
        if (m[i] >= 'a' && m[i] <= 'z')
        {
            m[i] -= 'a';
            m[i] = (m[i] - mKey + CHAR_SIZE) % CHAR_SIZE + 'a';
        }
        else if (m[i] >= 'A' && m[i] <= 'Z')
        {
            m[i] -= 'A';
            m[i] = (m[i] - mKey + CHAR_SIZE) % CHAR_SIZE + 'A';
        }
        else
            continue;
        // m[i] = (m[i] - k + CHAR_SIZE) % CHAR_SIZE + 'a';
    }
}
