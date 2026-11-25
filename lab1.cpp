#include <iostream>
#include <limits>
#include <bitset>
#include <cstring>
#include <string>
using namespace std;

void sizes()
{
    bool booltype;
    char chartype;
    short int shortinttype;
    int inttype;
    long int longinttype;
    float floattype;
    double doubletype;
    long double longdoubletype;

    cout << "Размеры типов данных:" << endl;
    cout << "Тип bool: " << sizeof(booltype) << " байт" << endl;
    cout << "Тип char: " << sizeof(chartype) << " байт" << endl;
    cout << "Тип short int: " << sizeof(shortinttype) << " байт" << endl;
    cout << "Тип int: " << sizeof(inttype) << " байт" << endl;
    cout << "Тип long int: " << sizeof(longinttype) << " байт" << endl;
    cout << "Тип float: " << sizeof(floattype) << " байт" << endl;
    cout << "Тип double: " << sizeof(doubletype) << " байт" << endl;
    cout << "Тип long double: " << sizeof(longdoubletype) << " байт\n" << endl;
}



void green(string text) {
    cout << "\033[32m" << text << "\033[0m";
}
void red(string text) {
    cout << "\033[31m" << text << "\033[0m";
}

void bits_signed(signed int a) {
    string binary = bitset<32>(a).to_string();

    if (a > 0) {
        cout << "Двоичное представление числа " << a << ":\n";
        green("0");
        cout << binary.substr(1, 31) << endl;

        cout << "Цветом помечен знаковой бит йоу" << endl;

    } 
    else if (a < 0) { 
        cout << "Двоичное представление числа " << a << ":\n";
        red("1");
        cout << binary.substr(1, 31) << endl;

        cout << "Цветом помечен знаковой бит йоу" << endl;

    }
    else {
        cout << "Двоичное представление числа " << a << ": " << binary << endl;
    }
    
}

void bits_unsigned(unsigned int a) {
    string binary = bitset<32>(a).to_string();
    cout << "Двоичное представление числа " << a << ":\n" << binary << endl;
}



void float_bits(float num) {
    unsigned int bits;
    memcpy(&bits, &num, sizeof(num));
    string binary = bitset<32>(bits).to_string();

    cout << binary.substr(0, 1) << " | "
        << binary.substr(1, 8) << " | "
        << binary.substr(9) << endl;
    cout << "Знаковый бит: " << binary.substr(0,1) << endl;
    cout << "Степень: " << binary.substr(1,8) << " (8 бит)" << endl;
    cout << "Мантисса: " << binary.substr(9) << " (23 бита)\n" << endl;
}

void double_bits(double num) {
    unsigned long long int bits;
    memcpy(&bits, &num, sizeof(num));
    string binary = bitset<64>(bits).to_string();

    cout << binary.substr(0, 1) << " | "
         << binary.substr(1, 11) << " | "
         << binary.substr(12) << endl;
    cout << "Знаковый бит: " << binary.substr(0, 1) << endl;
    cout << "Степень: " << binary.substr(1, 11) << " (11 бит)" << endl;
    cout << "Мантисса: " << binary.substr(12) << " (52 бита)\n" << endl;
}



int change_bit(int x, int pos, char op) {
    unsigned int u = x;              // те же 32 бита, но без знака
    unsigned int mask = 1u << pos;   // единица, сдвинутая на pos мест

    if (op == 's') u |= mask;        // установить бит
    else if (op == 'r') u &= ~mask;  // сбросить бит
    else if (op == 't') u ^= mask;   // инвертировать бит

    return (int)u;                   // обратно в знаковое
}

float change_float_bit(float num, int pos, char op) {
    unsigned int bits;
    memcpy(&bits, &num, sizeof(num));   
    bits = change_bit(bits, pos, op);  
    memcpy(&num, &bits, sizeof(num));   
    return num;
}

double change_double_bit(double num, int pos, char op) {
    unsigned long long bits;                
    memcpy(&bits, &num, sizeof(num));       

    unsigned long long mask = 1ULL << pos;  
    if (op == 's') bits |= mask;            
    else if (op == 'r') bits &= ~mask;     
    else if (op == 't') bits ^= mask;    

    memcpy(&num, &bits, sizeof(num));      
    return num;
}

int make_odd(int x) {
    unsigned int u = x;   // те же 32 бита, но без знака
    u |= 1u;              // младший бит (бит 0) = 1
    return (int)u;        // обратно в знаковое
}

int main()
{
    cout << "=== Размеры типов данных ===" << endl;
    sizes();


    cout << "=== Двоичное представление: целые числа ===" << endl;

    cout << "\n--- unsigned ---" << endl;
    cout << "\nunsigned 0:" << endl;
    bits_unsigned(0);

    cout << "\nunsigned 5:" << endl;
    bits_unsigned(5);

    cout << "\nUnsigned использует все биты для хранения величины числа, поэтому нет знакового бита" << endl;

    cout << "\n--- signed ---" << endl;
    cout << "\nsigned 5 (положительное):" << endl;
    bits_signed(5);

    cout << "\nsigned -5 (отрицательное):" << endl;
    bits_signed(-5);

    cout << "\nsigned 0 (ноль, знакового бита нет):" << endl;
    bits_signed(0);

    cout << "\nSigned кодируется с помощью дополнительного кода, поэтому можно выделить знаковый бит (кроме нуля)" << endl;



    cout << "\n=== Двоичное представление: float и double ===" << endl;

    cout << "Число 3.14 вида float:" << endl;
    float_bits(3.14f);

    cout << "Число -2.5 вида double:" << endl;
    double_bits(-2.5);

    cout << "Число 0.0 вида double:" << endl;
    double_bits(0.0);

    cout << "Денормализованное число" << endl;
    float denorm_num = numeric_limits<float>::denorm_min();
    float_bits(denorm_num);

    cout << "Inf" << endl;
    float positive_inf = numeric_limits<float>::infinity();
    float_bits(positive_inf);




    cout << "\n=== Манипуляция битами: целые числа ===" << endl;

    cout << "\nЧисло 5, установка бита 1 (ожидаем 7):" << endl;
    bits_signed(5);
    bits_signed(change_bit(5, 1, 's'));

    cout << "\nЧисло 5, сброс бита 0 (ожидаем 4):" << endl;
    bits_signed(5);
    bits_signed(change_bit(5, 0, 'r'));

    cout << "\nЧисло 5, инверсия бита 2 (ожидаем 1):" << endl;
    bits_signed(5);
    bits_signed(change_bit(5, 2, 't'));

    cout << "\nЧисло -3, сброс бита 31 (знак пропадает, ожидаем 2147483645):" << endl;
    bits_signed(-3);
    bits_signed(change_bit(-3, 31, 'r'));





    cout << "\n=== Манипуляция битами: float ===" << endl;

    cout << "\nfloat 3.14, инверсия бита 31 (знак, ожидаем -3.14):" << endl;
    float_bits(3.14f);
    float_bits(change_float_bit(3.14f, 31, 't'));

    cout << "float 3.14, установка бита 23 (порядок +1, ожидаем 6.28):" << endl;
    float_bits(3.14f);
    float_bits(change_float_bit(3.14f, 23, 's'));


    cout << "\n=== Манипуляция битами: double ===" << endl;

    cout << "\ndouble -2.5, инверсия бита 63 (знак, ожидаем 2.5):" << endl;
    double_bits(-2.5);
    double_bits(change_double_bit(-2.5, 63, 't'));

    cout << "double -2.5, установка бита 52 (порядок +1, ожидаем -5.0):" << endl;
    double_bits(-2.5);
    double_bits(change_double_bit(-2.5, 52, 's'));




    cout << "\n=== Индивидуальное задание: сделать число нечётным ===" << endl;

    cout << "\nЧисло 4 (ожидаем 5):" << endl;
    bits_signed(4);
    bits_signed(make_odd(4));

    cout << "\nЧисло -4 (ожидаем -3):" << endl;
    bits_signed(-4);
    bits_signed(make_odd(-4));
    
}
