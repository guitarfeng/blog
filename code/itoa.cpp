#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>

char* itoa(int value, char* result, int base) {
    //check that the base if valid
    if (base < 2 || base > 36) { 
        *result = '\0';
        return result; 
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) 
        *ptr++ = '-'; 

    *ptr-- = '\0';

    while(ptr1 < ptr) { 
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

std::string itoa(int value, int base) { 
    std::string buf;

    // check that the base if valid
    if (base < 2 || base > 16) return buf;

    enum { kMaxDigits = 35 };

    // Pre-allocate enough space.  
    buf.reserve(kMaxDigits);

    int quotient = value;

    // Translating number to string with base:
    do {
        std::cout << quotient % base << std::endl;
        buf += "0123456789abcdef"[ std::abs(quotient % base) ]; // incorrect
        quotient /= base;
    } while (quotient); 

    // Append the negative sign
    if (value < 0)
        buf += '-';

    std::reverse(buf.begin(), buf.end());
    return buf;
}

int main()
{
    int value;
    std::cin >> value;
    std::cout << itoa(value, 10);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << itoa(value, -10);
    return 0; 
}
