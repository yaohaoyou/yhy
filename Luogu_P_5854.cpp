#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e7+10;
int n;
int a[maxn],l[maxn],r[maxn];
stack<int> stk;
inline char nc() {
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    bool flag = (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2);
    return flag ? EOF : *p1++;
}
inline int read() {
    register int x = 0, sign = 1;
    static char c = nc();
    for (; c > '9' || c < '0'; c = nc()) {
        if (c == '-') sign = -1;
    }
    for (; c <= '9' && c >= '0'; c = nc()) {
        x = (x << 3) + (x << 1) + c - 48;
    }
    return x*sign;
}
int main(){
    n=read();
    for(int i=1;i<=n;++i)   a[i]=read();
    for(int i=1;i<=n;++i){
        int x=0;
        while(!stk.empty()&&a[stk.top()]>a[i]){x=stk.top();stk.pop();}
        if(stk.empty()) l[i]=x;
        else    l[i]=r[stk.top()],r[stk.top()]=i;
        stk.push(i);
    }
    ll ans=0;
    for(int i=1;i<=n;++i)   ans^=(1ll*i*(l[i]+1));
    printf("%lld ",ans);
    ans=0;
    for(int i=1;i<=n;++i)   ans^=(1ll*i*(r[i]+1));
    printf("%lld\n",ans);
}