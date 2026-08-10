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
int n,q;
pii a[maxn];
bool liv[maxn];
multiset<int,greater<int>> C;
multiset<int> B;
priority_queue<int,vector<int>,greater<int>> pq;
ll solve(){
    B.clear();C.clear();
    for(int i=1;i<=n;i++)if(liv[i]){
        if(a[i].fi==1)  B.ep(a[i].se);
        else    C.ep(a[i].se);
    }
    // for(int i:B)    printf("%d ",i);puts("");
    // for(int i:C)    printf("%d ",i);puts("");
    while(!pq.empty())pq.pop();
    ll ans=(B.size()+C.size()+1)/2;
    for(auto i=C.begin();i!=C.end();i=C.erase(i)){
        int c=*i;
        auto it=B.upper_bound(c);
        if(it==B.begin())   break;
        it--;int b=*it;B.erase(it);
        if(!pq.empty()&&max(b,c)+c>pq.top()){
            ans+=pq.top();pq.pop();
        }
        else{
            ans+=max(b,c)+c;
            pq.ep(min(b,c)+1);
        }
    }
    vector<int> vb,vc;
    for(int i:B)    vb.eb(i);reverse(vb.begin(),vb.end());
    for(int i:C)    vc.eb(i);
    // for(int i:vb)   printf("%d ",i);puts("");
    // for(int i:vc)   printf("%d ",i);puts("");
    for(int i=0;i<vb.size()&&i<vc.size();i++){
        int b=vb[i],c=vc[i];
        if(!pq.empty()&&max(b,c)+c>pq.top()){
            ans+=pq.top();pq.pop();
        }
        else{
            ans+=max(b,c)+c;
            pq.ep(min(b,c)+1);
        }
        // printf("%d\n",ans);
    }
    if(vb.size()>vc.size()){
        for(int i=vc.size();i<vb.size();i+=2)   ans+=vb[i]+1;
    }
    else{
        for(int i=vb.size();i<vc.size();i+=2)   ans+=vc[i]<<1;
    }
    // auto i=B.begin(),j=C.begin();
    // while(i!=B.end()||j!=C.end()){
    //     if(i==B.end()){
    //         ans+=*j*2;
    //         j++;if(j!=C.end())j++;
    //     }
    //     else if(j==C.end()){
    //         ans+=*i+1;
    //         i++;if(i!=B.end())i++;
    //     }
    //     else{
    //         int b=*i,c=*j;i++;j++;
    //         if(!pq.empty()&&max(b,c)+c>pq.top()){
    //             ans+=pq.top();pq.pop();
    //         }
    //         else{
    //             ans+=max(b,c)+c;
    //             pq.ep(min(b,c)+1);
    //         }
    //     }
    //     printf("%lld\n",ans);
    // }
    return ans;
}
int main(){
    mems(liv,1);
    freopen("ferry.in","r",stdin);freopen("ferry.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        int w,t;scanf("%d%d",&w,&t);
        a[i]=pii(w,t);
    }
    printf("%lld\n",solve());
    while(q--){
        int op,w,t;scanf("%d%d",&op,&w);
        if(op==1){scanf("%d",&t);a[++n]=pii(w,t);}
        else    liv[w]=false;
        printf("%lld\n",solve());
    }
}