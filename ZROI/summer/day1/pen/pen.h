#ifndef PEN_H
#define PEN_H

#include <utility>

/*
 * 笔测试(pen)函数交互接口
 *
 * 选手需要实现:std::pair<int,int> solve_one(int N);
 * 选手可调用:  int try_write(int pen);
 */

// 解出一组测试数据的答案,返回所选两支互不相同的笔(编号 1..N)。
// 该函数会被交互库调用恰好 T 次(每组一次)。
std::pair<int, int> solve_one(int N);

// 对「当前组」的笔 pen(1..N)试写一次:
//   返回 1 表示试写成功(该笔墨水减 1);返回 0 表示失败(该笔已空)。
// 每次调用 solve_one 期间,调用 try_write 的次数不得超过 N(N+1)/2。
int try_write(int pen);

#endif  // PEN_H
