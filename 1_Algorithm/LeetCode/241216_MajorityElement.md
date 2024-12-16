[leetcode](https://leetcode.com/problems/majority-element/description/?envType=study-plan-v2&envId=top-interview-150)   

n개의 원소를 가진 `nums` 배열이 주어진다.   
`nums`의 원소들 중 가장 많은 빈도수를 가진 원소( majority element )를 반환해라.   
이때, majority element는 `n / 2`번 이상 나타나고, 이를 만족하는 원소는 항상 존재한다.   

시간 복잡도: O(N)   
공간 복잡도: O(1)   

# 풀이
`n / 2`번 이상 나타난다는 성질을 이용하면 `nums`를 sorting 한 후, 가운데 원소를 반환하면 된다.   
공간 복잡도에 대한 제약 사항이 없으면, hash map을 이용해서 각 원소의 빈도수를 측정하면 된다.   

[Moore Voting Algorithm](/1_Algorithm/AlgorithmConcepts/MooreVotingAlgorithm.md)   