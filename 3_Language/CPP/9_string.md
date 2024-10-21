- [std::string의 내부를 살펴보자](#stdstring의-내부를-살펴보자)
  - [1. std::string concatenate](#1-stdstring-concatenate)

<br><br>

# std::string의 내부를 살펴보자

## 1. std::string concatenate
`std::string은 문자열을 추가할 때마다 메모리를 재할당하고 복사`한다   
따라서 반복적인 문자열 추가는 메모리 재할당과 복사의 overhead를 증가시킬 수 있다   
이에 cpp compiler와 std library는 문자열 추가 시 메모리 재할당을 최소화하도록 최적화했다   

그럼에도 추가 연산 횟수가 적은 것이 성능면에서 유리하기 때문에 reserve를 이용하여 메모리 재할당을 방지하는 것이 좋다   