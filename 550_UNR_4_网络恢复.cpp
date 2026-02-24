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
mt19937_64 matt(844547);
inline int rnd(){return abs((int)matt());}
vector<unsigned long long> Query(vector<unsigned long long> A, vector<int> S);
void Report(int x,int y);
unordered_map<ull,int> mp;
set<int> V;
vector<ull> a;
bool fin[maxn];
void Solve(int n,int m){
    int T=50;
    for(int i=1;i<=n;i++)V.insert(i);
    for(int i=0;i<n;i++)a.eb(0);
    while(T--){
        mp.clear();
        for(int i=0;i<n;i++){
            a[i]=matt();
            while(mp[a[i]])    a[i]=matt();
            mp[a[i]]=i;
        }
        vector<int> tmp;tmp.clear();
        for(int i:V)tmp.eb(i);
        vector<ull> res=Query(a,tmp);
        for(int i=0;i<res.size();i++)   res[i]^=a[i];
        int cnt=40,flag=0;
        while(cnt--){
            for(int i:tmp){
                if(fin[i])  continue;
                int u=mp[a[i]];
                if(u){Report(i,u);V.erase(i);flag=1;res[u]^=a[i];fin[i]=true;}
            }
            if(!flag)break;
        }
        cnt=40;
        tmp.clear();for(int i:V)tmp.eb(i);
        while(cnt--){
            int x=rnd()%tmp.size();
            x=tmp[x];
            if(fin[x])  continue;
            for(int i:tmp){
                if(i==x)    continue;
                if(fin[i])  continue;
                int u=mp[res[x]^a[i]];
                if(u){Report(i,x);Report(x,u);V.erase(x);res[i]^=a[x];res[u]^=a[x];fin[x]=true;}
            }
        }
    }
}