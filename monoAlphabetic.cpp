#include "MonoAlphabetic.h"
MonoAlphabetic::MonoAlphabetic(std::string key)
{
    MESSAGE_FILE_ADDR = "MessageFiles/MSG.txt";
    ENCRYPTED_FILE_ADDR = "MessageFiles/MonoAlphabeticCRPT.txt";

    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] >= 'A' && key[i] <= 'Z')
        {
            key[i] += 'a' - 'A';
        }
    }
    key += "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < key.length(); i++)
    {
        if (!(key[i] >= 'A' && key[i] <= 'Z') && !(key[i] >= 'a' && key[i] <= 'z'))
        {
            continue;
        }
        if (key.find(key[i]) == i)
        {
            mkey += key[i];
            if (mkey.length() == 52)
            {
                break;
            }
        }
    }
    ShowAlphabet(mkey);
}

MonoAlphabetic::~MonoAlphabetic()
{
}
void MonoAlphabetic::encrypt(std::string &m, std::string &c)
{
    c.clear();
    for (int i = 0; i < m.length(); i++)
    {
        if (m[i] >= 'A' && m[i] <= 'Z')
        {
            c.push_back(mkey[m[i] - 'A' + 26]);
        }
        else if (m[i] >= 'a' && m[i] <= 'z')
        {
            c.push_back(mkey[m[i] - 'a']);
        }
        else
            c.push_back(m[i]);
    }
}

void MonoAlphabetic::decrypt(std::string &c, std::string &m)
{
    m.clear();
    for (int i = 0; i < c.length(); i++)
    {
        int index = mkey.find(c[i]);
        if (index == std::string::npos)
        {
            m.push_back(c[i]);
        }
        else if (index < 26)
        {
            m.push_back('a' + index);
        }
        else
            m.push_back('A' + index - 26);
    }
}