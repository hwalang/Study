---
layout:
  title:
    visible: true
  description:
    visible: false
  tableOfContents:
    visible: true
  outline:
    visible: true
  pagination:
    visible: true
---

# 2024.05.21. 원형 순열에서의 인원 제거

\[code tree]\([https://www.codetree.ai/missions/6/problems/josephus-permutations?\&utm\_source=clipboard\&utm\_medium=text](https://www.codetree.ai/missions/6/problems/josephus-permutations?\&utm\_source=clipboard\&utm\_medium=text))



## 1. My Solution

```cpp
#include <iostream>
#include <queue>
using namespace std;

queue<int> q;
int total, removed_num;

void Input()
{
	cin >> total >> removed_num;
	for (int i = 1; i <= total; ++i)
	{
		q.push(i);
	}
}

void PrintRemovedPerson()
{
	while (q.size() >= 1)
	{
		for (int i = 1; i < removed_num; ++i)
		{
			q.push(q.front());
			q.pop();
		}
		
		cout << q.front() << " ";
		q.pop();
	}
}

int main()
{
	Input();
	PrintRemovedPerson();
}
```

## 2. Review

PrintRemovePerson()에서 removed\_num번째 사람을 제거하기 위해서는 for의 i가 0부터 시작인지, 1부터 시작인지 헷갈렸다.

for문의 i가 0부터 시작하면 removed\_num + 1번째 사람을 제거했다.  removed\_num번째 사람까지 맨 마지막으로 이동하기 때문이다.



