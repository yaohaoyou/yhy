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
const int maxn=4e5+10;
bool mem1;
int q;
priority_queue<int,vector<int>,greater<int>> L[2];
priority_queue<int> pq[2];
ll ans[2];
int be,en;
bool mem2;
inline void clr(auto &x){while(!x.empty())x.pop();}
void matt(int _cases){
    clr(L[0]);clr(L[1]);clr(pq[0]);clr(pq[1]);
    ans[0]=ans[1]=0;
    scanf("%d",&q);
    {
        q--;
        int op,x,y;scanf("%d%d%d",&op,&x,&y);
        if(op==1)   be=y,en=x;
        else    be=x,en=y;
        ans[1]=max(x,y);L[1].ep(max(x,y));pq[1].ep(min(x,y));
        printf("%d\n",be);
    }
    while(q--){
        int op,x,y;scanf("%d%d%d",&op,&x,&y);
        if(op==1){
            ans[0]+=max(be,x);L[0].ep(max(be,x));
            if(L[0].top()<min(be,x))   ans[0]+=min(be,x)-L[0].top(),pq[0].ep(L[0].top()),L[0].pop(),L[0].ep(min(be,x));
            else    pq[0].ep(min(be,x));
            be=y;
            ans[1]+=max(x,y);L[1].ep(max(x,y));
            if(L[1].top()<min(x,y))    ans[1]+=min(x,y)-L[1].top(),pq[1].ep(L[1].top()),L[1].pop(),L[1].ep(min(x,y));
            else    pq[1].ep(min(x,y));
        }
        else if(op==3){
            pq[0].ep(en);pq[0].ep(x);
            ans[0]+=pq[0].top();L[0].ep(pq[0].top());pq[0].pop();
            pq[1].ep(x);pq[1].ep(y);
            ans[1]+=pq[1].top();L[1].ep(pq[1].top());pq[1].pop();
            en=y;
        }
        else{
            L[0].swap(L[1]);pq[0].swap(pq[1]);swap(ans[0],ans[1]);
            ans[1]+=max(be,x);L[1].ep(max(be,x));
            if(L[1].top()<min(be,x))    ans[1]+=min(be,x)-L[1].top(),pq[1].ep(L[1].top()),L[1].pop(),L[1].ep(min(be,x));
            else    pq[1].ep(min(be,x));
            pq[1].ep(en);pq[1].ep(y);ans[1]+=pq[1].top();L[1].ep(pq[1].top());pq[1].pop();
            be=x;en=y;
        }
        printf("%lld\n",ans[0]+be);
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}