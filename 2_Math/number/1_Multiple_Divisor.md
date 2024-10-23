# 1. Multiple
어떤 수 a가 다른 수 b의 배수라는 것은 $a = b * k( k는 정수 )$로 나타낼 수 있다.<br>

### 0은 모든 정수의 배수이다
수학적으로 0은 어떤 정수 n에 대해 $0 * n = 0$이기 때문이다. <br>

<br><br>

# 2. Divisor - 약수

## 2.1. Sum of Divisors
1부터 n까지의 자연수 중에서 n의 약수의 합을 구한다   
```cpp
long long solution(int n) {
    long long sum = 0;

    for(int i = 1; i * i <= n; ++i){
        if(n % i == 0){
            sum += i;
            if(i != n / i){
                sum += n / i;
            }
        }
    }
    return sum;
}
```
1부터 n까지의 자연수 모두를 탐색하는 것이 아니라 절반만 탐색하여 효율을 높인다   

`어떤 수 n의 약수 i가 있을 때, n / i도 약수라는 성질`을 이용한다   
예를 들면, n = 36일 때 i = 2이면 36 / 2 = 18도 약수다   

참고로 i * i == n인 경우, i와 n / i가 같기 때문에 한 번만 더한다   