#include "HexToBin.h"

std::string hexToBinary(const std::string& hex)
{
    std::string binary;

    for (char c : hex) {
        // Перетворюємо кожен символ hex у число
        unsigned int n;
        std::stringstream ss;
        ss << std::hex << c;
        ss >> n;

        // Додаємо до двійкового рядка 4 біти (одна hex-цифра = 4 біти)
        binary += std::bitset<4>(n).to_string();
    }

    return binary;
}