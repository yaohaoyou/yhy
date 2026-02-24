#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=(1<<18)+5,maxc=20;
int n,c,K;
int ans;
int a[maxn],buc[maxc];
bool dp[(1<<maxc)+5];
char s[maxn];
vector<int> v;
void discrete(){
    v.clear();
    for(int i=1;i<=n;i++)if(s[i]==s[n])s[i]='z';
    for(int i=1;i<=n;i++)v.eb(s[i]-'A');
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    c=v.size();
    for(int i=1;i<=n;i++)a[i]=lower_bound(v.begin(),v.end(),s[i]-'A')-v.begin();
}
void init(){
    for(int i=0;i<(1<<c);i++)   dp[i]=false;
    for(int i=0;i<c;i++)    buc[i]=0;
}
void solve(){
    init();
    scanf("%d%d%d%s",&n,&c,&K,s+1);
    discrete();
    int now=(1<<c)-1;
    dp[now^(1<<a[n])]=true;
    for(int i=1;i<=K;i++){
        if(!buc[a[i]])  now^=(1<<a[i]);
        buc[a[i]]++;
    }
    dp[now]=true;
    for(int i=K+1;i<=n;i++){
        buc[a[i-K]]--;
        if(!buc[a[i-K]]) now^=(1<<a[i-K]);
        if(!buc[a[i]])  now^=(1<<a[i]);
        buc[a[i]]++;
        dp[now]=true;
    }
    for(int i=0;i<c;i++)
        for(int j=0;j<(1<<c);j++)
            if(j&(1<<i))    dp[j^(1<<i)]|=dp[j];
    ans=c;
    for(int i=0;i<(1<<c);i++)
        if(!dp[i])   ans=min(ans,__builtin_popcount(i));
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)solve();}