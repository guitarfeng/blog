Find Number of 1s. [(Hamming weight)](http://en.wikipedia.org/wiki/Hamming_weight)
=============================
Efficient way to count number of 1s in the binary representation of a
number in O(1) if you have enough memory to play with.

一共有三种方法

### 定长位运算
<pre class="prettyprint"> 
//types and constants used in the functions below
 
typedef unsigned __int64 uint64;  //assume this gives 64-bits
const uint64 m1  = 0x5555555555555555; //binary: 0101...
const uint64 m2  = 0x3333333333333333; //binary: 00110011..
const uint64 m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64 m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64 m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64 m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64 hff = 0xffffffffffffffff; //binary: all ones
const uint64 h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...
 
//This is a naive implementation, shown for comparison,
//and to help in understanding the better functions.
//It uses 24 arithmetic operations (shift, add, and).
int popcount_1(uint64 x) {
    x = (x & m1 ) + ((x >>  1) & m1 ); //put count of each  2 bits into those  2 bits 
    x = (x & m2 ) + ((x >>  2) & m2 ); //put count of each  4 bits into those  4 bits 
    x = (x & m4 ) + ((x >>  4) & m4 ); //put count of each  8 bits into those  8 bits 
    x = (x & m8 ) + ((x >>  8) & m8 ); //put count of each 16 bits into those 16 bits 
    x = (x & m16) + ((x >> 16) & m16); //put count of each 32 bits into those 32 bits 
    x = (x & m32) + ((x >> 32) & m32); //put count of each 64 bits into those 64 bits 
    return x;
}
 
//This uses fewer arithmetic operations than any other known  
//implementation on machines with slow multiplication.
//It uses 17 arithmetic operations.
int popcount_2(uint64 x) {
    x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
    x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    x += x >>  8;  //put count of each 16 bits into their lowest 8 bits
    x += x >> 16;  //put count of each 32 bits into their lowest 8 bits
    x += x >> 32;  //put count of each 64 bits into their lowest 8 bits
    return x & 0x7f;
}
 
//This uses fewer arithmetic operations than any other known  
//implementation on machines with fast multiplication.
//It uses 12 arithmetic operations, one of which is a multiply.
int popcount_3(uint64 x) {
    x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
    x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    return (x * h01)>>56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}
</pre> 

### least significant nonzero bit (depends on the number of 1s)
<pre class="prettyprint"> 
int popcount_4(uint64 x) {
    int count; 
    for (count=0; x; count++) 
        x &= x-1; 
    return count; 
}
</pre> 

### 查表法(unlimited memory)
<pre class="prettyprint"> 
static unsigned char wordbits[65536] = { bitcounts of ints between 0 and 65535 };
static int popcount(uint32 i)
{
    return (wordbits[i&0xFFFF] + wordbits[i>>16]);
}
</pre> 


Next Largest Smaller && Smallest Larger Number
=============================
Given a number, find the next higher number which has the exact same
set of digits as the original number. For example: given 38276 return
38627.

Here's an example:

```
123456784987654321
start with a number

123456784 987654321
         ^ the first place where the left-digit is less-than the
         right-digit is here.  Digit "x" is 4

123456784 987654321
         ^ find the smallest digit larger than 4 to the right

123456785 4 98764321
         ^ place it to the left of 4

123456785 4 12346789
123456785123446789
         ^ sort the digits to the right of 5.  Since all of them except
         the '4' were already in descending order, all we need to do
         is reverse their order, and find the correct place for the '4'
```
Here's the Code: 
<pre class="prettyprint"> 
</pre> 

```
Given an integer, print the next smallest and next largest number
that have the same number of 1 bits in their binary representation.
```
Here is a detailed
[Explanation](http://www.slideshare.net/gkumar007/bits-next-higher-presentation).

### Alogrithm
- Given a bit-pattern, start from right, find succesive zeros.
  (xxxx01111_0000);
- Folowed by zeroes find succesive 1's, stop on hitting a zero (xxxx0_1111 0000);
- Interchange that zero with a 1 from successive 1's (xxxx10_111 0000);
- Move the remaining 1's to extreme right, filling the gap with zeros
  (xxxx10 0000 111).  

Here is the Code:
<pre class="prettyprint">
unsigned foo(unsigned x) {
    unsigned last_one = x & (-x);  // 从右到左第一个1
    unsigned y = x + last_one;     // set 1
    unsigned z = (y ^ x) >> 2 / last_one; // 取剩下的1
    return y | z;
}
</pre> 


Determine if is Palindrome
===========================
- If input is a number, reverse the number from right to left.
- If input is a string, varify from two sides of the string.

<pre class="prettyprint">

</pre> 

itoa, atoi
===========================
base, negative. 
关于负数取模运算，不同语言定义不同。参考[负数的取模运算](http://www.googies.info/blog/184.html)。

char *itoa (int value, char *str, int base);

int atoi (const char * str); 

<pre class="prettyprint">
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
</pre> 

<pre class="prettyprint">
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
</pre> 

Add 2 numbers without using + or arithmetic operators
===========================
Write a function Add() that returns sum of two integers. The
function should not use any of the arithmetic operators (+, ++, -, --,
.. etc).  Sum of two bits can be obtained by performing XOR (\^) of
the two bits.  Carry bit can be obtained by performing AND (\&) of two
bits.

Above is simple Half Adder logic that can be used to add 2 single
bits. We can extend this logic for integers. If x and y don’t have set
bits at same position(s), then bitwise XOR (\^) of x and y gives the
sum of x and y. To incorporate common set bits also, bitwise AND (\&)
is used. Bitwise AND of x and y gives all carry bits. We calculate 
(x &amp; y) &lt;&lt; 1 and add it to x ^ y to get the required result.  

<pre class="prettyprint">
int Add(int x, y)
{
    // Iterate till there is no carry 
    while (y != 0)
    {
        // carry now contains common set bits of x and y
        int carry = x & y; 
 
        // Sum of bits of x and y where at least one of the bits is not set
        x = x ^ y;
 
        // Carry is shifted by one so that adding it to x gives the required sum
        y = carry << 1;
    }
    return x;
}

int main()
{
    printf("%d", Add(15, 32));
    return 0;
}

//Following is recursive implementation for the same approach.

int Add(int x, int y)
{
    if (y == 0)
        return x;
    else
        return Add( x ^ y, (x & y) << 1);
}
</pre> 


Implement *, -, / using only +
===========================
+  n * a = a + a + a + ... + a



### Substract Only Using Increase and Loop
We have only two constructs, loop(a) means loop for a times,
increment(a) increments a.
Thus to implement a+b one could write 

    loop(a) {
        inc(b)
    } 
    return b;

The question is how to implement a-b.

Hint: If we can figure out dec(n) function, it's done.

<pre class="prettyprint">
    DEC(n) {
        cur = 0
        loop (n) {
            pre = cur
            inc(cur)
        }
        /* Here cur == n, pre == n-1 */
        return pre
    }

    /* a-b */
    SUB(a, b) {
        loop(b) {
            DEC(a)
        }
    } 
</pre> 

find max of two numbers without comparison
===========================
<pre class="prettyprint">
int getMax(int a, int b) {  
    int c = a - b;  
    int k = (c >> 31) & 0x1;  
    return a -  k * (a - b);  
}
</pre> 

swap two numbers with +/-
===========================
<pre class="prettyprint">
void swap(int &a, int &b) { 
    a = a + b;
    b = a - b;
    a = a - b;
    return;
}
</pre> 

swap two numbers with ^
===========================
<pre class="prettyprint">
void swap(int &a, int &b) { 
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    return;
}
</pre> 

given an integer, find the closest number that is palindrome
===========================
http://www.geeksforgeeks.org/given-a-number-find-next-smallest-palindrome-larger-than-this-number/
<pre class="prettyprint">
</pre> 

implement putlong() by putchar()
===========================
Here is a popular interview question: write a C/C++ function which
outputs a long integer to the console:

    void putlong(long number);

To make it harder, the interview often specifies the following restrictions: 
+ You can only use putchar(char c) as your only mean of outputing to the console 
+ Do not create a string buffer to store the digits (this is necessary to reverse the order of the digits) 
+ No stack to reverse the digits 
+ No recursion allowed


Hint: in place reverse number.  
<pre class="prettyprint">
</pre> 

