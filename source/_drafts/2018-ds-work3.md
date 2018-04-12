---
title: 2018-ds-work3
tags:
---

## 五子棋危险判断

### 问题描述

已知两人分别执白棋和黑棋在一个围棋棋盘上下五子棋，若同一颜色的棋子在同一条横行、纵行或斜线上连成5个棋子，则执该颜色棋子的人获胜。编写程序读入某一时刻下棋的状态，并判断是否有人即将获胜，即：同一颜色的棋子在同一条横行、纵列或斜线上连成4个棋子，且该4个棋子的两端至少有一端为空位置。
输入的棋盘大小是19×19，用数字0表示空位置（即没有棋子），用数字1表示该位置下了一白色棋子，用数字2表示该位置下了一黑色棋子。假设同一颜色的棋子在同一条横行、纵列或斜线上连成的棋子个数不会超过4个，并且最多有一人连成线的棋子个数为4。

### 输入形式

从控制台输入用来表示棋盘状态的数字0、1或2；每行输入19个数字，各数字之间以一个空格分隔，每行最后一个数字后没有空格；共输入19行表示棋盘状态的数字。

### 输出形式

若有人即将获胜，则先输出即将获胜人的棋子颜色（1表示白色棋子，2表示黑色棋子），然后输出英文冒号:，最后输出连成4个棋子连线的起始位置（棋盘横行自上往下、纵列自左往右从1开始计数，横行最小的棋子在棋盘上的横行数和纵列数作为连线的起始位置，若在同一行上，则纵列数最小的棋子位置作为起始位置，两数字之间以一个英文逗号,作为分隔符）。
若没有人获胜，则输出英文字符串：No。
无论输出什么结果，最后都要有回车换行符。

### 输入样例1

```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 2 0 1 1 2 0 0 0 0 0 0 0
0 0 0 0 0 2 1 1 1 1 2 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 2 1 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 1 0 2 2 0 0 0 0 0 0 0 0
0 0 0 0 0 2 0 1 0 0 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### 输出样例1

```
1:9,8
```

### 输入样例2

```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 2 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 2 2 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### 输出样例2

```
No
```

### 样例说明

在输入的样例1中，执白棋（数字1表示）的人即将获胜，连成4个棋子且有一端为空的起始位置在第9行第8列，所以输出1:9,8。
在输入的样例2中，还没有同一颜色的棋子连成4个，所以无人即将获胜，直接输出No。

### 评分标准

该题要求判断五子棋的棋盘状态，提交程序文件名为chess.c。

## 小数形式与科学计数法转换（简）

### 问题描述

编写一个程序，将用小数表示的浮点数，转换成科学计数法的形式输出。输入的数据没有符号，小数点前后必有数字，且全为有效数据，即小数点后的末尾数字不为0；小数点前若只有一位数字，可以为0，否则小数点前的最高位数字不为0。

提示：以字符串形式保存相关数据。

### 输入形式

从控制台输入一小数，最后有回车换行符，所有输入的字符数不会超过100。

### 输出形式

以科学计数法形式输出数据。输出的数据由以下几部分构成：
1.底数部分是一个小数或整数，若为小数，则小数点前后必有数字，而且都为有效数字。即：小数点前只有一位大于0的数字，小数点后的末尾数字不能为0。若为整数，则只有一位数字，不带小数点。
2.必有小写字母“e”。
3.指数部分是一个整数，若大于等于0，则不带正号“+”。若小于0，则需要带负号“-”，且整数的最高位数字不为0。

### 输入样例1

```
0.000000000000002
```

### 输出样例1

```
2e-15
```

### 输入样例2

```
8.9845623489651700659
```

### 输出样例2

```
8.9845623489651700659e0
```

### 输入样例3

```
367298599999093453490394859509568659795603.4
```

### 输出样例3

```
3.672985999990934534903948595095686597956034e41
```

### 样例说明

以小数形式输入数据，然后转换成科学计数法形式输出。

### 评分标准

该题要求以科学计数法形式输出数据，提交程序文件名为notation.c。

## 输出文件的末尾行

### 问题描述

命令 tail用来打印文件中最后n行。
命令格式为：tail [-n] filename，其中：
-n ：n表示需要打印的行数，中括号表示-n可省略，省略时默认打印最后10行。
filename ：给定文件名。
如，命令tail -20 example.txt 表示打印文件example.txt的最后20行，用C语言实现该程序。（提示：使用命令行参数）

### 输入形式

tail [-n] filename，其中：-n ：n表示需要打印的行数，中括号表示-n可省略，省略时默认打印最后10行。
filename ：给定文件名。

### 输出形式

向控制台打印输出文件filename的最后n行

### 输入样例

命令：tail  -2  tail.in
tail.in文件内容为：

```
Alcatel provides end-to-end solutions.
It enables enterprises to deliver content to any type of user.
lcatel operates in 130 countries.
Alcatel focus on optimizing their service offerings and revenue streams.
```

### 输出样例

屏幕将显示：

```
lcatel operates in 130 countries.
Alcatel focus on optimizing their service offerings and revenue streams.
```

### 样例说明

使用tail -2 tail.in输出文件tail.in的最后两行。

注意：文件末尾行有可能没有回车换行。

### 评分标准

如果你的程序输出正确得20分，每个测试点4分。提交程序名为tail.c。

## 加密文件

### 问题描述

有一种加密方法为：其使用一个字母串（可以含重复字母，字母个数不超过50）作为密钥。假定密钥单词串为feather，则先去掉密钥单词中的重复字母得到单词串feathr，然后再将字母表中的其它字母以反序追加到feathr的后面：

```
 f e a t h r z y x w v u s q p o n m l k j i g d c b
```

加密字母的对应关系如下：

```
 a b c d e f g h i j k l m n o p q r s t u v w x y z
 f e a t h r z y x w v u s q p o n m l k j i g d c b
```

其中第一行为原始英文字母，第二行为对应加密字母。其它字符不进行加密。编写一个程序，用这种密码加密文件。假定要加密的文件名为encrypt.txt及加密后的文件名为output.txt，并假定输入文件中字母全为小写字母，并且输入密钥也全为小写字母。

### 输入形式

从标准输入中输入密钥串，并从文件encrypt.txt中读入要加密的内容。

### 输出形式

加密后结果输出到文件output.txt中。

### 样例输入

```
feather
```

和文件encrypt.txt中内容，例如被加密的文件encrypt.txt中内容为：

```
c language is wonderful.
```

### 样例输出

加密后output.txt文件中内容为：

```
a ufqzjfzh xl gpqthmrju.
```

### 样例说明

首先将给定的密钥单词去除重复字母，然后按照上面的加密对应表对encrypt.txt文件内容进行加密即可得到加密后的文件，其中只对英文字母进行加密对换，并且假设encrypt.txt中的英文字母全是小写字母。

### 评分标准

该题要求对文件进行加密，共有5个测试点。提交程序名为encrypt.c

## 小型图书管理系统

### 问题描述

小明同学特别喜欢买书看书。由于书较多，摆放杂乱，找起来非常麻烦。这学期小明同学上了数据结构与程序设计课后，决定改变这种状况：用C开发一个小型图书管理系统。系统中包含的图书信息有：书名、作者、出版社、出版日期等。首先，图书管理系统对已有的书（原始书库，存放在一个文本文件中）按书名字典序进行（排序）摆放（即将原始无序的图书信息文件生成一个有序的文件，即新书库），以便查找。该管理系统可以对新书库中图书条目进行如下操作：
1.录入。新增书录入到书库中（即从输入中读入一条图书信息插入到已排序好的图书文件相关位置处）
2.查找。按书名或书名中关键字信息在书库中查找相关图书信息，若有多本书，按字典序输出。
3.删除。输入书名或书名中关键字信息，从书库中查找到相关书并将其删除，并更新书库。

### 输入形式

原始的图书信息（原始书库）保存在当前目录下的books.txt中。
用户操作从控制台读入，首先输入操作功能序号（1代表录入操作，2代表查找操作，3代表删除操作，0代表将已更新的图书信息保存到书库中并退出程序），然后在下一行输入相应的操作信息（录入操作后要输入一条图书信息，查找和删除操作后只要输入书名或书名中部分信息）。程序支行过程中可以进行多次操作，直到退出（输入操作0）程序。
要求：
1、原始文件中的图书信息与录入的图书信息格式相同，每条图书信息都在一行上，包括书名（不超过50个字符）、作者（不超过20个字符）、出版社（不超过30个字符）和出版日期（不超过10个字符），只由英文字母和下划线组成，用一个空格分隔。图书信息总条数不会超过500.
2、下划线字符参加排序。
3、图书不会重名。

### 输出形式

进行录入和删除操作，系统会更新图书信息，但不会在控制台窗口显示任何信息。
进行查找操作后，将在控制台按书名字典序分行输出查找到的图书信息，书名占50个字符宽度，作者占20个字符宽度，出版社占30个字符宽度，出版日期占10个字符宽度，都靠左对齐输出。
最终按字典排序的图书信息保存在当前目录下的ordered.txt中，每条图书信息占一行，格式与查找输出的图书信息相同。

### 样例输入

假设books.txt中保存的原始图书信息为：

```
The_C_programming_language Kernighan Prentice_Hall 1988
Programming_in_C Yin_Bao_Lin China_Machine_Press 2013
Data_structures_and_Algorithm_Analysis_in_C Mark_Allen_Weiss Addison_Wesley 1997
ANSI_and_ISO_Standard_c Plauger Microsoft_Press 1992
Data_structures_and_program_design_in_C Robert_Kruse Pearson_Education 1997
Computer_network_architectures Anton_Meijer Computer_Science_Press 1983
C_programming_guidelines Thomas_Plum Prentice_Hall 1984
Data_structures_using_C Tenenbaum Prentice_Hall 1990
Operating_system_concepts Peterson Addison_Wesley 1983
Computer_networks_and_internets Douglas_E_Come Electronic_Industry 2017
```

用户控制台输入信息为：

```
1
Data_structures_and_C_programs Christopher Addison_Wesley 1988
2
structure
1
The_C_programming_tutor Leon_A_Wortman R_J_Brady 1984
2
rogram
3
rogramming
0
```

### 样例输出

用户输入“2 structure”后，控制台输出：

```
Data_structures_and_Algorithm_Analysis_in_C       Mark_Allen_Weiss    Addison_Wesley                1997
Data_structures_and_C_programs                    Christopher         Addison_Wesley                1988
Data_structures_and_program_design_in_C           Robert_Kruse        Pearson_Education             1997
Data_structures_using_C                           Tenenbaum           Prentice_Hall                 1990
```

用户输入“2 rogram”后，控制台输出：

```
C_programming_guidelines                          Thomas_Plum         Prentice_Hall                 1984
Data_structures_and_C_programs                    Christopher         Addison_Wesley                1988
Data_structures_and_program_design_in_C           Robert_Kruse        Pearson_Education             1997
Programming_in_C                                  Yin_Bao_Lin         China_Machine_Press           2013
The_C_programming_language                        Kernighan           Prentice_Hall                 1988
The_C_programming_tutor                           Leon_A_Wortman      R_J_Brady                     1984
```

ordered.txt文件内容为：

```
ANSI_and_ISO_Standard_c                           Plauger             Microsoft_Press               1992
Computer_network_architectures                    Anton_Meijer        Computer_Science_Press        1983
Computer_networks_and_internets                   Douglas_E_Come      Electronic_Industry           2017
Data_structures_and_Algorithm_Analysis_in_C       Mark_Allen_Weiss    Addison_Wesley                1997
Data_structures_and_C_programs                    Christopher         Addison_Wesley                1988
Data_structures_and_program_design_in_C           Robert_Kruse        Pearson_Education             1997
Data_structures_using_C                           Tenenbaum           Prentice_Hall                 1990
Operating_system_concepts                         Peterson            Addison_Wesley                1983
```

### 样例说明

先读入books.txt中的10条图书信息，按照书名进行字典序排序；用户进行了五次操作，然后退出：第一次操作是插入了一条图书信息，这时有11条图书信息，按书名字典序排序为：

```
ANSI_and_ISO_Standard_c Plauger Microsoft_Press 1992
C_programming_guidelines Thomas_Plum Prentice_Hall 1984
Computer_network_architectures Anton_Meijer Computer_Science_Press 1983
Computer_networks_and_internets Douglas_E_Come Electronic_Industry 2017
Data_structures_and_Algorithm_Analysis_in_C Mark_Allen_Weiss Addison_Wesley 1997
Data_structures_and_C_programs Christopher Addison_Wesley 1988
Data_structures_and_program_design_in_C Robert_Kruse Pearson_Education 1997
Data_structures_using_C Tenenbaum Prentice_Hall 1990
Operating_system_concepts Peterson Addison_Wesley 1983
Programming_in_C Yin_Bao_Lin China_Machine_Press 2013
The_C_programming_language Kernighan Prentice_Hall 1988
```

第二次操作是查找书名包含structure的图书，有4本图书信息按照格式要求输出到屏幕；第三次操作又插入了一条图书信息，这时有12条图书信息；第四次操作查找书名包含rogram的图书，有6本图书信息按照格式要求输出到屏幕；第五次操作是删除书名包含rogramming的图书信息，有三条图书信息要删除，剩下九条图书信息；最后退出程序前将剩余的九条图书信息按照格式要求存储在ordered.txt文件中。

### 评分标准

该程序要求编写图书管理系统。提交程序文件名为books.c。