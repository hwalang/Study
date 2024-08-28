- [std::transform](#stdtransform)

<br>

# std::transform
```cpp
#include <algorithm>

// 1
templace <class InputIt, class OutputIt, class UnaryOp>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op);

// 2
template <class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryOp>
ForwardIt2 transform(ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 d_first, UnaryOp unary_op);

// 3
template <class InputIt1, class InputIt2, class OutputIt, class BinaryOp>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOp binary_op);
```
`[first1, last1) 내의 범위에 주어진 elements에게 주어진 function을 적용`시킨다<br>
`d_first 첫 시작 주소를 가져와서 위 결과를 저장`한다<br>