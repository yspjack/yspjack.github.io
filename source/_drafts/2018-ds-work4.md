---
title: 2018-ds-work4
mathjax: true
tags:
---

## 猴子选大王

### 问题描述

要从n只猴子中选出一位大王。它们决定使用下面的方法：
n只猴子围成一圈，从1到n顺序编号。从第q只猴子开始，从1到m报数，凡报到m的猴子退出竞选，下一次又从退出的那只猴子的下一只开始从1到m报数，直至剩下的最后一只为大王。请问最后哪只猴子被选为大王。

### 输入形式

控制台输入三个整数n，m，q。

### 输出形式

输出最后选为大王的猴子编号。

### 样例输入

```
7  4  3
```

### 样例输出

```
4
```

### 评分标准

本题要求输出最后被选为大王的猴子编号，完全正确得20分，每个测试点4分。上传C语言文件名为`monkey.c`。

## 多项式相乘

### 问题描述

编写一个程序实现两个一元多项式相乘。

### 输入形式

首先输入第一个多项式中系数不为0的项的系数和指数，以一个空格分隔。且该多项式中各项的系数均为0或正整数，系数和最高幂次不会超过int类型的表示范围。对于多项式 $a_n x_n +a_{n-1} x_{n-1} + \dots + a_1 x_1 + a_0 x_0$ 的输入方法如下：
$$ a_n \; n \; a_{n-1} \; n-1 \; \dots \; a_1 \; 1 \; a_0 \; 0$$
即相邻两个整数分别表示表达式中一项的系数和指数。在输入中只出现系数不为0的项。最后一项的指数后没有空格，只有一个回车换行符。
按照上述方式再输入第二个多项式。

### 输出形式

将运算结果输出到屏幕。将系数不为0的项按指数从高到低的顺序输出，每次输出其系数和指数，均以一个空格分隔，最后一项的指数后也可以有一个空格。

### 样例输入

```
10 80000 2 6000 7 300 5 10 18 0
3 6000 5 20 8 10 6 0
```

### 样例输出

```
30 86000 50 80020 80 80010 60 80000 6 12000 21 6300 10 6020 31 6010 66 6000 35 320 56 310 42 300 25 30 130 20 174 10 108 0
```

### 样例说明

输入的两行分别代表如下表达式：
$ 10x^{80000} + 2x^{6000} + 7x^{300} + 5x^{10} + 18 $
$ 3x^{6000} + 5x^{20} + 8x^{10} + 6 $
相乘结果为：
$ 30x^{86000} + 50x^{80020} + 80x^{80010} + 60x^{80000} + 6x^{12000} + 21x^{6300}$
$ + 10x^{6020} + 31x^{6010} + 66x^{6000} + 35x^{320} + 56x^{310} + 42x^{300} $
$ + 25x^{30} + 130x^{20} + 174x^{10} + 108$

提示：利用链表存储多项式的系数和指数。

### 评分标准

该题要求输出相乘后多项式中系数不为0的系数和指数，共有5个测试点。上传C语言文件名为`multi.c`。

## 文件加密（环）

### 问题描述

有一种文本文件加密方法，其方法如下：

1、密钥由所有**ASCII码可见字符（ASCII码编码值32-126为可见字符）**组成，密钥长度不超过32个字符；

2、先将密钥中的重复字符去掉，即：**只保留最先出现的字符**，其后出现的相同字符都去掉；

3、将不含重复字符的密钥和其它不在密钥中的可见字符（按字符升序）连成一个由可见字符组成的环，密钥在前，密钥的头字符为环的起始位置；

4、设原密钥的第一个字符（即环的起始位置）作为环的开始位置标识，先从环中删除第一个字符（位置标识则移至下一个字符），再沿着环从下一个字符开始顺时针以第一个字符的ASCII码值移动该位置标识至某个字符，则该字符成为第一个字符的密文字符；然后从环中删除该字符，再从下一个字符开始顺时针以该字符的ASCII码值移动位置标识至某个字符，找到该字符的密文字符；依次按照同样方法找到其它字符的密文字符。**当环中只剩一个字符时，则该剩下的最后一个字符的密文为原密钥的第一个字符。**

下面以可见字符集只由小写字母组成为例来说明对应密文字符集生成过程。如果密钥为：helloworld，将密钥中重复字符去掉后为：`helowrd`，将不在密钥中的小写字母按照升序添加在密钥后，即形成字符串：`helowrdabcfgijkmnpqstuvxyz`，该字符串形成的环如下图所示：

{% asset_img huan.jpg %}

明码的第一个字母为h，h也是环的起始位置。h的ASCII码制为104，先把h从环中删除，再从下一个字母e开始顺时针沿着环按其ASCII值移动位置标识（即移动位置标识104次）至字母w，则h的密文字符为w。w的ASCII码制为119，然后将w从环中删除，再从下一个字母r开始顺时针沿着环移动位置标识119次至字母为l，则w的密文字符为l。依次按照同样方法找到其它字母的密文字符。环中剩下的最后一个字母为x，则x的密文字符为明码的第一个字母h。按照这种方法形成的密文转换字符表为：

{% asset_img biao.jpg %}

上方为原文字符，下方为对应的密文字符。由所有ASCII可见字符集组成的字符集密文字符生成方式与上例相同。

编写程序实现上述文件加密方法。密钥从**标准输入**读取，待加密文件为当前目录下的`in.txt`文件，该文件中的字符若是可见字符，则按照上述方法进行加密，否则原样输出（例如：回车换行符），加密后生成的密文文件为当前目录下的`in_crpyt.txt`。

### 输入形式

密钥是从标准输入读取的一行字符串，可以包含任意ASCII码可见字符（ASCII码编码值32-126为可见字符），长度不超过32个字符。

### 输出形式

加密后生成的密文文件为当前目录下的`in_crpyt.txt`。

### 样例输入

```
C Programming(Second Edition)
```

假设in.txt文件内容为：

```
This book is meant to help the reader learn how to program in C. It is the definitive reference guide, now in a second edition. Although the first edition was written in 1978, it continues to be a worldwide best-seller. This second edition brings the classic original up to date to include the ANSI standard.

From the Preface:
```

### 样例输出

in_crpyt.txt文件内容为：

```
KgklW#33>WklWA\^M8W83Wg\Z,W8g\WP\^u\PWZ\^PMWg3jW83W,P30P^AWkMWX5W.8WklW8g\Wu\EkMk8kt\WP\E\P\MR\W0-ku\+WM3jWkMW^Wl\R3MuW\uk8k3M5WIZ8g3-0gW8g\WEkPl8W\uk8k3MWj^lWjPk88\MWkMW'71G+Wk8WR3M8kM-\lW83W#\W^Wj3PZujku\W#\l8Jl\ZZ\P5WKgklWl\R3MuW\uk8k3MW#PkM0lW8g\WRZ^llkRW3Pk0kM^ZW-,W83Wu^8\W83WkMRZ-u\W8g\WIOY.Wl8^Mu^Pu5

4P3AW8g\WdP\E^R\(
```

### 样例说明

输入的密钥为C Programming(Second Edition)，由该密钥生成的字符串环中字符依次为：

```
C Progamin(SecdEt)!"#$%&'*+,-./0123456789:;<=>?@ABDFGHIJKLMNOQRTUVWXYZ[\]^_`bfhjklpqsuvwxyz{|}~
```

形成的字符转换字符表（第一行为原ASCII字符，第二行为对应的密文字符）为：

{% asset_img image.png %}

```
 !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
Wzx]veT{HL%*+J5Cs'~}q/o1G7(9;<FpSI&X2n4 6.h:U[OVdBwYK`f?Q_a|rc@"i^#Ru\E0gk=>ZAM3,yPl8-tj!m)$bDN
```

按照该密文转换字符表将in.txt中的内容转换成加密字符输出到`in_crpyt.txt`中。

### 评分标准

该题要求对指定的文件进行加密，提交的文件名为：`encode.c`。

## 词频统计（数组或链表实现）

### 问题描述

编写程序统计一个英文文本文件中每个单词的出现次数（词频统计），并将统计结果按单词字典序输出到屏幕上。

注：在此单词为仅由字母组成的字符序列。包含大写字母的单词应将大写字母转换为小写字母后统计。

### 输入形式

打开当前目录下文件`article.txt`，从中读取英文单词进行词频统计。

### 输出形式

程序将单词统计结果按单词字典序输出到屏幕上，每行输出一个单词及其出现次数，单词和其出现次数间由一个空格分隔，出现次数后无空格，直接为回车。

### 样例输入

当前目录下文件`article.txt`内容如下：

```
"Do not take to heart every thing you hear."
"Do not spend all that you have."
"Do not sleep as long as you want;"
```

### 样例输出

```
all 1
as 2
do 3
every 1
have 1
hear 1
heart 1
long 1
not 3
sleep 1
spend 1
take 1
that 1
thing 1
to 1
want 1
you 3
```

### 样例说明

按单词字典序依次输出单词及其出现次数。

### 评分标准

通过所有测试点将得满分。

### Solution

此题数据量少，使用链表实现即可。
注意单词的输入。

```C
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
    char val[20];
    int freq;
    struct Node *next;
};
typedef struct Node Node;
Node *head=NULL;
void ins(char *word)
{
    Node *u=head;
    while(u)
    {
        if(strcmp(u->val,word)==0)
        {
            u->freq++;
            return;
        }
        u=u->next;
    }

    Node *tmp=(Node*)malloc(sizeof(Node));
    strcpy(tmp->val,word);
    tmp->freq=1;
    tmp->next=NULL;

    if(head==NULL)
    {
        head=tmp;
        return;
    }
    if(strcmp(head->val,tmp->val)>0)
    {
        tmp->next=head;
        head=tmp;
        return;
    }
    Node *p,*q;
    p=head;
    q=head->next;
    while(q)
    {
        if(strcmp(q->val,tmp->val)>0)
        {
            break;
        }
        p=q;
        q=q->next;
    }
    tmp->next=q;
    p->next=tmp;

}

void dumplist()
{
    Node *u=head;
    while(u)
    {
        printf("%s %d\n",u->val,u->freq);
        u=u->next;
    }
}

char buf[512];
int getword()
{
    int ch=getchar();
    while(!isalpha(ch))
    {
        if(ch==EOF)
            return 0;
        ch=getchar();
    }
    int p=0;
    while(isalpha(ch))
    {
        buf[p++]=tolower(ch);
        ch=getchar();
    }
    buf[p]=0;
    return 1;
}
int main()
{
    freopen("article.txt","r",stdin);
    while(getword())
    {
        ins(buf);
    }
    dumplist();
    return 0;
}

```