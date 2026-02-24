#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n,q;
char s[maxn];
bitset<maxn> bs[30];
inline int getid(char c){return c-'a'+1;}
int main(){ 
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)
        bs[getid(s[i])].set(i);
    scanf("%d",&q);
    while(q--){
        int opt,l,r;char c[maxn];
        scanf("%d%d",&opt,&l);
        if(opt==1){
            scanf("%s",c+1);
            bs[getid(s[l])].reset(l);
            s[l]=c[1];
            bs[getid(s[l])].set(l);
        }
        else{
            scanf("%d",&r);scanf("%s",c+1);
            int len=strlen(c+1);
            bitset<maxn> ans;ans.set();
            for(int i=1;i<=len;i++)
                ans&=(bs[getid(c[i])]>>(i-1));
            int pl=(ans>>l).count(),pr=(ans>>(r-len)+2).count();
            printf("%d\n",max(pl-pr,0));
        }
    }
}