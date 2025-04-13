#include "HexToBin.h"

std::string hexToBinary(const std::string& hex)
{
    std::string binary;

    for (char c : hex) {
        // ������������ ����� ������ hex � �����
        unsigned int n;
        std::stringstream ss;
        ss << std::hex << c;
        ss >> n;

        // ������ �� ��������� ����� 4 ��� (���� hex-����� = 4 ���)
        binary += std::bitset<4>(n).to_string();
    }

    return binary;
}