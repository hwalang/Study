[leetcode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/?envType=study-plan-v2&envId=top-interview-150)   

`prices` 배열에서 `prices[i]`는 i번째 날짜에 주어진 물건의 가격을 뜻한다.   
하나의 물건을 사는 날짜를 하나 선택하고, 선택한 물건을 파는 날짜를 선택하여 가장 큰 이익을 얻을 수 있길 원한다.   
이러한 거래로 얻은 최대 이익을 반환하거나, 이익을 얻을 수 없으면 0을 반환한다.   

# ME
어떻게 틀렸는지 기록한다.   
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 1) return 0;

        int sell_day = -1;
        for (int i = prices.size() - 1; i >= 1; --i) {
          if (prices[i] > prices[i - 1]) {
            sell_day = i;
            break;
          }
        }

        if (sell_day == -1) {
          return 0;
        }

        int profit = 0;
        for (int i = 0; i < sell_day; ++i) {
          profit = max(profit, prices[sell_day] - prices[i]);
        }

        cout << sell_day << endl;

        return profit;
    }
};
```
## Approch
마지막 원소에서 첫 번째 원소로 순회하면서 더 이상 값이 줄어들지 않으면, 그 위치가 사는 날짜다.
  - 만약 사는 날짜를 고르지 못하면, 어떠한 수단으로도 미래에 더 큰 이득을 얻지 못하기 때문에 0을 반환한다.

첫 번째 원소에서 사는 날짜를 비교하여 가장 많은 이득을 보는 날짜를 반환한다.   

---
```
prices: [3,2,6,5,0,3]

output: 3
expected: 4
```
여기서 `sell_day`를 구하는 과정에 문제가 발생했다.   
만약 `sell_day`로 정한 날짜 앞에 더 높은 가치를 가진 원소가 존재하면, 해당 알고리즘으로 올바른 답을 도출할 수 없다.   

# Other
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int buy = prices[0];
        for (int i = 1; i < prices.size(); ++i) {
          if (buy < prices[i]) {
            profit = max(profit, prices[i] - buy);
          }
          else {
            buy = prices[i];
          }
        }

        return profit;
    }
};
```
## Approch
구매값을 `prices[0]`으로 세팅한다.   
`prices`를 순회하면서 구매값이 현재 값보다 작으면, 이익을 볼 수 있기 때문에 `profit`을 갱신한다.   
작지 않으면, 구매 값을 현재 값으로 갱신하여 더 많은 이익을 추구한다.   

----
구매 값을 갱신한다는 생각을 못했다..   