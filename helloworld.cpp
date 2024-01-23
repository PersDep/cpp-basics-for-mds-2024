#include <iostream>
#include <string>
#include <vector>
// import iostream
// python program starts here

// a = 0
// int a = 0;
int64_t a = 0;

// 8 bits, 1 byte, int8_t ; range from -128 to 127 == 2^7 - 1
// 16 bits, 2 bytes, int16_t ; range from -32768 to 32767 == 2^15 - 1
// 32 bits, 4 bytes, int32_t ; range from -2147483648 to 2147483647
// 64 bits, 8 bytes, int64_t ; range from -9223372036854775808 to 9223372036854775807

uint8_t b = 10; // 1 byte ; range from 0 to 255 == 2^8 - 1
uint16_t c = 10; // 2 bytes ; range from 0 to 65535 == 2^16 - 1
uint32_t d = 10; // 4 bytes ; range from 0 to 4294967295
uint64_t e = 10; // 8 bytes ; range from 0 to 18446744073709551615


// using namespace std;

int main(void)
{
    // C++ program starts here

    // auto b = 10;

    int8_t x = 200;
    // 128 == -128
    // 129 == -127
    // 130 == -126
    x = x + 1;
    std::cout << "X = " << (int)x << std::endl;

    std::vector<int64_t> v = {1, 2, 3, 4, 5};

    // int = int32_t
    // int = int64_T

    //each object in C++ is just a set of bytes
    // s.push_back(1);

    int x2 = int8_t();

    std::cout << "X = " << (int)x2 << std::endl;

    float x1 = 10.1; // 32 bits
    double y = 10.1; // 64 bits float in python is 64 bits
    char c = 'a'; auto d = 'aaaaa';
    wchar_t f = L'ф';

    auto e = "ффффффф";

    // std::string s = "aaaaa";

    // std::wstring w = L"ффффф";

    std::cout << "Hello my World! " << std::endl << c << " " << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    // std::cout << w << std::endl;
    // std::cout << s << std::endl;

    // printf("Hello my World!\n");
    // printf("Hello my World! X = %c X1 = %f\n", x, x1);

    // std::cout << "Hello my World!" << std::endl;

    // std::cout << "Sizes: " << sizeof(a) << " " << sizeof(int) << " " << sizeof(int64_t) << std::endl;

    // a = a + 1;

    // std::cout << "a: " << a << std::endl;
    // print("a:", a)

    return 0;
}
