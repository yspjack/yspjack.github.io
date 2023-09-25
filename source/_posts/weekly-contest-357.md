---
title: LeetCode 第 357 场周赛
date: 2023-08-06 22:58:05
tags:
- LeetCode
---

# LeetCode 第 357 场周赛

已 AC 的题目列表：

- 故障键盘
- 判断是否能拆分数组
- 找出最安全路径

<!--more-->

## 故障键盘

题目链接：
https://leetcode.cn/problems/faulty-keyboard/

按照题意直接模拟：如果字符不为 `i` 则加入到输出字符串，否则将输出字符串反转。

时间复杂度为 $O(n^2)$，$n$ 为字符串长度

## 判断是否能拆分数组

题目链接：
https://leetcode.cn/problems/check-if-it-is-possible-to-split-array/

首先求出前缀和，方便后续计算区间和

区间DP，定义状态 $d(i,j)$ 为区间 $[i,j]$ 可划分得到满足要求的数组的数量，最后判断是否满足 $d(0,n-1) \ge n$

状态转移：

在 $[i,j]$ 中枚举 $k$

$k=i$ 时，如果 $\sum_{l=i+1}^{j} nums[l] \ge m$

$$
d(i,j) \leftarrow \max \{d(i,j),d(i+1,j)+1\}
$$

$k=j-1$ 时，如果 $\sum_{l=i}^{j-1} nums[l] \ge m$

$$
d(i,j) \leftarrow \max \{d(i,j), d(i,j-1)+1 \}
$$

否则 $i<k<j-1$，判断是否满足 $\sum_{l=i}^{k} nums[l] \ge m$ 或 $\sum_{l=k+1}^{j} nums[l] \ge m$，如果满足则进行转移：

$$
d(i,j) \leftarrow  \max \{d(i,j), d(i,k)+d(k+1,j)\}
$$

需要注意边界情况：

- 子数组的长度为 1，返回 1
- 子数组的长度为 2，返回 2

时间复杂度为 $O(n^3)$

## 找出最安全路径

题目链接：
https://leetcode.cn/problems/find-the-safest-path-in-a-grid/

先广度优先搜索，以 `grid[r][c] = 1` 的网格为起点向上下左右4个方向扩展，预处理所有网格的安全系数：

|   |   |   |   |
|---|---|---|---|
| 3 | 2 | 1 | 0 |
| 2 | 3 | 2 | 1 |
| 1 | 2 | 3 | 2 |
| 0 | 1 | 2 | 3 |

题目要求**最小**曼哈顿距离的**最大**值，显然可以使用二分答案的方法。
对安全系数进行二分，判断是否能找到一条从起点到终点的路径，其经过路径的安全系数都大于等于当前安全系数 `mid`。
使用广度优先搜索寻找路径，以 (0,0) 为起点向上下左右4个方向扩展，扩展时判断网格安全系数都大于等于 `mid`，判断是否到达终点

时间复杂度为 $O(n^2 \log n)$
