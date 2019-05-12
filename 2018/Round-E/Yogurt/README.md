# [Yogurt](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050ff5/00000000000510f1)

## 题目描述  

有N杯酸奶，第i杯酸奶会在第Ai天过期，每天最多能喝K杯酸奶。
问在所有酸奶过期前，最多能喝多少杯酸奶？

## 数据范围  

1 <= K <= N
1 <= Ai <= 10^9
1 <= N <= 5000

## 解题步骤

* 1.模拟  

## 分析
统计从第1天到第N天，每天分别会有多少酸奶过期。把过期时间大于N的酸奶都算到第N天头上。
然后倒着从第N天遍历到第1天，每天喝不超过K杯，没喝完的就留给前一天（第i天的酸奶如果喝不完，就把多余的酸奶争取放在第i-1天喝）。
遍历完了之后，能喝到的杯数就是最终的结果。

## 复杂度
时间：O(N)  
空间：O(N)