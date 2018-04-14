---
title: 数据结构第2次作业
mathjax: true
tags:
---

## 求差集

### 问题描述

两个集合的差集定义如下：
集合A、B的差集，由所有属于A但不属于B的元素构成。
输入两个集合A、B，每个集合中元素都是自然数。求集合A、B的差集。

### 输入形式

从标准输入接收集合中的自然数元素，以空格分隔。-1表示输入结束。
其中，每个集合都不输入重复的元素。

### 输出形式

输出差运算后集合中的元素，以空格分隔。输出元素的顺序与原有集合A输入的顺序一致。
如果A、B的差集为空集，则不输出任何数值。

### 样例输入

```
2 8 3 4 -1
6 1 4 9 -1
```

### 样例输出

```
2 8 3
```

### 样例说明

从标准输入接收集合中的自然数元素，输出集合A、B的差集。

### 评分标准

该题要求输出差运算后集合中的元素，结果完全正确得20分，每个测试点4分。上传C语言文件名为`sets.c`。

<!--more-->

### AC代码

```C
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int A[1000003],B[1000003],vis[1000003];

int main()
{
    int x,p1=0,p2=0;
    while(scanf("%d",&x)==1)
    {
        if(x==-1)break;
        A[p1++]=x;
    }
    while(scanf("%d",&x)==1)
    {
        if(x==-1)break;
        B[p2++]=x;
        vis[x]=1;
    }
    int i;
    for(i=0;i<p1;i++)
    {
        if(!vis[A[i]])
        {
            printf("%d ",A[i]);
        }
    }
    return 0;
}

```

<!--more-->

## 表达式计算（支持空格，连乘，连除）

### 问题描述

从标准输入中读入一个整数算术运算表达式，如 ` 5 - 1 * 2 * 3 + 12 / 2 / 2  = `。计算表达式结果，并输出。

要求：
1、表达式运算符只有+、-、*、/，表达式末尾的’=’字符表示表达式输入结束，表达式中可能会出现空格；
2、表达式中不含圆括号，不会出现错误的表达式；
3、出现除号/时，以整数相除进行运算，结果仍为整数，例如：5/3结果应为1。

### 输入形式

在控制台中输入一个以’=’结尾的整数算术运算表达式。

### 输出形式

向控制台输出计算结果（为整数）。

### 样例1输入

```
5 - 1 * 2 * 3 + 12 / 2 / 2  =
```

### 样例1输出

```
2
```

### 样例2输入

```
500 =
```

### 样例2输出

```
500
```

### 样例1说明

```
输入的表达式为5 - 1 * 2 * 3 + 12 / 2 / 2 =，按照整数运算规则，计算结果为2，故输出2。
```

### 样例2说明

输入的表达式为500 = ，没有运算符参与运算，故直接输出500。

算法之一提示：
1、可以利用gets函数，读取整行表达式；
2、对于空格，可以考虑首先去除表达式中的所有空格
3、可以设一计数器用来记录已读取、但未参加运算的运算符的个数，根据该计数器来判断如何进行运算；
4、可以设计一函数：实现二元整数算术运算。

### 评分标准

该题要求输出整数表达式的计算结果，共有5个测试点。上传C语言文件名为`example1c.c`。

### AC代码

```C
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char expr[4096];
int num[4096],top=0;
int op[4096],top2=0;

int isop(char ch)
{
    return ch=='+'||ch=='-'||ch=='*'||ch=='/';
}
void print_num()
{
    int i;
    for(i=0; i<top; i++)
    {
        printf("%d ",num[i]);
    }
}
void print_op()
{
    int i;
    for(i=0; i<top2; i++)
    {
        printf("%c ",op[i]);
    }
}
void process()
{
    char o=op[top2--];
    int b=num[top--];
    int a=num[top--];
    if(o=='+')
    {
        num[++top]=a+b;
    }
    else if(o=='-')
    {
        num[++top]=a-b;
    }
    else if(o=='*')
    {
        num[++top]=a*b;
    }
    else if(o=='/')
    {
        num[++top]=a/b;
    }
}
int main()
{
    fgets(expr,4096,stdin);
    int i=0,n=strlen(expr);
    while(i<n)
    {
        if(expr[i]<=' ')
        {
            ++i;
            continue;
        }
        if(expr[i]=='*'||expr[i]=='/')
        {
            while(top2 && (op[top2]=='/'||op[top2]=='*'))
            {
                process();
            }
            op[++top2]=expr[i];
        }
        else if(expr[i]=='+'||expr[i]=='-')
        {
            while(top2 && isop(op[top2]))
            {
                process();
            }
            op[++top2]=expr[i];
        }
        else if(expr[i]>='0' && expr[i]<='9')
        {
            int x=0;
            while(expr[i]>='0' && expr[i]<='9')
            {
                x=x*10+expr[i]-'0';
                i++;
            }
            num[++top]=x;
            continue;
        }
        else if(expr[i]=='=')
        {
            while(top2 && isop(op[top2]))
            {
                process();
            }
            break;
        }
        i++;
    }
    printf("%d\n",num[top]);
    return 0;
}

```

## 超长正整数的减法

### 问题描述

编写程序实现两个超长正整数（每个最长80位数字）的减法运算。

### 输入形式

从键盘读入两个整数，要考虑输入高位可能为0的情况（如00083）。

1. 第一行是超长正整数A；
2. 第二行是超长正整数B；

### 输出形式

输出只有一行，是长整数A减去长整数B的运算结果，从高到低依次输出各位数字。要求：若结果为0，则只输出一个0；否则输出的结果的最高位不能为0，并且各位数字紧密输出。

### 输入样例

```
234098
134098703578230056
```

### 输出样例

```
-134098703577995958
```

### 样例说明

进行两个正整数减法运算， 234098-134098703578230056 = -134098703577995958。

### 评分标准

 完全正确得20分，每个测试点4分，提交程序文件名为`subtract.c`。

### AC代码

```C
#include <stdio.h>
#include <string.h>
int A[100],B[100],C[100];
char buf[1000];
/*
    string to bigint
*/
void buf2big(char *buf,int *A)
{
    int n=strlen(buf);
    int i;
    for(i=0; i<n; i++)
    {
        A[n-i-1]=buf[i]-'0';
    }
}
/*
    suppose A>B
    return len of C
*/
int dec(int *A,int *B)
{
    int i;
    for(i=0; i<100; i++)
    {
        C[i]=A[i]-B[i];
    }
    for(i=0; i<100-1; i++)
    {
        if(C[i]<0)
        {
            C[i]+=10;
            C[i+1]--;
        }
    }
    int l=100;
    while(l>1 && C[l-1]==0)
    {
        --l;
    }
    return l;
}

int cmp(int *A,int *B)
{
    int i;
    for( i=99; i>=0; --i)
    {
        if(A[i]!=B[i])
            return A[i]-B[i];
    }
    return 0;
}
void print(int n)
{
    int i;
    for(i=n-1; i>=0; --i)
    {
        printf("%d",C[i]);
    }
}

int main()
{
    scanf("%s",buf);
    buf2big(buf,A);
    scanf("%s",buf);
    buf2big(buf,B);
    int neg=0,l=0;
    int c=cmp(A,B);
    if(c>=0)
    {
        l=dec(A,B);
    }
    else if(c<0)
    {
        neg=1;
        l=dec(B,A);
    }
    if(neg)
    {
        putchar('-');
    }
    print(l);
    return 0;
}

```

## 字符串替换（新）

### 问题描述

编写程序将一个指定文件中某一字符串替换为另一个字符串。要求：（1）被替换字符串若有多个，均要被替换；（2）指定的被替换字符串，大小写无关。

### 输入形式

给定文件名为`filein.txt`。从控制台输入两行字符串（不含空格，行末尾都有回车换行符），分别表示被替换的字符串和替换字符串。

### 输出形式

将替换后的结果输出到文件`fileout.txt`中。

### 样例输入

从控制台输入两行字符串：

```
in
out
```

文件filein.txt的内容为：

```
#include <stdio.h>
void main()
{
    FILE * IN;
    if((IN=fopen("in.txt","r"))==NULL)
    {
       printf("Can't open in.txt!");
       return;
    }
    fclose(IN);
}
```

### 样例输出

文件fileout.txt的内容应为：

```
#outclude <stdio.h>
void maout()
{
    FILE * out;
    if((out=fopen("out.txt","r"))==NULL)
    {
       prouttf("Can't open out.txt!");
       return;
    }
    fclose(out);
}
```

### 样例说明

输入的被替换字符串为in，替换字符串为out，即将文件`filein.txt`中的所有in字符串（包括iN、In、IN字符串）全部替换为out字符串，并输出保存到文件`fileout.txt`中。

### 评分标准

该题要求得到替换后的文件内容，共有5个测试点。上传C语言文件名为`replace.c`。

### AC代码

```C
#include <stdio.h>
#include <ctype.h>
#include <string.h>
char in[128],out[128];
char buf[1024];
int main()
{
    FILE *fin,*fout;
    fin=fopen("filein.txt","r");
    fout=fopen("fileout.txt","w");
    scanf("%s%s",in,out);
    int l1,l2;
    l1=strlen(in);
    l2=strlen(out);
    while(fgets(buf,1024,fin))
    {
        int n=strlen(buf);
        int i=0;
        while(i<n)
        {
            int ok=0;
            if(tolower(buf[i])==tolower(in[0]))
            {
                int j=0;
                ok=1;
                while(j<l1)
                {
                    if(i>=n)
                    {
                        ok=0;
                        break;
                    }
                    if(tolower(buf[i+j])!=tolower(in[j]))
                    {
                        ok=0;
                        break;
                    }
                    j++;
                }
                if(ok)
                {
                    i+=j;
                    fprintf(fout,"%s",out);
                }
            }
            fprintf(fout,"%c",buf[i]);
            i++;
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

```

## 全排列数的生成

### 问题描述

输入整数N( $ 1 \le N \le 10 $ )，生成从1~N所有整数的全排列。

### 输入形式

输入整数N。

### 输出形式

输出有N!行，每行都是从1~N所有整数的一个全排列，各整数之间以空格分隔。各行上的全排列不重复。输出各行遵循“小数优先”原则, 在各全排列中，较小的数尽量靠前输出。如果将每行上的输出看成一个数字，则所有输出构成升序数列。具体格式见输出样例。

### 样例输入1

```
1
```

### 样例输出1

```
1
```

### 样例说明1

输入整数N=1，其全排列只有一种。

### 样例输入2

```
3
```

### 样例输出2

```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

### 样例说明2

输入整数N=3，要求整数1、2、3的所有全排列, 共有N!=6行。且先输出1开头的所有排列数，再输出2开头的所有排列数，最后输出3开头的所有排列数。在以1开头的所有全排列中同样遵循此原则。

### 样例输入3

10

### 样例输出3

```
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 10 9
1 2 3 4 5 6 7 9 8 10
1 2 3 4 5 6 7 9 10 8
1 2 3 4 5 6 7 10 8 9
1 2 3 4 5 6 7 10 9 8
1 2 3 4 5 6 8 7 9 10
1 2 3 4 5 6 8 7 10 9
1 2 3 4 5 6 8 9 7 10
1 2 3 4 5 6 8 9 10 7
……………………
```

### 样例说明3

输入整数N=10，要求整数1、2、3、……、10的所有全排列。上例显示了输出的前10行。

### 运行时限

要求每次运行时间限制在20秒之内。超出该时间则认为程序错误。提示：当N增大时，运行时间将急剧增加。在编程时要注意尽量优化算法，提高运行效率。

### 评分标准

该题要求输出若干行整数。

### AC代码

```C
#include <stdio.h>
#include <string.h>
int A[15];
int n;
void dfs(int cur)
{
    if(cur==n)
    {
        int i;
        for(i=0;i<n;i++)
        {
            printf("%d ",A[i]);
        }
        printf("\n");
        return;
    }
    int i;
    for(i=1;i<=n;i++)
    {
        int ok=1;
        int j;
        for(j=0;j<cur;j++)
            if(A[j]==i)
            {
                ok=0;
                break;
            }
        if(ok)
        {
            A[cur]=i;
            dfs(cur+1);
            A[cur]=0;
        }
    }
}

int main()
{
    scanf("%d",&n);
    memset(A,0,sizeof(0));
    dfs(0);
    return 0;
}
```

## 电话薄排序

### 问题描述

编写一个程序，输入N个用户的姓名和电话号码，按照用户姓名的词典顺序排列输出用户的姓名和电话号码。

### 输入形式

用户首先在第一行输入一个正整数，该正整数表示待排序的用户数目，然后在下面多行输入多个用户的信息，每行的输入格式为：姓名 电话。以回车结束每个用户的输入。

### 输出形式

程序输出排序后的结果。每行的输出结果格式也是： 姓名 电话。姓名和电话字段中间没有空格，要求用户姓名不能超过10个字符，超出10个字符时候只取前10个字符作为姓名。电话号码不能超过10位，超过10位时只按10位处理。输出姓名、电话字段各占12个字符宽，输出格式采用默认对齐方式。另外，用户的数量要求不超过50个。

### 样例输入

```
3
amethystic 1234567
amethyst 654321
wangwei 7645434
```

### 样例输出

```
    amethyst      654321
  amethystic     1234567
     wangwei     7645434
```

### 样例说明

程序根据用户姓名的词典顺序排序，最后按照姓名#电话的格式输出。另外，由于规定姓名和电话之间用空格分割，所以输入姓名时请将姓和名一起输入，中间不要有空格。另外输出时候程序将自动补齐12字符宽。程序输出结尾有个回车符。

### 评分标准

完全正确为20分，每个测试点4分。提交程序文件名为`telsort.c`

### AC代码

```C
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct user
{
    char name[16];
    char tele[16];
} user;
user dat[55];
int n;
int cmp(const void *a_,const void *b_)
{
    user *a=(user*)a_,*b=(user*)b_;
    return strcmp(a->name,b->name);
}
char buf[1024];
int main()
{
    int i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",buf);
        memcpy(dat[i].name,buf,10);
        dat[i].name[10]='\0';
        scanf("%s",buf);
        memcpy(dat[i].tele,buf,10);
        dat[i].tele[10]='\0';

    }
    qsort(dat,n,sizeof(user),cmp);
    for(i=0;i<n;i++)
    {
        printf("%12s%12s\n",dat[i].name,dat[i].tele);
    }
    return 0;
}

```