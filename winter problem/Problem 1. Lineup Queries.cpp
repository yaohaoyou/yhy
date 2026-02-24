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
int q;
int main(){
    scanf("%d",&q);
    while(q--){
        int op;ll x,t;scanf("%d%lld%lld",&op,&x,&t);
        if(op==1){
            if(t<x+x){printf("%lld\n",x);continue;}
            ll T=x+x-1;
            while(t>=T+x+1){
                T+=x+1,x=T/2;
            }
            printf("%lld\n",x-t+T);
        }
        else{
            while(true){
                ll st=(t-x-x)/3;
                bool flag=false;
                for(ll a=max(0ll,st-1);a<=st+1;a++){
                    if(x+a==(t-a)/2){t-=a+1;x=0;flag=true;break;}
                }
                // printf("%d\n",flag);
                if(!flag){
                    for(ll a=max(0ll,st-1);a<=st+1;a++)
                        if(x+a==(t-a)/2+1){x+=a;flag=true;break;}
                    // assert(flag);
                    break;
                }
            }
            printf("%lld\n",x);
        }
    }
}