// 注意，这里必须使用双引号，不能使用尖括号
#include "disk.h"
// 你可以继续 include 其他头文件
#include<bits/stdc++.h>
using namespace std; // 你大概率需要这个

// 可以定义全局变量
// 可以定义其他函数（不能是 main 函数）

// 你提交的代码中不需要定义 query 函数，这份部分是由交互库实现的。你可以在 solve 中调用 query 函数。

int solve(int n, int z) {
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(query(i,j)==z)	return i*n+j;
  return 0;
}