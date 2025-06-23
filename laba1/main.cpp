#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <sstream>
#include <stdexcept>

using namespace std;

// Вспомогательные функции
string decimalToBinary(int n, int bitLength = 0) {
    if (n == 0) {
        return bitLength ? string(bitLength, '0') : "0";
    }
    string binary;
    while (n > 0) {
        binary = to_string(n % 2) + binary;
        n /= 2;
    }
    if (bitLength > 0) {
        if (binary.length() < bitLength) {
            binary = string(bitLength - binary.length(), '0') + binary;
        } else if (binary.length() > bitLength) {
            binary = binary.substr(binary.length() - bitLength);
        }
    }
    return binary;
}

int binaryToDecimal(const string& binaryStr) {
    int decimal = 0;
    for (size_t i = 0; i < binaryStr.length(); i++) {
        decimal += (binaryStr[i] - '0') * pow(2, binaryStr.length() - 1 - i);
    }
    return decimal;
}

int twosComplementToDecimal(const string& binaryStr) {
    int bitLength = binaryStr.length();
    int unsignedVal = binaryToDecimal(binaryStr);
    if (binaryStr[0] == '0') {
        return unsignedVal;
    } else {
        return unsignedVal - (1 << bitLength);
    }
}

// Функции представления чисел
string getPositiveCode(int n, int bitLength) {
    string binaryStr = decimalToBinary(n, bitLength - 1);
    return "0" + binaryStr;
}

string getNegativeCode(int n, int bitLength) {
    string binaryStr = decimalToBinary(abs(n), bitLength - 1);
    return "1" + binaryStr;
}

string getReverseCode(int n, int bitLength) {
    if (n >= 0) {
        return getPositiveCode(n, bitLength);
    }
    string posCode = decimalToBinary(abs(n), bitLength - 1);
    string inverted;
    for (char bit : posCode) {
        inverted += (bit == '0') ? '1' : '0';
    }
    return "1" + inverted;
}

string getAdditionalCode(int n, int bitLength) {
    if (n >= 0) {
        return getPositiveCode(n, bitLength);
    }
    string rev = getReverseCode(n, bitLength);
    int carry = 1;
    string additional;
    for (int i = rev.length() - 1; i >= 0; i--) {
        int total = (rev[i] - '0') + carry;
        additional = to_string(total % 2) + additional;
        carry = total / 2;
    }
    return additional;
}

// Арифметические операции
string binaryAdd(const string& a, const string& b) {
    int maxLen = max(a.length(), b.length());
    string aPadded = a;
    string bPadded = b;
    aPadded.insert(0, maxLen - a.length(), '0');
    bPadded.insert(0, maxLen - b.length(), '0');
    
    int carry = 0;
    string result;
    for (int i = maxLen - 1; i >= 0; i--) {
        int sumBit = (aPadded[i] - '0') + (bPadded[i] - '0') + carry;
        result = to_string(sumBit % 2) + result;
        carry = sumBit / 2;
    }
    if (carry) result = "1" + result;
    return result;
}

string binarySubtract(const string& a, const string& b) {
    int maxLen = max(a.length(), b.length());
    string aPadded = a;
    string bPadded = b;
    aPadded.insert(0, maxLen - a.length(), '0');
    bPadded.insert(0, maxLen - b.length(), '0');
    
    string result;
    int borrow = 0;
    for (int i = maxLen - 1; i >= 0; i--) {
        int diff = (aPadded[i] - '0') - (bPadded[i] - '0') - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result = to_string(diff) + result;
    }
    // Удаляем ведущие нули
    size_t firstOne = result.find_first_not_of('0');
    if (firstOne != string::npos) {
        result = result.substr(firstOne);
    } else {
        result = "0";
    }
    return result;
}

int binaryCompare(const string& a, const string& b) {
    string aTrimmed = a;
    string bTrimmed = b;
    aTrimmed.erase(0, aTrimmed.find_first_not_of('0'));
    bTrimmed.erase(0, bTrimmed.find_first_not_of('0'));
    if (aTrimmed.empty()) aTrimmed = "0";
    if (bTrimmed.empty()) bTrimmed = "0";
    
    if (aTrimmed.length() > bTrimmed.length()) return 1;
    if (aTrimmed.length() < bTrimmed.length()) return -1;
    if (aTrimmed > bTrimmed) return 1;
    if (aTrimmed < bTrimmed) return -1;
    return 0;
}

string addInAdditionalCode(int a, int b, int bitLength) {
    string aCode = getAdditionalCode(a, bitLength);
    string bCode = getAdditionalCode(b, bitLength);
    return binaryAdd(aCode, bCode);
}

string subtractInAdditionalCode(int a, int b, int bitLength) {
    return addInAdditionalCode(a, -b, bitLength);
}

string multiplyInDirectCode(int a, int b, int bitLength) {
    char signA = a >= 0 ? '0' : '1';
    char signB = b >= 0 ? '0' : '1';
    string magA = decimalToBinary(abs(a), bitLength - 1);
    string magB = decimalToBinary(abs(b), bitLength - 1);
    
    string product = "0";
    for (int i = magB.length() - 1; i >= 0; i--) {
        if (magB[i] == '1') {
            string partial = magA + string(magB.length() - 1 - i, '0');
            product = binaryAdd(product, partial);
        }
    }
    product = string(bitLength - 1 - product.length(), '0') + product;
    char resultSign = (signA == signB) ? '0' : '1';
    return string(1, resultSign) + product;
}

pair<string, double> divideInDirectCode(int a, int b, int precision = 5, int intBitLength = 8) {
    if (b == 0) {
        return make_pair("Ошибка: деление на ноль", 0.0);
    }
    
    char resultSign = ((a >= 0 && b > 0) || (a < 0 && b < 0)) ? '0' : '1';
    string dividend = decimalToBinary(abs(a));
    string divisor = decimalToBinary(abs(b));
    
    string quotient;
    string temp;
    for (char bit : dividend) {
        temp += bit;
        // Удаляем ведущие нули
        size_t firstOne = temp.find_first_not_of('0');
        if (firstOne != string::npos) {
            temp = temp.substr(firstOne);
        } else {
            temp = "0";
        }
        
        if (binaryCompare(temp, divisor) >= 0) {
            quotient += "1";
            temp = binarySubtract(temp, divisor);
        } else {
            quotient += "0";
        }
    }
    
    // Удаляем ведущие нули в частном
    size_t firstOne = quotient.find_first_not_of('0');
    if (firstOne != string::npos) {
        quotient = quotient.substr(firstOne);
    } else {
        quotient = "0";
    }
    
    string remainder = temp;
    string fractional;
    for (int i = 0; i < precision; i++) {
        remainder += "0";
        // Удаляем ведущие нули
        size_t firstOne = remainder.find_first_not_of('0');
        if (firstOne != string::npos) {
            remainder = remainder.substr(firstOne);
        } else {
            remainder = "0";
        }
        
        if (binaryCompare(remainder, divisor) >= 0) {
            fractional += "1";
            remainder = binarySubtract(remainder, divisor);
        } else {
            fractional += "0";
        }
    }
    
    string intPart = string(intBitLength - 1 - quotient.length(), '0') + quotient;
    string directInt = string(1, resultSign) + intPart;
    string finalResult = directInt + "." + fractional;
    
    int decInt = binaryToDecimal(quotient);
    double fracVal = 0.0;
    for (size_t i = 0; i < fractional.length(); i++) {
        if (fractional[i] == '1') {
            fracVal += 1.0 / pow(2, i + 1);
        }
    }
    double decResult = decInt + fracVal;
    if (resultSign == '1') decResult = -decResult;
    
    return make_pair(finalResult, decResult);
}

// IEEE754 функции
string convertFloatToIEEE754(float num) {
    if (num == 0.0f) return string(32, '0');
    
    // Определяем знак
    char signBit = (num < 0) ? '1' : '0';
    num = abs(num);
    
    // Разделяем на целую и дробную части
    int intPart = static_cast<int>(num);
    float fracPart = num - intPart;
    
    // Преобразуем целую часть в двоичную
    string binInt;
    if (intPart == 0) {
        binInt = "0";
    } else {
        int temp = intPart;
        while (temp > 0) {
            binInt = to_string(temp % 2) + binInt;
            temp /= 2;
        }
    }
    
    // Преобразуем дробную часть в двоичную
    string binFrac;
    float tempFrac = fracPart;
    for (int i = 0; i < 30; i++) {
        tempFrac *= 2;
        if (tempFrac >= 1) {
            binFrac += "1";
            tempFrac -= 1;
        } else {
            binFrac += "0";
        }
    }
    
    // Вычисляем экспоненту и мантиссу
    int exponent;
    string mantissa;
    
    if (binInt != "0") {
        // Нормализованное число
        exponent = binInt.length() - 1;
        mantissa = binInt.substr(1) + binFrac;
    } else {
        // Денормализованное число
        int firstOnePos = binFrac.find('1');
        if (firstOnePos == string::npos) {
            // Ноль
            return string(32, '0');
        }
        exponent = -(firstOnePos + 1);
        mantissa = binFrac.substr(firstOnePos + 1);
    }
    
    // Смещенная экспонента
    int expBias = exponent + 127;
    string expBits = decimalToBinary(expBias, 8);
    
    // Мантисса (23 бита)
    mantissa = mantissa.substr(0, 23);
    while (mantissa.length() < 23) {
        mantissa += "0";
    }
    
    return signBit + expBits + mantissa;
}

float ieee754ToDecimal(const string& ieee) {
    if (ieee.length() != 32) {
        throw invalid_argument("IEEE754 строка должна быть длиной 32 бита");
    }
    
    // Знак
    float sign = (ieee[0] == '0') ? 1.0f : -1.0f;
    
    // Экспонента
    int exponent = 0;
    for (int i = 1; i <= 8; i++) {
        exponent = exponent * 2 + (ieee[i] - '0');
    }
    exponent -= 127;
    
    // Мантисса
    float mantissa = 1.0f;
    for (int i = 9; i < 32; i++) {
        if (ieee[i] == '1') {
            mantissa += pow(2, -(i - 8));
        }
    }
    
    // Специальные случаи
    if (exponent == -127 && mantissa == 1.0f) {
        return 0.0f * sign; // Ноль
    }
    if (exponent == 128) {
        if (mantissa == 1.0f) {
            return numeric_limits<float>::infinity() * sign; // Бесконечность
        } else {
            return numeric_limits<float>::quiet_NaN(); // NaN
        }
    }
    
    return sign * mantissa * pow(2, exponent);
}

string addIEEE754(const string& bin1, const string& bin2) {
    if (bin1.length() != 32 || bin2.length() != 32) {
        throw invalid_argument("Оба числа должны быть 32-битными");
    }
    
    // Извлекаем знаки
    int sign1 = (bin1[0] == '0') ? 0 : 1;
    int sign2 = (bin2[0] == '0') ? 0 : 1;
    
    // Извлекаем экспоненты
    int exp1 = 0, exp2 = 0;
    for (int i = 1; i <= 8; i++) {
        exp1 = exp1 * 2 + (bin1[i] - '0');
        exp2 = exp2 * 2 + (bin2[i] - '0');
    }
    
    // Извлекаем мантиссы (с неявной ведущей 1)
    int mant1 = (1 << 23) + stoi(bin1.substr(9), nullptr, 2);
    int mant2 = (1 << 23) + stoi(bin2.substr(9), nullptr, 2);
    
    // Выравниваем экспоненты
    int exp = exp1;
    if (exp1 > exp2) {
        int shift = exp1 - exp2;
        mant2 >>= shift;
    } else if (exp2 > exp1) {
        int shift = exp2 - exp1;
        mant1 >>= shift;
        exp = exp2;
    }
    
    // Выполняем сложение/вычитание
    int resultMant, resultSign;
    if (sign1 == sign2) {
        resultMant = mant1 + mant2;
        resultSign = sign1;
    } else {
        if (mant1 >= mant2) {
            resultMant = mant1 - mant2;
            resultSign = sign1;
        } else {
            resultMant = mant2 - mant1;
            resultSign = sign2;
        }
    }
    
    // Нормализация результата
    if (resultMant == 0) {
        return string(32, '0');
    }
    
    while (resultMant >= (1 << 24)) {
        resultMant >>= 1;
        exp += 1;
    }
    
    while (resultMant < (1 << 23)) {
        resultMant <<= 1;
        exp -= 1;
    }
    
    // Проверка на переполнение экспоненты
    if (exp >= 255) {
        // Бесконечность
        return string(1, resultSign + '0') + string(8, '1') + string(23, '0');
    }
    
    // Формируем результат
    string result;
    result += to_string(resultSign);
    
    string expBits = decimalToBinary(exp, 8);
    result += expBits;
    
    string fracBits = decimalToBinary(resultMant - (1 << 23), 23);
    result += fracBits;
    
    return result;
}

// Вспомогательная функция для ввода чисел
int inputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число\n";
        } else {
            break;
        }
    }
    return value;
}

float inputFloat(const string& prompt) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число\n";
        } else {
            break;
        }
    }
    return value;
}

int main() {
    cout << "Введите два целых числа для анализа\n";
    
    int num1 = inputInt("Первое число: ");
    int num2 = inputInt("Второе число: ");
    
    const int bitLength = 8;
    cout << "\nБитовая длина представления: " << bitLength << " бит\n";
    
    // Вывод представлений для первого числа
    cout << "\nПредставления первого числа:\n";
    if (num1 > 0) {
        cout << "Прямой код: " << getPositiveCode(num1, bitLength) << endl;
    } else {
        cout << "Прямой код: " << getNegativeCode(num1, bitLength) << endl;
    }
    cout << "Обратный код: " << getReverseCode(num1, bitLength) << endl;
    cout << "Дополнительный код: " << getAdditionalCode(num1, bitLength) << endl;
    
    // Вывод представлений для второго числа
    cout << "\nПредставления второго числа:\n";
    if (num2 > 0) {
        cout << "Прямой код: " << getPositiveCode(num2, bitLength) << endl;
    } else {
        cout << "Прямой код: " << getNegativeCode(num2, bitLength) << endl;
    }
    cout << "Обратный код: " << getReverseCode(num2, bitLength) << endl;
    cout << "Дополнительный код: " << getAdditionalCode(num2, bitLength) << endl;
    
    // Арифметические операции
    cout << "\nРезультаты арифметических операций:\n";
    
    // Сложение
    string sumResult = addInAdditionalCode(num1, num2, bitLength);
    cout << "\nСложение (" << num1 << " + " << num2 << "):\n";
    cout << "Дополнительный код: " << sumResult << endl;
    cout << "Десятичный результат: " << twosComplementToDecimal(sumResult) << endl;
    
    // Вычитание
    string subResult = subtractInAdditionalCode(num1, num2, bitLength);
    cout << "\nВычитание (" << num1 << " - " << num2 << "):\n";
    cout << "Дополнительный код: " << subResult << endl;
    cout << "Десятичный результат: " << twosComplementToDecimal(subResult) << endl;
    
    cout << "\nТестирование умножения в прямом коде:\n";
    string mulCode = multiplyInDirectCode(num1, num2, 8);
    
    auto directCodeToDecimal = [](const string& directStr) {
        if (directStr[0] == '0') {
            return binaryToDecimal(directStr.substr(1));
        } else {
            return -binaryToDecimal(directStr.substr(1));
        }
    };
    
    cout << "Умножение " << num1 << " и " << num2 << ":\n";
    cout << "Результат (bin): " << mulCode << endl;
    cout << "Результат (dec): " << directCodeToDecimal(mulCode) << endl;
    
    if (num2 == 0) {
        cout << "\nДеление на ноль невозможно!\n";
    } else {
        auto [divResult, divDec] = divideInDirectCode(num1, num2, 5, bitLength);
        cout << "\nДеление (" << num1 << " / " << num2 << "):\n";
        cout << "Прямой код: " << divResult << endl;
        cout << "Десятичный результат: " << fixed << setprecision(5) << divDec << endl;
    }
    
    cout << "\nТестирование сложения чисел с плавающей точкой по IEEE-754:\n";
    float a = inputFloat("Введите первое число (например, 3.3): ");
    float b = inputFloat("Введите второе число (например, 4.9): ");
    
    string ieeeA = convertFloatToIEEE754(a);
    string ieeeB = convertFloatToIEEE754(b);
    
    cout << "\nПредставление чисел в IEEE-754 (32 бит):\n";
    cout << "A = " << a << " -> " << ieeeA << endl;
    cout << "B = " << b << " -> " << ieeeB << endl;
    
    string ieeeResult = addIEEE754(ieeeA, ieeeB);
    cout << "\nРезультат сложения в формате IEEE-754 (32 бит):\n";
    cout << ieeeResult << endl;
    
    float decResult = ieee754ToDecimal(ieeeResult);
    cout << "\nРезультат сложения (десятичное значение):\n";
    cout << decResult << endl;
    
    return 0;
}
