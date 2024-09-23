- [Token](#token)
  - [Example](#example)
    - [1. Programming Language](#1-programming-language)
    - [2. 자연어 처리](#2-자연어-처리)
- [Parsing](#parsing)
  - [Example](#example-1)
    - [1. Programming Language](#1-programming-language-1)
    - [2. 자연어 처리](#2-자연어-처리-1)

<br>

`Token`: input data를 분석 가능한 작은 단위로 분리   
`Parsing`: 분리된 token을 문법 규칙에 따라 구조화하고 해석하는 과정   
[programmers - 다항식 더하기](/1_Algorithm/Programmers/240923_다항식더하기.md)   

<br>

# Token
text 또는 source code를 분석할 때, `가장 작은 단위의 의미 있는 element`를 말한다   

compiler나 interpreter가 source code를 분석하고 실행하기 위해 token으로 분리한다   
검색 엔진이나 언어 모델이 text를 분석하고 처리하기 위해 단어 단위로 분리한다   

## Example
### 1. Programming Language
```cpp
int main() { return 0; }
```
```
// token
int, return: keyword
main: identifier
(), {}, ; : delimiter
0: literal
```

### 2. 자연어 처리
```
"안녕하세요. 만나서 반갑습니다."
```
```
// token
"안녕하세요"
"."
"만나서"
"반갑습니다"
"."
```

<br><br>

# Parsing
`input data를 구조화된 형식으로 해석하고 분석하는 과정`   
주로 문법에 따라 데이터를 분해하여 의미 있는 구조로 변환하는 과정이다   

compiler는 source code의 구문을 분석해서 중간 코드나 기계어로 변환하며, 데이터 처리를 위해 JSON, XMAL 같은 데이터 형식을 해석하여 프로그램에서 사용할 수 있는 구조로 변환   
자연어 처리에선 문장의 문법 구조를 분석하여 의미를 이해한다   

## Example
### 1. Programming Language
```cpp
int a = 5 + 3;
```
```
// parsing result
변수 선언: int a
할당 연산: =
표현식: 5 + 3
```

### 2. 자연어 처리
```
나는 사과를 먹었다
```
```
// parsing result
주어: "나"
목적어: "사과"
동사: "먹었다"
```