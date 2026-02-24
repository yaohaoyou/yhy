#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define pui pair<ull,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10,B=5e5+1;
int n;
char s[maxn];
int nex[maxn<<1][2];
void solve(){
    scanf("%s",s+1);n=strlen(s+1);
    int cnt=B;
    for(int i=1;i<=n;i++){
        nex[cnt][s[i]-'0']++;
        cnt+=((s[i]-'0')?1:-1);
    }
    cnt=B;
    for(int i=1;i<=n;i++){
        if(nex[cnt][0]&&nex[cnt-1][1])  nex[cnt][0]--,cnt--,putchar('0');
        else if(nex[cnt][1])    nex[cnt][1]--,cnt++,putchar('1');
        else    nex[cnt][0]--,cnt--,putchar('0');
    }
    putchar('\n');
}
int main(){int t;scanf("%d",&t);while(t--)solve();}