- [Decimal to Binary](#decimal-to-binary)
  - [1. Brute Force Approach](#1-brute-force-approach)
    - [1.1. Print: Using arithmetic operators( O(logN) )](#11-print-using-arithmetic-operators-ologn-)
    - [1.2. Print: Using bitwise operators( O(1) )](#12-print-using-bitwise-operators-o1-)
    - [1.3. Return string: Using bitwise operators( O(logN) )](#13-return-string-using-bitwise-operators-ologn-)
    - [1.4. Return int( O(logN) )](#14-return-int-ologn-)
    - [1.5. std::bitset](#15-stdbitset)

<br><br>

# Decimal to Binary


## 1. Brute Force Approach
[ Greeks for Greeks - Program for Decimal to Binary Conversion ](https://www.geeksforgeeks.org/program-decimal-binary-conversion/)   

정수 10을 binary number로 변환해보자.   
1. 10을 2로 나누면 0이 남는다. 따라서 arr[0] = 0;
2. 5를 2로 나누면 1이 남는다. 따라서 arr[1] = 1;
3. 2를 2로 나누면 0이 남는다. 따라서 arr[2] = 0;
4. 1을 2로 나누면 1이 남는다. 따라서 arr[3] = 1;
5. 0이 남은 이후에는 array를 reverse해서 출력한다. 따라서 1010;

### 1.1. Print: Using arithmetic operators( O(logN) )
```cpp
#include <iostream>
using namespace std;

void decToBinary(int n) {
  int binaryNum[32];    // array to store binary number

  int i = 0;
  while (n > 0) {
    binaryNum[i] = n % 2;   // storing remainder in binary array
    n = n / 2;
    ++i;
  }

  // printing binary array in reverse order
  for (int j = i - 1; j >= 0; --j)
    cout << binaryNum[j];
}
```

### 1.2. Print: Using bitwise operators( O(1) )
int의 크기는 32bit로 가정한다   
```cpp
#include <iostream>
using namespace std;

void decToBinary(int n) {
  for (int i = 31; i >= 0; --i) {
    int k = n >> i;
    if (k & 1) cout << "1";
    else cout << "0";
  }
}
```
`(n >> i) & 1`은 최상위 비트( most significant bit, msb )부터 시작해서 최하위 비트( least significant bit, lsb )까지 n이 odd 값인지 확인한다   

### 1.3. Return string: Using bitwise operators( O(logN) )
```cpp
#include <string>
#include <algorithm>
using namespace std;

string decToBinary(int n) {
  string binary;
  while (n) {
    if (n & 1) str += '1';
    else       str += '0';
    n >>= 1;
  }

  reverse(binary.begin(), binary.end());  
  return binary;
}

int main() {
  int num = 59;
  string binary = decToBinary(num);       // 111011
}
```
`n & 1`로 정수의 첫 번째 자리가 1인지 판단하여 even, odd에 따라 1 또는 0을 string에 추가한다   
그 후 나머지 bit도 판단하기 위해서 right shift 연산으로 1칸 이동한다   
마지막에 reverse 함수를 사용해서 문자열의 순서를 뒤집는다   

### 1.4. Return int( O(logN) )
```cpp
#include <cmath>
using namespace std;

#define ull unsigned long long int

int decToBinary(int n) {
  ull B_Number = 0;     // To store the binary number;

  int cnt = 0;
  while (n) {
    int rem = n % 2;
    ull c = pow(10, cnt);
    B_Number += rem * c;
    n /= 2;
    ++cnt;      // Count used to store exponent( 지수 ) value
  }

  return B_Number;
}
```
`rem`은 0 또는 1을 나타내며, `c`는 정수의 자릿수를 나타낸다   

### 1.5. std::bitset