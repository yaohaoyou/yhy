---
title: '光速幂学习笔记'
date: 2024-10-30 09:09:31
tags: [算法]
published: true
hideInList: false
feature: 
isTop: false
---
多次询问 $a^x \bmod p$。

选定一个数 $B$，预处理出 $a^i\bmod p,i\in [0,B)$ 和 $a^{i\times B} \bmod p,i\in[1,\frac{(p-1)}B)$，询问时 $a^x \bmod p=a^{\lfloor \frac x B \rfloor} \times a^{x \bmod B} \bmod p$，取 $B=\sqrt p$ 时可以做到 $O(\sqrt p) - O(1)$ 快速幂。

然而 $O(\sqrt p)$ 可能还是太慢了，实际上可以做到取一个 $B$，复杂度为 $O(\log_Bp \times B) - O(\log_Bp)$，后面的 $\log_Bp$ 基本就只是常数了，可以按需求平衡复杂度，其实不太好理解，下面放一份 $B=32$ 的代码，这应该是比较优的块长了，常数较小。

```c
inline void init(int x){
        Pow[0][0]=Pow[1][0]=Pow[2][0]=Pow[3][0]=Pow[4][0]=Pow[5][0]=1;
        for(int i=1;i<S;i++)   Pow[0][i]=Pow[0][i-1]*x%mod;
        int b=immul(Pow[0][S-1],x);
        for(int i=1;i<S;i++)    Pow[1][i]=Pow[1][i-1]*b%mod;
        b=immul(Pow[1][S-1],b);
        for(int i=1;i<S;i++)    Pow[2][i]=Pow[2][i-1]*b%mod;
        b=immul(Pow[2][S-1],b);
        for(int i=1;i<S;i++)    Pow[3][i]=Pow[3][i-1]*b%mod;
        b=immul(Pow[3][S-1],b);
        for(int i=1;i<S;i++)    Pow[4][i]=Pow[4][i-1]*b%mod;
        b=immul(Pow[4][S-1],b);
        for(int i=1;i<S;i++)    Pow[5][i]=Pow[5][i-1]*b%mod;
    }
    inline int qpow(int y){return Pow[5][(y>>25)]*Pow[4][(y>>20)&(S-1)]%mod*Pow[3][(y>>15)&(S-1)]%mod*Pow[2][(y>>10)&(S-1)]%mod*Pow[1][(y>>5)&(S-1)]%mod*Pow[0][y&(S-1)]%mod;}
}POW;
```

实测尽量添加 ``#pragma unroll(4)`` 实现并行，``Pow`` 可以开 ``long long`` 避免多次 ``int`` 强转。

[完整代码](http://goj.wiki/d/Union2024/record/6720c6c62a3076890aff827e)