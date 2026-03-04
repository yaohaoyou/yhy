#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10;
int n,q;
int a[maxn];
namespace Trie{
    int cnt,sum,tag;
    int nex[maxn*20][2],s[maxn*20];
    inline void ins(int x){
        sum^=x;
        int p=0;
        for(int i=0;i<20;i++){
            s[p]++;
            bool o=x&(1<<i);
            int &t=nex[p][o];
            if(!t)  t=++cnt;
            p=t;
        }
        s[p]++;
    }
    inline void del(int x){
        sum^=x;
        int p=0;
        for(int i=0;i<20;i++){
            s[p]--;
            bool o=x&(1<<i);
            p=nex[p][o];
        }
        s[p]--;
    }
    inline void upd(){
        tag++;
        int p=0;
        for(int i=0;i<20;i++){
            int &ls=nex[p][0],&rs=nex[p][1];
            if(rs&&(s[rs]&1)) sum^=(1<<i);
            swap(ls,rs);
            if(rs&&(s[rs]&1)) sum^=(1<<i);
            if(ls)  p=ls;
            else break;
        }
    }
}
using namespace Trie;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),ins(a[i]);
    while(q--){
        int op,x,p;scanf("%d",&op);
        if(!op){
            scanf("%d%d",&x,&p);
            del(a[x]+tag);
            a[x]=p-tag;
            ins(a[x]+tag);
        }
        else if(op==1)  upd();
        else printf("%d\n",sum);
    }
}