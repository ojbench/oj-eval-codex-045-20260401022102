# Problem 045 - T4 (电梯系统)

**ACMOJ Problem ID**: 1467

## Table of Contents

- [Problem 045 - T4 (电梯系统)](#problem-045-t4-电梯系统)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

Implement elevator system for billion-floor building. Support add/cancel requests, action execution with direction logic.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1467. T4 (电梯系统)** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/045/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

3022年，为了解决学校的图书馆在期末考试周常出现的一座难求问题，海上交通大学决定新盖一座有 $10^9$ 层的图书馆。这样，即便全国的人都来海上交通大学的图书馆自习，也不会出现座位不够的情况。现在这座新图书馆的大部分都已经完成了，只差一个电梯系统。听说你很会编程，不知你能不能帮帮忙。

简单起见，我们假设图书馆里只有一部电梯。该电梯有两个属性：**当前所在层次**和**运行方向**。开始时，电梯位于第0层，运行方向为向上。电梯运行规则如下：

（1）如果没有未完成的请求，电梯保持不动，且运行方向不变；

（2）如果当前运行方向上还有未完成的请求，则完成该方向上最近的请求；

（3）否则运行方向反转，并完成新方向上最近的一个请求。

例如，现在电梯位于第2层，方向为上行，在1，3，5层还有未完成的请求；按照此规则，电梯会以3，5，1的顺序完成这三个请求，此后停在1层，方向为下行，直到新请求的出现。你所设计的电梯系统需要支持以下四种操作：

（1）`action`: 让电梯按照上述规则执行下一个请求。如果现在没有未完成的请求，则电梯保持不动，且运行方向不变。

（2）`add x`: 新增第$x$层的请求（$0\le x\le 10^9$）。保证$x$不等于电梯当前所在层，且同一层最多只会同时存在一个请求。

（3）`cancel x`: 取消第$x$层请求（$0\le x\le 10^9$）。保证不会取消一个不存在的请求。

（4）`locate`: 输出电梯当前所在的位置。

本题难度较大，你可以将页面滑动到底部以获取一些提示。

### 输入格式

第一行一个整数 $n$ 表示操作的数量。

接下来 $n$ 行，按顺序每行给出一次操作。

### 输出格式

对于每一个`locate` 操作，输出一行表示电梯所在的位置。

### 样例输入

```
13
locate
add 1
add 2
add 3
cancel 1
action
locate
add 0
action
locate
locate
action
locate
```

### 样例输出

```
0
2
3
3
0
```

### 提交说明

你所提交的代码中**只能使用`cstdio`，`iostream`这两个头文件**。我们将后台检查代码，如果出现其它头文件将直接判为0分。

### 数据范围

测试数据由10个测试点组成，每个测试点10分。各个测试点的性质如下：

| 测试点编号 | $n\le$ |  特殊性质 |
| ---------- | ---- | ---------- |
| 1-4 | $10^3$ | 无|
| 5-7 | $5\times10^5$ | 保证`add`新增请求的位置高于电梯的位置，即电梯自始至终只会向上运行。同时也保证没有`cancel`操作。 |
| 8 | $5\times10^5$ | 保证没有`cancel`操作。|
| 9 | $5\times10^5$ | 保证`add`新增请求的位置高于电梯的位置，即电梯自始至终只会向上运行。 |
| 10 | $5\times10^5$ | 无|

对于每一个测试点，保证 `locate` 操作不会出现超过1000次。

### 一些提示

如果你想拿到本题的高分，一种叫做**二叉堆**的东西可能会派上用场。

二叉堆有什么用？假设你有一个包含 $n$ 个元素的集合（元素都是整数），你有什么办法能知道这个集合里最大的元素是哪一个呢？这当然很简单，你只需要遍历一遍所有元素，找到最大的那一个就可以了。但如果我们需要不断地往集合里**增加新的元素**或者**删除掉集合里最大的元素**，有什么办法能在每一次集合变化后都知道这个集合里最大的元素是哪一个呢？当然，我们可以在每一次集合发生变化之后都重新遍历所有元素以找到最大的那一个。但遍历一遍需要 $O(n)$ 的时间，这太低效了。二叉堆能更高效地解决这个问题。

二叉堆（简称**堆**）是一种满足**堆性质**的二叉树（即每个结点最多只有两个子结点），其中每一个结点都有一个权值。堆可以分为两种：大根堆和小根堆。

> **堆性质**：在一个大根堆中，父亲结点的权值不小于儿子结点的权值；在一个小根堆中，父亲结点的权值不大于儿子结点的权值。

下文将以大根堆为例。如下图所示，这是一个大根堆。

![fig1](https://acm.sjtu.edu.cn/OnlineJudge-pic/20220210-221721-780398.jpg)



根据堆性质，大根堆的堆顶（即根节点）一定是所有元素中的最大值。正如前面所说的，大根堆支持高效地插入一个值或删掉最大值，我们分别介绍如下：

**插入一个值**：最简单的方法就是在最下一层的最右边的结点之后插入（如果最下一层已满，就新增一层）。但一个可能的问题是：插入之后如果不满足堆性质该怎么办？我们可以**向上调整**：如果这个新添加的结点的权值大于它父亲的权值，就交换它们，重复此过程直到堆的性质被满足。下图展示了依次向堆中插入一系列元素之后，堆的变化。不难看出，插入的时间复杂度是 $O(\log n)$的，因为二叉堆的高度是 $O(\log n)$ 的。

![fig2](https://acm.sjtu.edu.cn/OnlineJudge-pic/20220210-221738-241603.gif)

**删除最大值**：换句话说就是删除根结点。如果直接删除，那么堆就裂成两个了。我们不妨考虑插入操作的逆过程，设法将根结点移到最后一个结点，然后直接删掉。然而实际上这不好操作。我们通常采用的方法是，把根结点和最后一个结点直接交换，然后直接删掉（在最后一个结点处的）根结点。但是新的根结点可能不满足堆性质，于是我们可以采用**向下调整**：在该结点的儿子中，找一个较大的，与该结点交换，重复此过程直到底层。不难发现，删除的时间复杂度也是 $O(\log n)$ 的。下图展示了如何从堆中删除最大值。

![fig3](https://acm.sjtu.edu.cn/OnlineJudge-pic/20220210-221747-690830.gif)

**堆的存储**：在编程时，如何存储一个堆呢？这里介绍一种比较方便的存储方法——用数组来存储一个堆。以下图这个堆为例，结点旁的蓝色数字表示该结点在数组中的下标。不难发现，对于存储下标为 $i$ 的结点，它的左儿子的存储位置为 $i\times 2$，它的右儿子的存储位置为 $i\times 2+1$。因此我们不需要显式地构建出堆的形状，只通过下标的运算就可以”操作“这一个堆。

![fig4](https://acm.sjtu.edu.cn/OnlineJudge-pic/20220210-221759-599713.jpg)

下面我们给出用C++实现的堆的部分代码。其中`push`函数的功能是向堆中插入一个值，`pop`函数的功能是删除堆的最大值。我们只给出`push`的实现。如果你想用这段代码的话，请自己仿照完成`pop`的实现。

```C++
struct Heap{
    
    int arr[N], cnt; // arr: 用来存储堆的数组，cnt: 堆中的元素个数。
    
    Heap(){
        cnt = 0;
    }
    
    /* 向堆中插入x */
    void push(int x){
        arr[++cnt]=x;
        for(int i = cnt, j = cnt>>1; j; i=j, j>>=1)
        {
            if(arr[j] < arr[i]){ // 如果父亲的值比儿子的值小，就交换他们
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            else break;
        }
    }
    
    /* 删除堆顶 */
    void pop(){
        // TODO
    }
};
```



以上关于堆的介绍仅供参考。除了堆以外，你当然也可以使用别的方法来得分。

### Input Format

See the problem description above.

### Output Format

See the problem description above.

### Samples

No sample data provided for this problem.

### Data Constraints

See the problem description for constraints.

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 512 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/045/data_test/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
