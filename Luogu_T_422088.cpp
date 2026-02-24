#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e7+10;
int n,k;
string s;
int nxt[maxn],pre[maxn];
stack<int> q;
#define eb push
inline void era(int x){int nx=nxt[x],pr=pre[x];pre[nx]=pr;nxt[pr]=nx;}
void solve(){
    cin>>n>>k>>s;
    s=' '+s;
    nxt[0]=1;
    for(int i=1;i<=n;i++){
        nxt[i]=i+1;
        pre[i]=i-1;
    }
    while(k--){
        for(int i=nxt[0];i<=n;i=nxt[i])
            if(s[pre[i]]==s[nxt[i]])    q.eb(i);
        if(q.empty())   break;
        while(!q.empty()){
            int u=q.top();
            era(u);
            q.pop();
        }
    }
    for(int i=nxt[0];i<=n;i=nxt[i]) cout<<s[i];
    cout<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t,id;
    cin>>t>>id;
    while(t--)  solve();
}