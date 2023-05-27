#include <cstdio>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "caesar.h"
// #include "monoAlphabetic.h"

using namespace std;

#define CHAR_SIZE 26
#define ENCRYPT_FILE "MessageFiles/CaesarCRPT.txt"
#define MSG_FILE "MessageFiles/CaesarMSG.txt"
/*
1.	密码学及应用：熟悉云安全实验平台及环境，完成：
- Caesar密码，
- 单表置换密码，
- 仿射密码
2.	密码学及应用：
- DES，
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
	typeMonoalphabetic
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
// 命令行提示
#pragma region

//	功能：密文对照表控制台输出显示
//  参数：outTable: 密文对照表
void ShowTable(const string &outTable)
{
	int i = 0;

	printf("明文和密文对照表\n");
	for (i = 0; i < CHAR_SIZE; i++)
	{
		printf("%c ", 'a' + i);
	}
	printf("\n");

	for (i = 0; i < CHAR_SIZE; i++)
	{
		printf("%c ", outTable[i]);
	}
	printf("\n");
}

//	功能：由密钥iKey生成密文对照表
//  参数：iKey: 密钥k; outTable: 密文对照表
//  备注：密文对照表均为大写字母
void ContrastTable(int iKey)
{
	int i = 0, k = 0;
	string AlphabetC;

	k = iKey % CHAR_SIZE;
	for (i = 0; i < CHAR_SIZE; i++)
	{
		AlphabetC.push_back('a' + i);
	}

	for (i = 0; i < CHAR_SIZE; i++)
	{
		AlphabetC[i] = AlphabetC[i] + k;
		if (AlphabetC[i] > 'z')
			AlphabetC[i] = AlphabetC[i] - 26;
	}
	ShowTable(AlphabetC);
}
#pragma endregion

// calculate and fill encrypt file
int EncodeFile(CipherType cipherType, string key)
{
	ifstream inFile(MSG_FILE);
	ofstream outFile(ENCRYPT_FILE);

	string lineMsg;
	string lineCipher;
	string lineDecodeMsg;
	BaseCipher *cipher;
	switch (cipherType)
	{
	case typeCaesar:
		cipher = new Caesar(key);
		break;
	
	default:
		break;
	}
	while (getline(inFile, lineMsg))
	{

		// 跳过UTF-8的BOM
		if (lineMsg.size() >= 3 && lineMsg[0] == char(0xEF) && lineMsg[1] == char(0xBB) && lineMsg[2] == char(0xBF))
		{
			lineMsg = lineMsg.substr(3);
		}

		cipher->encrypt(lineMsg, lineMsg.length(), lineCipher);
		outFile << lineCipher;
		outFile << "\n";
		cipher->decrypt(lineCipher, lineCipher.length(), lineDecodeMsg);

		if (lineDecodeMsg != lineMsg)
		{
			cout << "\ndecode:" << lineDecodeMsg << "\n";
			cout << "code:" << lineMsg << "\n";

			throw runtime_error("decode text is NOT equal with encode text\n");
			return -1;
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	string k = "3";
	// cin>>k;

	ContrastTable(3);
	EncodeFile(typeCaesar, k);
	return 0;
}
