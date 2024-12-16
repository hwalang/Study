- [Index](#index)
- [Coding Test](#coding-test)
  - [Top Interview 150 - leetcode](#top-interview-150---leetcode)
- [Programmers](#programmers)
    - [Level 0](#level-0)
    - [Level 1](#level-1)
- [Leet Code](#leet-code)

<br>

# Index
`KMP 알고리즘( Knuth-Morris-Pratt)` : find 함수 대신 KMP 알고리즘을 사용하여 더 효율적으로 부분 문자열을 찾을 수 있다   

1. **[place value ( digit )](1_place_value(digit).md)** : 숫자의 자릿수를 다루는 방법을 알아본다.
2. **[string 활용법](2_string.md)**
   - 정수의 앞자리 0을 제거하는 방법
   - 문자 반복 출력
   - string `token 및 parsing`
   - string(cnt, char) 생성자를 이용한 `char to string`
   - `문자열 비교`
     - sort
     - shift
     - find
3. **[Big Integer Arithmetic](3_Big_Integer_Arithmetic.md)** : 컴퓨터에서 숫자로 표현할 수 없는 정수를 처리하는 방법
4. **[bit 연산 모음집](4_bitwise_operation.md)**
   - 짝/홀 판단( & ), `bit mask( check, set, remove )`
   - 정수 2배( Left-Shift )
   - 2나누기( Right-Shift )
5. **[여러 가지 mapping 방법](5_mapping.md)**
   - `enum - unordered_map`
6. **[어려운 matrix 연산법](6_matrix_operation.md)**
   - `Lower/Upper Triangular Matrix`, `string(count, ch)`
7. **[ frequency 기록 방법 ](7_frequency.md)** : array, unordered_map
8.  [Refactoring Code to Eliminate If-Else Statements](8_refactoring_if_else.md)
   - Adding Binary Strings using Bitwise Operations
9.  **[ Decimal To Binary ](10_Decimal_to_Binary.md)**
    - Brute Force Approach( Print, Return )


<br>

# Coding Test
코딩 테스트 통과에 필요한 실력을 갖추기 위한 공부   
## Top Interview 150 - leetcode
| 날짜 | 문제 풀이 | 메모 | Try Count |
|:---:|:---:|:---:|:---:|
| `2024.12.16` | [`Majority Element`](LeetCode/241216_MajorityElement.md) | hash-table, sort, Moore Voting Algorithm | 0 |
| `2024.12.15` | [`Remove Dulplicates from Sorted Array 2`](LeetCode/241215_RemoveDuplicatesFromSortedArray2.md) | two-pointer | 0 |
| `2024.12.12` | [`Merge Sorted Array`](LeetCode/241212_MergeSortedArray.md) | implementation | 0 |
| `2024.11.27` | [`Remove Element`](LeetCode/241126_RemoveElement.md) | two-pointer | 0 |
| `2024.11.09` | [`Remove Dulplicates from Sorted Array`](LeetCode/241109_RemoveDuplicatesFromSortedArray.md) | two-pointer, std::unique | 1 |

<br><br>

# Programmers
다시 풀어 볼 만한 문제를 모아둔다<br>
더 이상 안 풀어도 되는 경우 삭제한다<br>

### Level 0
| 날짜 | 문제 풀이 | 메모 | Try Count |
|:---:|:---:|:---:|:---:|
| `2024.10.03` | [`다음에 올 숫자`](Programmers_level_0/241003_다음에올숫자.md) | math  | 1 |
| `2024.10.03` | [`연속된 수의 합`](Programmers_level_0/241003_연속된수의합.md) | math  | 1 |
| `2024.10.03` | [`문자열 밀기`](Programmers_level_0/241003_문자열밀기.md) | string  | 1 |
| `2024.10.01` | [`A를 B로 만들기`](Programmers_level_0/241001_A로B만들기.md) | string  | 1 |
| `2024.10.01` | [`이진수 더하기`](Programmers_level_0/241001_이진수더하기.md) | string, bit mask  | 1 |
| `2024.09.29` | [`등수 매기기`](Programmers_level_0/240929_등수매기기.md) | simulation | 1 |
| `2024.09.28` | [`옹알이(1)`](Programmers_level_0/240928_옹알이1.md) | string, bit mask | 1 |
| `2024.09.28` | [`유한소수 판별하기`](Programmers_level_0/240928_유한소수판별하기.md) | Irreducible Fraction, Prime Factor, Prime Factorization, GCD | 1 |
| `2024.09.27` | [`겹치는 선분의 길이`](Programmers_level_0/240927_겹치는선분의길이.md) | sweep line algorithm | 1 |
| `2024.09.24` | [`외계어 사전`](Programmers_level_0/240924_외계어사전.md) | string, simulation, unordered_map | 1 |
| `2024.09.24` | [`삼각형의 완성조건(2)`](Programmers_level_0/240924_삼각형의완성조건2.md) | math | 1 |
| `2024.09.24` | [`안전 지대`](Programmers_level_0/240924_안전지대.md) | simulation | 1 |
| `2024.09.24` | [`숨어있는 숫자의 덧셈(2)`](Programmers_level_0/240924_숨어있는숫자의덧셈2.md) | token, parsing | 1 |
| `2024.09.23` | [`다항식 더하기`](Programmers_level_0/240923_다항식더하기.md) | simulation, token, parsing | 1 |
| `2024.09.22` | [`머쓱이보다 키 큰 사람`](Programmers_level_0/240922_머쓱이보다키큰사람.md) | distance | 1 |
| `2024.09.21` | [`n의 배수 고르기`](Programmers_level_0/240921_n의배수고르기.md) | remove_if, erase, accumulate | 1 |
| `2024.09.20` | [`배열의 유사도`](Programmers_level_0/240920_배열의유사도.md) | set | 1 |
| `2024.09.20` | [`문자열 계산하기`](Programmers_level_0/240920_문자열계산하기.md) | stringstream | 1 |
| `2024.09.20` | [`영어가 싫어요`](Programmers_level_0/240920_영어가싫어요.md) | string, regex | 1 |
| `2024.09.19` | [`가까운 수`](Programmers_level_0/240919_가까운수.md) | Simulation | 1 |
| `2024.09.17` | [`소인수 분해`](Programmers_level_0/240917_소인수분해.md) | set, prime factorization | 1 |
| `2024.09.17` | [`모음 제거`](Programmers_level_0/240917_모음제거.md) | unordered_set | 1 |
| `2024.09.15` | [`합성수 찾기`](Programmers_level_0/240915_합성수찾기.md) | Composite Number | 1 |
| `2024.09.13` | [`구슬을 나누는 경우의 수`](Programmers_level_0/240913_구슬을나누는경우의수.md) | Combination, DP, Recursion, memoization | 1 |
| `2024.09.12` | [`순서쌍의 개수`](Programmers_level_0/240912_순서쌍의개수.md) | 수학 | 1 |
| `2024.09.12` | [`진료순서 정하기`](Programmers_level_0/240912_진료순서정하기.md) | 문제 해석 능력 | 1 |
| `2024.09.06` | [`정수를 나선형으로 배치하기`](Programmers_level_0/240906_정수를나선형으로배치.md) | matrix, implementation | 1 |
| `2024.08.23` | [`문자열 잘라서 정렬하기`](Programmers_level_0/240901_문자열잘라서정렬.md) | stringstream | 1 |
| `2024.08.23` | [`배열 조각하기`](Programmers_level_0/240823_배열조각하기.md) | implementation | 1 |
| `2024.08.22` | [`2의 영역`](Programmers_level_0/240822_2의영역.md) | vector<T>() constructor | 1 |
| `2024.08.15` | [`문자 개수 세기`](Programmers_level_0/240815_문자개수세기.md) | ASCII code와 영문자를 이용한 count 배열 | 1 |
| `2024.08.15` | [`QR code`](Programmers_level_0/240815_QRcode.md) | Modulo 연산 | 1 |
| `2024.08.14` | [`세로 읽기`](Programmers_level_0/240814_세로읽기.md) | Simulation | 1 |
| `2024.08.09` | [`주사위 게임3`](Programmers_level_0/240809_주사위게임3.md) | 2D-matrix, Thinking | 1 |
| `2024.07.28` | [`배열 만들기2`](Programmers_level_0/240728_배열만들기2.md) | brute-force, bit-mask | 1 |

### Level 1
| 날짜 | 문제 풀이 | 메모 | Try Count |
|:---:|:---:|:---:|:---:|
| `2024.11.09` | [최소 직사각형](Programmers_level_1/241109_최소직사각형.md) | brute-force | 0 |
| `2024.11.08` | [숫자 문자열과 영단어](Programmers_level_1/241108_숫자문자열과영단어.md) | regex | 0 |
| `2024.11.04` | [3진법 뒤집기](Programmers_level_1/241104_3진법뒤집기.md) | math | 0 |
| `2024.11.03` | [두 개 뽑아서 더하기](Programmers_level_1/241103_두개뽑아서더하기.md) | Combination | 0 |
| `2024.10.30` | [키패드 누르기](Programmers_level_1/241030_키패드누르기.md) | implementation | 0 |
| `2024.10.29` | [다트 게임](Programmers_level_1/241029_다트게임.md) | parsing | 0 |
| `2024.10.29` | [실패율](Programmers_level_1/241029_실패율.md) | | 0 |
| `2024.10.27` | [완주하지 못한 선수](Programmers_level_1/241027_완주하지못한선수.md) | | 0 |
| `2024.10.24` | [[1차] 비밀지도](Programmers_level_1/241024_[1차]비밀지도.md) | math | 0 |
| `2024.10.23` | [소수 만들기](Programmers_level_1/241023_소수만들기.md) | math | 0 |
| `2024.10.23` | [약수의 합](Programmers_level_1/241023_약수의합.md) | math | 0 |
| `2024.10.22` | [시저 암호](Programmers_level_1/241022_시저암호.md) | math | 0 |
| `2024.10.21` | [수박수...?](Programmers_level_1/241021_수박.md) | string 내부 동작 | 0 |
| `2024.10.14` | [문자열 내 p와 y의 개수](Programmers_level_1/241014_문자열내p와y의개수.md) |  | 1 |
| `2024.10.12` | [두 정수 사이의 합](Programmers_level_1/241012_두정수사이의합.md) | Arithmetic Sequence, type casting | 1 |


<br><br>

# Leet Code
| 날짜 | 문제 풀이 | 메모 | Try Count |
|:---:|:---:|:---:|:---:|
| `2024.12.06` | [`Search Insert Position`](LeetCode/241206_SearchInsertPosition.md) | binary search | 0 |
| `2024.11.28` | [`Find the Index of the First Occurrence in a String`](LeetCode/241127_FindTheIndexOfTheFirstOccurrenceInAString.md) | brute-force, KMP | 0 |
| `2024.11.08` | [`Merge Two Sorted Lists`](LeetCode/241108_MergeTwoSortedLists.md) | struct pointer | 0 |
| `2024.11.06` | [`longest common prefix`](LeetCode/241106_LongestCommonPrefix.md) | sort | 0 |
| `2024.11.04` | [`palindrome number`](LeetCode/241104_PalindromeNumber.md) | | 0 |
| `2024.10.30` | [`two sum`](LeetCode/241030_TwoSum.md) | complement, hash table  | 0 |