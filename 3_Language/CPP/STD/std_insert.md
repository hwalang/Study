- [std::vector::insert](#stdvectorinsert)
- [Exception](#exception)
- [return value](#return-value)
- [Example](#example)
    - [Programmers](#programmers)

<br>

# std::vector::insert
```cpp
// 1.
iterator insert(const_iterator pos, const T& value);

// 2.
iterator insert(const_iterator pos, T&& value);

// 3.
iterator insert(const_iterator pos, size_type count, const T& value);

// 4.
template <class InputIt>
iterator insert(const_iterator pos, InputIt first, InputIt last);

// 5.
iterator insert(const_iterator pos, std::initializer_list<T> ilist);
```
container의 `특정 위치에 elements를 넣는다`<br>

1. `pos 앞`에 value를 넣는다.
2. ㅇ
3. pos 앞에 value를 count 만큼 추가한다.
4. pos 앞에 [first, last) 범위의 elements를 넣는다
   - `*this( 자기 자신 )의 iterator를 추가할 수 없다`.
5. pos 앞에 초기화된 list를 넣는다.

<br>
<br>

# Exception
```cpp
// re-allocation
vector<int> vec{ 1, 2, 3 };
auto it = vec.begin() + 1;
vec.insert(vec.end(), 4);
cout << *it << endl;          // invalid action : runtime error

// non re-allocation
vector<int> vec{ 1, 2, 3 };
vec.resize(10);
auto it = vec.begin() + 1;
vec.insert(vec.end(), 4);
cout << *it << endl;          // valid
```
`insert 연산 이후` 새로운 size()가 이전 capacity()보다 크다면 재할당이 발생하면서 모든 iterator와 element에 대한 참조가 무효화 된다<br>
재할당이 발생하지 않으면 insert 이전의 iterator와 element에 대한 참조만 유효하다<br>

```cpp
// visual studio 2022
int main()
{
    vector<int> vec{ 1, 2, 3 };
    auto it = vec.begin() + 1;

    cout << vec.capacity() << endl;
    it = vec.insert(it, 2, 4);
    for (; it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n" << vec.capacity() << endl;
}
```
최근 실험해본 결과 `reallocation이 발생해도 iterator가 유효`했다<br>
이는 compiler 최적화나 Debug 모드의 최적화, 시스템에서 메모리 할당을 기존 메모리 위치와 같은 경우 등 다양한 원인이 있으 수 있다<br>


<br>
<br>

# return value
1. `삽입된 value를 가리키는 iterator`
2. 삽입된 value를 가리키는 iterator
3. 삽입된 `첫 번째 element를 가리키는 iterator`
   - `count가 0`이라면 pos iterator
4. 삽입된 첫 번째 element를 가리키는 iterator
   - `first == last`라면 pos iterator
5. 삽입된 첫 번째 element를 가리키는 iterator
   - `ilist가 empty`라면 pos iterator

<br>
<br>

# Example
```cpp
int main()
{
  vector<int> vec(3, 1);
  auto pos = vec.begin();

  // 1.
  pos = vec.insert(pos, 2);   // 2, 1, 1, 1

  // 3.
  vec.insert(pos, 2, 3);      // 3, 3, 2, 1, 1, 1
  // reallocation 발생 - pos 무효
  pos = vec.begin();

  // 4. *this 불가능
  vector<int> vec2(2, 5);
  vec.insert(std::next(pos, 2), vec2.begin(), vec2.end());

  // 5.
  vec.insert(vec.end(), { 6, 6, 6 });
}
```

### Programmers
[ 빈 배열에 추가, 삭제하기 ](https://school.programmers.co.kr/learn/courses/30/lessons/181860)<br>
```cpp
vector<int> solution(vector<int> arr, vector<bool> flag)
{
  vector<int> vec;

  for (int i = 0; i < flag.size(); ++i)
    flag[i] ? vec.insert(vec.end(), arr[i] * 2, arr[i]) : vec.erase(vec.end() - arr[i], vec.end());
  
  return vec;
}
```
