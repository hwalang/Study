# Palindrome Number
[leetcode](https://leetcode.com/problems/palindrome-number/solutions/3651712/2-method-s-c-java-python-beginner-friendly/)   

숫자를 문자열로 바꿔서 푸는 방법과 숫자 그대로 사용해서 푸는 방법이 존재한다.   
여기서 숫자로만 풀어봤는데, 하위권 효율이 나왔기 때문에 다른 사람의 풀이를 보고 메모한다.   

# 풀이
## ME
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        // x의 자릿수를 vector에 저장해서, sqrt(size)까지 탐색하면서 비교
        // x가 음수인 경우에는 palindrome number가 될 수 없다
        if (x < 0) return false;

        vector<int> place_values;
        while (x > 0) {
          place_values.emplace_back(x % 10);
          x /= 10;
        }

        int size = place_values.size();
        for (int i = 0; i < size / 2; ++i) {
          if (place_values[i] - place_values[size - (i + 1)]) {
            return false;
          }
        }
        return true;
    }
};
```

## Other
### Approach 1 : Reversing the Entire Number
```cpp
class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0) return false;

    long long reversed = 0;
    long long origin = x;

    while (origin != 0) {
      int digit = origin % 10;
      reversed = reversed * 10 + digit;
      origin /= 10;
    }

    return (reversed == x);
  }
};
```
input number를 뒤집어서 original number와 같은지 비교하는 방법으로 풀 수 있다   

loop 내부에서 origin 값을 뒤집는 방법은 현재 reversed에 10을 곱하고, origin의 마지막 숫자를 더하는 것이다. 즉, `loop는 original number를 뒤집기 위한 로직을 위해 사용`한다.   
이는 직접 계산해보면 이해하기 쉽다. `reversed에 저장된 현재 값의 자릿수를 증가시키고, origin에서 추출한 마지막 자릿수를 더한다`.   

### Approach 2 : Reversing Half of the Number
```cpp
class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0 || (x != 0 && x % 10 == 0)) return false;

    int reversed = 0;
    while (x > reversed) {
      reversed = reversed * 10 + x % 10;
      x /= 10;
    }
    
    return (x == reversed) || (x == reversed / 10);
  }
};
```
input number가 0보다 작으면 palindrome number가 아니며, 0이 아니고 마지막 숫자가 0이면 palindrome number가 아니다.   

loop는 x의 첫 번째 구간의 절반값이 마지막 구간의 절반값( reversed )보다 작거나 같을 때까지 동작한다.   
즉, `x의 자릿수가 reversed의 자릿수 보다 작거나 동일하면 loop가 종료`된다.   

input number가 짝수인 경우, x는 reversed와 같으면 palindrome number이다.   
input number가 홀수인 경우, x는 reversed / 10과 같아야 한다. original number의 가운데 숫자는 무시하기 때문이다.   