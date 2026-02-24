#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10;
int n;
char S[maxn];
int ord[5],buc[5];
int s[maxn],t[maxn],bac[maxn];
ll ans;int out[maxn];
namespace BIT{
    int tr[5];
    inline int lowbit(int x){return x&-x;}
    inline void init(){mems(tr,0);}
    inline void add(int x,int s){while(x<=4){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x-=lowbit(x);}return res;}
}
using namespace BIT;
void solve(){
    ans=-1;
    scanf("%s",S+1);n=strlen(S+1);
    mems(buc,0);
    for(int i=1;i<=n;i++){
        if(S[i]=='A')s[i]=1;if(S[i]=='N')s[i]=2;if(S[i]=='T')s[i]=3;if(S[i]=='O')s[i]=4;
        buc[s[i]]++;
    }
    for(int i=1;i<=4;i++)   ord[i]=i;
    do{
        for(int i=1;i<=4;i++)   bac[ord[i]]=i;
        ll res=0;
        for(int i=1;i<=n;i++)   t[i]=ord[s[i]];
        init();
        for(int i=n;i;i--){
            res+=que(t[i]-1);
            add(t[i],1);
        }
        if(res>ans){
            ans=res;
            int tot=0;
            for(int i=1;i<=4;i++)
                for(int j=1;j<=buc[bac[i]];j++)  out[++tot]=bac[i];
        }

    }while(next_permutation(ord+1,ord+4+1));
    for(int i=1;i<=n;i++){
        char c;
        if(out[i]==1)c='A';if(out[i]==2)c='N';if(out[i]==3)c='T';if(out[i]==4)c='O';
        putchar(c);
    }
    putchar('\n');
}
int main(){int T;scanf("%d",&T);while(T--)solve();}