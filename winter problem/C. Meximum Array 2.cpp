#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=110;
int n,k,q;
int a[maxn];
piii Q[maxn];
bool st[maxn];
void matt(int _cases){
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=q;i++)   scanf("%d%d%d",&Q[i].fi,&Q[i].se.fi,&Q[i].se.se);
    sort(Q+1,Q+q+1);
    mems(a,-1);mems(st,0);
    for(int i=1;i<=q;i++){
        int op=Q[i].fi,l=Q[i].se.fi,r=Q[i].se.se;
        if(op==1){
            for(int j=l;j<=r;j++)a[j]=k;
        }
        else{
            for(int j=l;j<=r;j++)if(a[j]==k)a[j]=1e9;
        }
    }
    for(int i=1;i<=q;i++){
        int op=Q[i].fi,l=Q[i].se.fi,r=Q[i].se.se;
        if(op==1)   continue;
        queue<int> v;
        mems(st,0);
        for(int j=l;j<=r;j++){
            if(a[j]>=k) continue;
            if(!~a[j])  v.ep(j);
            else st[a[j]]=true;
        }
        for(int j=0;j<k;j++){
            if(st[j])   continue;
            if(v.empty())while(true);
            a[v.front()]=j;v.pop();
            st[j]=true;
        }
    }
    for(int i=1;i<=n;i++)if(!~a[i])a[i]=1e9;
    for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}  