#include <string>
#include <windows.h>
#include <bcrypt.h>
#include <string>
#include <iostream>
#include "sha256.h"
#include "HexToBin.h"
#pragma comment(lib, "bcrypt.lib")
#define MESSAGE_SIZE 256

struct Pair 
{
	std::string firstNum;
	std::string secondNum;
};

int main()
{
	// ³�������� ������ ��������� ���� (256 ��� �����)
	// ��� ����� ����������� ������������ ��������� ���������� �����

	Pair* secretKey = new Pair[MESSAGE_SIZE];

	unsigned char buffer[4];
	unsigned int firstNum, secondNum;

	for (int i = 0; i < MESSAGE_SIZE; ++i)
	{
		BCryptGenRandom(NULL, buffer, sizeof(buffer), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
		firstNum = *reinterpret_cast<unsigned int*>(buffer);
		BCryptGenRandom(NULL, buffer, sizeof(buffer), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
		secondNum = *reinterpret_cast<unsigned int*>(buffer);
		secretKey[i].firstNum = std::to_string(firstNum);
		secretKey[i].secondNum = std::to_string(secondNum);
	}

	// ������ �� ����� � ����� ��� ��������� ��������� �����. ����������� SHA256

	Pair* openKey = new Pair[MESSAGE_SIZE];

	for (int i = 0; i < MESSAGE_SIZE; ++i)
	{
		openKey[i].firstNum = sha256(secretKey[i].firstNum);
		openKey[i].secondNum = sha256(secretKey[i].secondNum);
	}

	// ����� ����(��������) ���� �������� �����������, ��� ����� ���� ���� �������� ����
	// ���� ���� ������� � ���������� ��������� ���� �������� ����� � ���� ��������� �����

	std::string message = "�����!";

	std::string hashMessage = hexToBinary(sha256(message));

	std::string signature[MESSAGE_SIZE];

	// 0 - ����� �����, 1 - ����� � ���������� �����
	for (int i = 0; i < MESSAGE_SIZE; ++i)
	{
		if (hashMessage[i] == '0') { signature[i] = secretKey[i].firstNum; }
		else if (hashMessage[i] == '1') { signature[i] = secretKey[i].secondNum; }
	}

	// ���� ������� ���� ����������� ����� �� �������
	// ��� �������� �����, ��� ����� �� ����� ���� �����������
	// ���� ��� ��� ������� ��� ���� ����� �������� �������� � ��������� �����

	std::string testArray[MESSAGE_SIZE];

	for (int i = 0; i < MESSAGE_SIZE; ++i)
	{
		if (hashMessage[i] == '0') { testArray[i] = openKey[i].firstNum; }
		else if (hashMessage[i] == '1') { testArray[i] = openKey[i].secondNum; }
	}

	// ��� ��� ���� ����� ����

	std::string hashSignature[MESSAGE_SIZE];

	for (int i = 0; i < MESSAGE_SIZE; ++i) hashSignature[i] = sha256(signature[i]);

	// ����� ��� ��������, �� ������� �������� ����� �� ��������� ������� ����, ���� ���, �� �� ����� ����������� ����
	bool isOk = true;

	for (int i = 0; i < MESSAGE_SIZE; ++i) 
	{
		if (testArray[i] != hashSignature[i])
		{
			isOk = false;
			break;
		}
	}

	if (isOk) std::cout << "Ok" << std::endl;
	else std::cout << "Not Alice" << std::endl;

	return 0;
}