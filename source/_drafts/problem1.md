---
title: problem1
date: 2017-10-29 21:24:50
tags:
mathjax: true
---

## A 音量调节 (changingsounds)
### 问题描述
一个吉他手准备参加一场演出。他不喜欢在演出时始终使用同一个音量，所以他决定每一首歌之前他都要改变一次音量。在演出开始之前，他已经做好了一个列表，里面写着在每首歌开始之前他想要改变的音量是多少。每一次改变音量，他可以选择调高也可以调低。
音量用一个整数描述。输入文件中给定整数beginLevel，代表吉他刚开始的音量，以及整数maxLevel，代表吉他的最大音量。音量不能小于0也不能大于maxLevel。输入文件中还给定了n个整数$c_{1},c_{2},...,c_{n}$，表示在第i首歌开始之前吉他手想要改变的音量是多少。
吉他手想以最大的音量演奏最后一首歌，你的任务是找到这个最大音量是多少。

<!--more-->

### 输入
第一行依次为三个整数：n, beginLevel, maxlevel。
第二行依次为n个整数：$c_{1},c_{2},...,c_{n}$。
### 输出
输出演奏最后一首歌的最大音量。如果吉他手无法避免音量低于0或者高于maxLevel，输出-1。
### 输入样例
```
3 5 10
5 3 7
```
### 输出样例
```
10
```
### 输入样例
```
4 8 20
15 2 9 10
```
### 输出样例
```
-1
```
对于30%的数据$1\le n\le 10$
对于100%的数据$1\le n\le 50 , 1\le C[i]\le maxlevel , 1\le maxlevel \le  1000,\\
0\le  beginlevel \le maxlevel$

### 题解
这题其实正解就是一个类似于背包的DP，每次只有两种可能，上调or下调，所以我们可以设计状态:
             f[i][j]表示前i次调节能否得到j音量
显然，f[i][j]=false表示不能，f[i][j]=true表示可以。
转移：
$$f[i][j]=f[i-1][j-c[i]]∨f[i-1][j+c[i]]
(j\ge c[i],j+c[i]\le maxlevel)$$
边界:$f[0][beginlevel]=1$
顺便一提，由于这里转移是f[i][j]只和f[i-1]这一层的状态有关，我们可以用滚动数组优化空间到一维
时间复杂度$T(n)=O(n * maxlevel)$

```cpp
    int maxFinal(vector <int> changeIntervals, int beginLevel, int maxLevel)
    {
        int len=changeIntervals.size();
        bool opt[1001],dp[1001];
        int i,j;
        for (i=0; i<=maxLevel; i++)
            opt[i]=dp[i]=false;
        dp[beginLevel]=true;
        for (j=0; j<len; j++)
        {
            for (i=0; i<=maxLevel; i++)
                if (dp[i])
                {
                    if (i+changeIntervals[j]<=maxLevel)
                        opt[i+changeIntervals[j]]=true;
                    if (i-changeIntervals[j]>=0)
                        opt[i-changeIntervals[j]]=true;
                }
            for (i=0; i<=maxLevel; i++)
            {
                dp[i]=opt[i];
                opt[i]=false;
            }
        }
        for (j=maxLevel; j>=0; j--)
            if (dp[j])
                return j;
        return -1;
    }
```

