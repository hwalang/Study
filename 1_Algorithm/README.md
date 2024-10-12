- [Index](#index)
- [Programmers](#programmers)
    - [Level 0](#level-0)
    - [Level 1](#level-1)

<br>

# Index
`KMP 알고리즘( Knuth-Morris-Pratt)` : find 함수 대신 KMP 알고리즘을 사용하여 더 효율적으로 부분 문자열을 찾을 수 있다   

1. **Problem Solving** : 다시 풀어 볼 만한 문제를 언제든지 풀 수 있도록 기록한다.
2. [place value ( digit )](1_place_value(digit).md) : 숫자의 자릿수를 다루는 방법을 알아본다.
3. [string 활용법](2_string.md)
   - 정수의 앞자리 0을 제거하는 방법
   - 문자 반복 출력
   - string `token 및 parsing`
   - string(cnt, char) 생성자를 이용한 `char to string`
   - `문자열 비교`
     - sort
     - shift
     - find
4. [Big Integer Arithmetic](3_Big_Integer_Arithmetic.md) : 컴퓨터에서 숫자로 표현할 수 없는 정수를 처리하는 방법
5. [bit 연산 모음집](4_bitwise_operation.md)
   - 짝/홀 판단( & ), `bit mask( check, set, remove )`
   - 정수 2배( Left-Shift )
   - 2나누기( Right-Shift )
6. [여러 가지 mapping 방법](5_mapping.md)
   - `enum - unordered_map`
7. [어려운 matrix 연산법](6_matrix_operation.md)
   - `Lower/Upper Triangular Matrix`, `string(count, ch)`
8. [ frequency 기록 방법 ](7_frequency.md) : array, unordered_map
9.  [Refactoring Code to Eliminate If-Else Statements](8_refactoring_if_else.md)
   - Adding Binary Strings using Bitwise Operations
10. [sweep line algorithm](9_Sweep_Line_Algorithm.md)
   - `겹치는 선분의 길이`


<br>

# Programmers
다시 풀어 볼 만한 문제를 모아둔다<br>
더 이상 안 풀어도 되는 경우 삭제한다<br>

### Level 0
| 날짜 | 문제 풀이 | 메모 | Try Count |
|:---:|:---:|:---:|:---:|
| `2024.10.03` | [`다음에 올 숫자`](Programmers/241003_다음에올숫자.md) | math  | 0 |
| `2024.10.03` | [`연속된 수의 합`](Programmers/241003_연속된수의합.md) | math  | 0 |
| `2024.10.03` | [`문자열 밀기`](Programmers/241003_문자열밀기.md) | string  | 0 |
| `2024.10.01` | [`A를 B로 만들기`](Programmers/241001_A로B만들기.md) | string  | 0 |
| `2024.10.01` | [`이진수 더하기`](Programmers/241001_이진수더하기.md) | string, bit mask  | 0 |
| `2024.09.29` | [`등수 매기기`](Programmers/240929_등수매기기.md) | simulation | 0 |
| `2024.09.28` | [`옹알이(1)`](Programmers/240928_옹알이1.md) | string, bit mask | 0 |
| `2024.09.28` | [`유한소수 판별하기`](Programmers/240928_유한소수판별하기.md) | Irreducible Fraction, Prime Factor, Prime Factorization, GCD | 0 |
| `2024.09.27` | [`겹치는 선분의 길이`](Programmers/240927_겹치는선분의길이.md) | sweep line algorithm | 0 |
| `2024.09.24` | [`외계어 사전`](Programmers/240924_외계어사전.md) | string, simulation | 0 |
| `2024.09.24` | [`삼각형의 완성조건(2)`](Programmers/240924_삼각형의완성조건2.md) | math | 0 |
| `2024.09.24` | [`안전 지대`](Programmers/240924_안전지대.md) | simulation | 0 |
| `2024.09.24` | [`숨어있는 숫자의 덧셈(2)`](Programmers/240924_숨어있는숫자의덧셈2.md) | token, parsing | 1 |
| `2024.09.23` | [`다항식 더하기`](Programmers/240923_다항식더하기.md) | simulation, token, parsing | 1 |
| `2024.09.22` | [`머쓱이보다 키 큰 사람`](Programmers/240922_머쓱이보다키큰사람.md) | distance | 1 |
| `2024.09.21` | [`n의 배수 고르기`](Programmers/240921_n의배수고르기.md) | remove_if, erase, accumulate | 1 |
| `2024.09.20` | [`배열의 유사도`](Programmers/240920_배열의유사도.md) | set | 1 |
| `2024.09.20` | [`문자열 계산하기`](Programmers/240920_문자열계산하기.md) | stringstream | 1 |
| `2024.09.20` | [`영어가 싫어요`](Programmers/240920_영어가싫어요.md) | string, regex | 1 |
| `2024.09.19` | [`가까운 수`](Programmers/240919_가까운수.md) | Simulation | 1 |
| `2024.09.17` | [`소인수 분해`](Programmers/240917_소인수분해.md) | set, prime factorization | 1 |
| `2024.09.17` | [`모음 제거`](Programmers/240917_모음제거.md) | unordered_set | 1 |
| `2024.09.15` | [`합성수 찾기`](Programmers/240915_합성수찾기.md) | Composite Number | 1 |
| `2024.09.13` | [`구슬을 나누는 경우의 수`](Programmers/240913_구슬을나누는경우의수.md) | Combination, DP, Recursion, memoization | 1 |
| `2024.09.12` | [`순서쌍의 개수`](Programmers/240912_순서쌍의개수.md) | 수학 | 1 |
| `2024.09.12` | [`진료순서 정하기`](Programmers/240912_진료순서정하기.md) | 문제 해석 능력 | 1 |
| `2024.09.06` | [`정수를 나선형으로 배치하기`](Programmers/240906_정수를나선형으로배치.md) | matrix, implementation | 1 |
| `2024.08.23` | [`문자열 잘라서 정렬하기`](Programmers/240901_문자열잘라서정렬.md) | stringstream | 1 |
| `2024.08.23` | [`배열 조각하기`](Programmers/240823_배열조각하기.md) | implementation | 1 |
| `2024.08.22` | [`2의 영역`](Programmers/240822_2의영역.md) | vector<T>() constructor | 1 |
| `2024.08.15` | [`문자 개수 세기`](Programmers/240815_문자개수세기.md) | ASCII code와 영문자를 이용한 count 배열 | 1 |
| `2024.08.15` | [`QR code`](Programmers/240815_QRcode.md) | Modulo 연산 | 1 |
| `2024.08.14` | [`세로 읽기`](Programmers/240814_세로읽기.md) | Simulation | 1 |
| `2024.08.09` | [`주사위 게임3`](Programmers/240809_주사위게임3.md) | 2D-matrix, Thinking | 1 |
| `2024.07.28` | [`배열 만들기2`](Programmers/240728_배열만들기2.md) | brute-force, bit-mask | 1 |

### Level 1
| 날짜 | 문제 풀이 | 메모 | Try Count |
|:---:|:---:|:---:|:---:|
|  |  |   |  |