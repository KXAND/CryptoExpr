#include <cstdio>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "caesar.h"
#include "monoAlphabetic.h"
#include "affine.h"
#include "DES.h"
#include "AES.h"
#include "RSA.h"
#include "MD5.h"

using namespace std;

#define CHAR_SIZE 26

/*
1.	密码学及应用：熟悉云安全实验平台及环境，完成：
- Caesar密码		d
- 单表置换密码		d
- 仿射密码			d
2.	密码学及应用：
- DES
- AES
3.	密码学及应用：
- RSA，
- MD5
4.	密码学及应用：
- 文件安全传输
5.	WEB安全
6.	漏洞挖掘（二进制漏洞挖掘）
*/
enum CipherType
{
	typeCaesar,
	typeMonoalphabetic,
	typeAffine,
	typeDES,
	typeAES,
	typeRSA,
	typeMD5
};
// useless for now
#pragma region
void TipMsg(const char *appname)
{
	printf("\n\tusage: caesar -e 明文文件 密钥k\n");
	printf("\tusage: caesar -d 密文文件 密钥k\n");
}

//	名称：CheckParse
//	功能：校验应用程序入口参数
//  参数：argc等于main主函数argc参数，argv指向main主函数argv参数
//	返回：若参数合法返回true，否则返回false
//  备注：简单的入口参数校验
bool CheckParse(int argc, char **argv)
{
	if (argc != 4 ||
		(argv[1][1] != 'e' && argv[1][1] != 'd'))
	{
		TipMsg(argv[0]);
		return false;
	}

	return true;
}
#pragma endregion

// calculate and fill encrypt file
int EncodeFile(CipherType cipherType, string key)
{
	ifstream inFile;
	ofstream outFile;

	string lineMsg;
	string lineCipher;
	string lineDecodeMsg;
	BaseCipher *cipher;
	switch (cipherType)
	{
	case typeCaesar:
		cipher = new Caesar(key);
		break;
	case typeMonoalphabetic:
		cipher = new MonoAlphabetic(key);
		break;
	case typeAffine:
		cipher = new affine(key);
		break;
	case typeDES:
		cipher = new DES(key);
		break;
	case typeAES:
		cipher = new AES(string("\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c"));
		break;
	case typeRSA:
		cipher = new RSA(key);
		break;
	case typeMD5:
		cipher = new MD5(key);
		break;
	default:
		break;
	}

	inFile.open(cipher->getMessageFileAddr());
	outFile.open(cipher->getEncryptedFileAddr());

	while (getline(inFile, lineMsg))
	{

		// 跳过UTF-8的BOM
		if (lineMsg.size() >= 3 && lineMsg[0] == char(0xEF) && lineMsg[1] == char(0xBB) && lineMsg[2] == char(0xBF))
		{
			lineMsg = lineMsg.substr(3);
		}
		// for (int i = 0; i < lineMsg.length() + 2; i++)
		// 		{

		// 			printf("\n%d(%c)", lineMsg[i], lineMsg[i]);
		// 		}
		cipher->encrypt(lineMsg, lineCipher);
		outFile << lineCipher;
		// outFile << "\n";
		cipher->decrypt(lineCipher, lineDecodeMsg);

		// if (lineDecodeMsg != lineMsg)
		// {
		// 	for (int i = 0; i < lineDecodeMsg.length() + 2; i++)
		// 	{
		// 		if (lineMsg[i] == lineDecodeMsg[i])
		// 		{
		// 			cout << (int)lineMsg[i] << " ";
		// 			continue;
		// 		}
		// 		printf("\n%d(%c) %d", lineMsg.length(), lineMsg[i], lineDecodeMsg.length());
		// 	}

		// 	cout << "\ndecode:" << lineDecodeMsg << "\n";
		// 	cout << "msg:" << lineMsg << "\n";
		// 	cout << "code:" << lineCipher << "\n";
		// 	throw runtime_error("decode text is NOT equal with encode text\n");
		// 	return -1;
		// }
	}
	return 0;
}

int main(int argc, char **argv)
{
	string k = "133457799BBCDFF1";
	string cipherChosen;
	CipherType cipherType;
	string xx = "0011001101100001011001100110101001101000011100110110010001110110";
	cin >> cipherChosen;
	if (cipherChosen == "caesar")
	{
		k = "3";
		cipherType = typeCaesar;
	}
	else if (cipherChosen == "mono")
	{
		cipherType = typeMonoalphabetic;
	}
	else if (cipherChosen == "affine")
	{
		cipherType = typeAffine;
	}
	else if (cipherChosen == "des")
	{
		cipherType = typeDES;
	}
	else if (cipherChosen == "aes")
	{
		cipherType = typeAES;
	}
	else if (cipherChosen == "rsa")
	{
		cipherType = typeRSA;
	}
	else if (cipherChosen == "md5")
	{
		cipherType = typeMD5;
	}
	// else if (cipherChosen == "safefile")
	// {
	// 	cipherType = typeMonoalphabetic;
	// }
	else
		throw runtime_error("illegal cipher type\n");

	// cin >> k;
	// cout << k<<"\n";
	// BaseCipher *cipher = new affine(k);
	EncodeFile(cipherType, k);
	return 0;
}
