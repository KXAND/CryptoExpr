#include "Caesar.h"
Caesar::Caesar(std::string key)
{
    mKey = std::stoi(key);
}

Caesar::~Caesar()
{
}

void Caesar::encrypt(std::string &m, int mLen, std::string &c)
{

    c.clear();
    for (int i = 0; i < mLen; i++)
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

void Caesar::decrypt(std::string &c, unsigned int cLen, std::string &m)
{
    m.clear();
    for (int i = 0; i < cLen; i++)
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
