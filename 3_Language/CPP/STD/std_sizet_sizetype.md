- [std::container::size\_type](#stdcontainersize_type)
  - [size\_t와 동일한데 size\_type은 왜 있나요?](#size_t와-동일한데-size_type은-왜-있나요)
    - [이식성 보장](#이식성-보장)
    - [결론](#결론)
- [std::size\_t](#stdsize_t)
    - [사용하는 이유](#사용하는-이유)

<br>

# std::container::size_type
cppreference에서 size_type 반환 값이 존재한다. 이 TYPE은 일반적으로 std::size_t로 정의한다<br>
size_type은 std::string, std::vector와 같은 `container에 정의된 타입`이다.<br>
`모든 STL container는 자신의 크기나 인덱스를 나타내기 위해 size_t를 기반으로 한 size_type을 정의`했다<br>

<br>

## size_t와 동일한데 size_type은 왜 있나요?
### 이식성 보장
모든 커스텀 container의 내부 구현이 동일한 타입( std::size_t )을 사용한다는 가정이면 std::size_t를 사용해도 되지만, 그렇지 않으면 호환성 문제가 발생할 수 있다<br>
```cpp
// custom container
template <typename T>
class CustomContainer
{
  public:
    using size_type = int;    // std::size_t와 다르게 정의

    CustomContainer(size_type size) : _size(size), _data(new T[size]) {}
    ~CustomContainer() { delete[] _data; }

    size_type size() const { return _size; }
    T& operator[](size_type index) { return _data[index]; }

  private:
    size_type _size;
    T* _data;
};
```
위 custom container에서는 어떠한 이유로 `size_type을 int로 정의`했다<br>
```cpp
int main()
{
  CustomContainer<int> container(5);
  // int type도 가능
  for (CustomContainer<int>::size_type i = 0; i < container.size(); ++i) {
    container[i] = i * 10;
    std::cout << container[i] << std::endl;
  }
}
```
위 코드에서는 container에서 정의한 size_type으로 index에 연산을 처리한다<br>
여기서 `size_type은 int로 정의했기 때문에 size_type이 아닌 int로 index를 처리할 수 있다`<br>

하지만 `size_t로 index에 접근하면 std::size_t와 int 간의 type 불일치로 warning이 발생`한다<br>
또한 unsigned와 signed int 차이가 있기 때문에 `의도치 않은 동작을 유발`할 수 있다<br>

### 결론
이처럼 `container의 size_type을 사용하면 해당 container의 내부 구현에 맞춰 코드가 자동으로 적응`할 수 있다<br>
반대로 특정 타입( std::size_t )를 강제로 사용하면 특정 상황에서 호환성 문제가 발생할 수 있다<br>

<br>
<br>

# std::size_t
```cpp
typedef size_t;
using size_t = decltype(sizeof(0));
```
`unsigned int type`으로써 메모리 size나 배열의 index를 나타내기 위해 설계됐다<br>
`compiler와 platform에 따라 적절한 크기의 타입으로 정의`된다<br>
예를 들면, 32bit 시스템에서는 unsigned int( 32bit )이고, 64bit 시스템에서는 unsigned long 또는 unsigned long long( 64bit )로 정의된다<br>

std::size_t는 특정 type 객체의 이론적으로 가능한 가장 큰 사이즈를 저장할 수 있다<br>
따라서 size_t로 크기를 표현할 수 없는 type은 잘못된 type이다<br>

### 사용하는 이유
배열의 size나 index를 나타내기 위해 unsigned int를 사용했다 가정한다<br>
unsigned int는 일반적으로 32bit 크기이며, 이는 UINT_MAX까지 표현할 수 있다<br>

하지만 64bit 시스템에서는 memory 주소 공간이 UINT_MAX보다 크기 때문에 배열의 크기가 이를 초과할 수 있다<br>
이로 인해 `overflow가 발생하여 의도치 않은 동작이 발생`한다<br>

이처럼 `플랫폼에 따라 달라지는 환경에 대응하기 위해서 size_t를 사용`할 수 있다<br>
size_t는 환경에 따라 size가 유동적으로 변하기 때문에 배열의 size, index를 표현할 때 overflow가 발생할 위험이 없다<br>