[leetcode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/?envType=study-plan-v2&envId=top-interview-150)

`prices` 배열이 주어지고, `prices[i]`는 `i`번째 날의 주식 가격을 나타낸다.   
각 날짜에 대해 주식을 사거나 팔 수 있지만, 최대 하나의 주식만 보유할 수 있다. 또한 산 날짜에 바로 팔 수 있다.   
최대 이익을 반환하자.   

## Approch
가격이 상승하는 날마다 전날에 사서 당일에 판다고 생각하면, 모든 오름 구간에서 발생하는 이익의 누적합으로 문제를 풀 수 있다.   

## Algorithm
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
      int profit = 0;
      for (int i = 1; i < prices.size(); ++i) {
        int value = prices[i] - prices[i - 1];
        if (value > 0) {
          profit += value;
        }
      }

      return profit;
    }
};
```
여기서 코드 3줄을 한 줄로 리팩토링 할 수 있다.
```cpp
// for
profit += max(0, prices[i] - prices[i - 1]);
```