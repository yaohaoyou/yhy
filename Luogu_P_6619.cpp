#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e6+10;
int n;
struct Ques{
    int op,t,x,y,id;
}a[maxn];
int v[maxn],len;
inline void discrete(){
    sort(v+1,v+len+1);
    len=unique(v+1,v+len+1)-v-1;
    for(int i=1;i<=n;i++)
        if(a[i].op==1) a[i].x=lower_bound(v+1,v+len+1,a[i].x)-v;
}
namespace BIT{
    int tr[2][maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int y,int s){while(x<=len){tr[y][x]+=s;x+=lowbit(x);}}
    inline int que(int x,int y){if(x>len)return 0;int res=0;while(x){res+=tr[y][x];x-=lowbit(x);}return res;}
    inline int binary(){
        int p=0,s0=0,s1=que(len,1);
        for(int i=20;~i;i--){
            if(p+(1<<i)>len)    continue;
            if(s0+tr[0][p+(1<<i)]>s1-tr[1][p+(1<<i)])   continue;
            p+=(1<<i);
            s0+=tr[0][p];s1-=tr[1][p];
        }
        return p;
    }
    inline int binary2(int s){
        int p=0,s0=0,s1=que(len,1);
        for(int i=20;~i;i--){
            if(p+(1<<i)>len)    continue;
            int ns0=s0+tr[0][p+(1<<i)],ns1=s1-tr[1][p+(1<<i)];
            if(min(ns0,ns1)==s){
                p+=(1<<i);
                s0=ns0;s1=ns1;
            }
            else if(ns0<=ns1){
                p+=(1<<i);
                s0=ns0;s1=ns1;
            }
        }
        // printf("%d and %d\n",min(s0,s1),s);
        return p;
    }
}
using namespace BIT;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].op,&a[i].t);
        if(a[i].op==1){scanf("%d%d",&a[i].x,&a[i].y);v[++len]=a[i].x;}
        a[i].id=i;
    }
    discrete();
    len++;
    for(int i=1;i<=n;i++){
        if(a[i].op==1)  add(a[i].x+a[i].t,a[i].t,a[i].y);
        else    add(a[a[i].t].x+a[a[i].t].t,a[a[i].t].t,-a[a[i].t].y);
        int p=binary(),res1=min(que(p,0),que(len,1)-que(p,1)),res2=min(que(p+1,0),que(len,1)-que(p+1,1));
        // printf("p = %d : (%d,%d) vs (%d,%d)\n",p,v[p],res1,v[p+1],res2);
        int ans2=max(res1,res2);
        if(!ans2){puts("Peace");continue;}
        int ans1=res1>res2?p:binary2(ans2);
        printf("%d %d\n",v[ans1],ans2<<1);
    }
}