#include<bits/stdc++.h>
#include "explore.h"
#define ll long long
#define ull unsigned long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e4+10,maxm=3e5+10;
mt19937_64 matt(659068243ull);
inline int rnd(){return abs((int)matt());}
vector<unsigned long long> Query(vector<unsigned long long> A, vector<int> S);
void Report(int x,int y);
int tot;
inline void report(int x,int y){Report(x+1,y+1);tot++;}
int n,m;
unordered_map<ull,int> mp;
set<int> V;
vector<ull> a,res;
bool fin[maxn];
queue<int> q;
inline bool check(int u){
    if(res[u])  return false;
    fin[u]=true;
    V.erase(u);
    return true;
}
inline bool find(int u){return mp.find(res[u])!=mp.end();}
bool inque[maxn];
inline void bfs(){
    while(!q.empty()){
        int u=q.front();q.pop();inque[u]=false;
        if(fin[u]||!find(u))  continue;
        int i=mp[res[u]];
        if(u==i||fin[i])    continue;
        report(i,u);
        res[u]=0;check(u);
        res[i]^=a[u];check(i);
        if(find(i)){q.push(i);inque[i]=true;}
    }
}
vector<int> tmp;
void solve(int L,int R){
    mems(fin,0);mems(inque,0);
    V.clear();
    for(int i=0;i<n;i++)V.insert(i);
    tmp.clear();
    for(int i=L;i<=R;i++)tmp.eb(i);
    res=Query(a,tmp);
    for(int i=0;i<res.size();i++)
        if(!res[i]){V.erase(i);fin[i]=true;}
    for(int i:V)
        if(find(i)){q.push(i);inque[i]=true;}
    while(tot^(R-L+1)){
        bfs();
        tmp.clear();for(int i:V)    tmp.eb(i);
        if(!tmp.size()||(tot==(R-L+1))) return;
        while(true){
            int s=tmp.size(),x=tmp[rnd()%s],y=tmp[rnd()%s];
            if(x==y||fin[x]||fin[y])    continue;
            if(mp.find(res[y]^a[x])!=mp.end())  swap(x,y);
            if(mp.find(res[x]^a[y])==mp.end())  continue;
            int z=mp[res[x]^a[y]];
            report(x,y);report(x,z);
            res[x]=0;check(x);
            res[y]^=a[x];
            if(find(y)){q.push(y);inque[y]=true;}
            res[z]^=a[x];
            if(find(z)){q.push(z);inque[z]=true;}
            break;
        }
    }
}
void Solve(int N,int M){
    n=N;
    int B=(M-1)/50+1;
    for(int i=0;i<n;i++)a.eb(0);
    for(int i=0;i<n;i++){
        a[i]=matt();
        while(mp[a[i]])    a[i]=matt();
        mp[a[i]]=i;
    }
    int T=50;
    int lst=1;
    while(T--){
        m+=B;m=min(m,M);
        if(!T)  m=M;
        if(lst>m)   return;
        tot=0;
        solve(lst,m);
        lst=m+1;
    }
}