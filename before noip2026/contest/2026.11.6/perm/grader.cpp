#include <iostream>
#include <random>
#include <cstring>
#include "perm.h"
using namespace std;
namespace {
    int c,n,cnt;
    unsigned long long seed;
    bool flg;
    mt19937_64 rnd;
    vector<int> p;
    bool vis[500];
}
inline void fail() {
    cout<<"-1\n";
    exit(0);
}
bool query(std::vector<int> q, int a, int b) {
    if (!flg||q.size()!=n) fail();
    ++cnt;
    memset(vis,0,n);
    for (int i=0;i<n;++i) {
        if (q[i]<0||q[i]>=n||vis[q[i]]) fail();
        vis[q[i]]=1;
    }
    if (a<0||a>=n||b<0||b>=n) fail();
    for (int i=1;i<=n;++i) {
        a=q[p[a]];
        if (a==b) return true;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>c>>n;
    p.resize(n);
    for (int i=0;i<n;++i) cin>>p[i];
    flg=1;
    if (perm(c,n)!=p) fail();
    cout<<cnt<<endl;
}