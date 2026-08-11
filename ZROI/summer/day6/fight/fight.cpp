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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int n=300,maxn=n+10,maxq=2.5e5+10;
int s,q;
int f[2][maxn][maxn];
struct ques{int cb,fb,ca,fa,id;}Q[maxq];
vector<ques> vq[maxn];
bool ans[maxq];
int main(){
    freopen("fight.in","r",stdin);freopen("fight.out","w",stdout);
    // s=499;
    scanf("%d%d",&s,&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d%d%d",&Q[i].cb,&Q[i].fb,&Q[i].ca,&Q[i].fa);Q[i].id=i;
        vq[Q[i].fb].eb(Q[i]);
    }
    mems(f,0x3f);
    // int cnt=0;
    for(int fb=0;fb<=n;fb++){
        // if(fb%100==0)debug("fb = %d,cnt = %d\n",fb,cnt);
        for(int i=1;i<=n;i++){
            for(int fa=0;fa<=n;fa++){
                for(int cb=fb?f[(fb-1)&1][i][fa]-1:n;cb>=0;cb--){
                    int ca=i;
                    bool flag=false;
                    if(fa){
                        bool f0=true;
                        if(fb&&f[(fb-1)&1][ca][fa-1]>cb)    f0=false;
                        else if(f[fb&1][ca][fa-1]>cb-max(ca-fb*s,0))   f0=false;
                        flag|=f0;
                    }
                    if(!flag){
                        bool f0=true;
                        ca-=max(cb-fa*s,0);
                        if(ca<=0)   flag=true;
                        else if(fb&&f[(fb-1)&1][ca][fa]>cb)  f0=false;
                        else if(f[fb&1][ca][fa]>cb-max(ca-fb*s,0))    f0=false;
                        flag|=f0;
                    }
                    if(!flag){f[fb&1][i][fa]=cb+1;break;}
                }
                // cnt+=f[fb&1][i-1][fa]!=f[fb&1][i][fa];
            }
        }
        for(auto [cb,fb,ca,fa,id]:vq[fb])ans[id]=f[fb&1][ca][fa]<=cb;
    }
    // debug("cnt = %d\n",cnt);
    for(int i=1;i<=q;i++)   puts(ans[i]?"Bob":"Alice");
}