#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n;
ll tagl,tagr;
int len[maxn];
priority_queue<ll> ql;
priority_queue<ll,vector<ll>,greater<ll>> qr;
ll ans;
inline void pushl(int x){ql.push(x-tagl);}
inline void pushr(int x){qr.push(x-tagr);}
int main(){
    scanf("%d",&n);
    int l,r;scanf("%d%d",&l,&r);
    ql.push(l);qr.push(r);
    for(int i=2;i<=n;i++){
        scanf("%d%d",&l,&r);
        len[i]=r-l;
        tagl-=len[i];tagr+=len[i-1];
        ll L=ql.top()+tagl,R=qr.top()+tagr;
        if(l<L){
            ans+=L-l;
            // ql.top() 变为斜率为 0 的线段
            ql.pop();
            pushr(L);
            pushl(l);pushl(l);
        }
        else if(l>R){
            ans+=l-R;
            // qr.top() 变为斜率为 0 的线段
            qr.pop();
            pushl(R);
            pushr(l);pushr(l);
        }
        else{
            // l 成为断点，左边斜率为 -1，右边为 1
            pushl(l);pushr(l);
        }
    }
    printf("%lld\n",ans);
}