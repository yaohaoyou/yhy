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
const int maxn=2e5+10;
int n;
string ss[maxn];
vector<int> son[maxn*30];
int res[maxn],bck[maxn];
namespace AC{
    inline int getnum(char x){return x-'a'+1;}
    namespace Trie{
        int cnt=0;
        int nex[maxn][30],en[maxn*30],idx[maxn];
        void insert(string s,int id){
            int p=0;
            for(int i=0;i<s.length();i++){
                int x=getnum(s[i]);
                if(!nex[p][x])  nex[p][x]=++cnt;
                p=nex[p][x];
            }
            if(!en[p])  en[p]=id;
            idx[id]=en[p];
            bck[id]=p;
        }
    }
    using namespace Trie;
    queue<int> q;
    int fail[maxn*30];
    void find(string s){
        int p=0;
        for(int i=0;i<s.length();i++){
            p=nex[p][getnum(s[i])];
            res[p]++;
        }
    }
    void build(string s){
        for(int i=1;i<=26;i++)  if(nex[0][i])   q.push(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();son[fail[u]].eb(u);
            for(int i=1;i<=26;i++){
                if(nex[u][i]){
                    fail[nex[u][i]]=nex[fail[u]][i];
                    q.push(nex[u][i]);
                }
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
    }
}
void dfs(int u){
    for(int t:son[u]){
        dfs(t);
        res[u]+=res[t];
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>ss[i];
        AC::insert(ss[i],i);
    }
    string s;
    cin>>s;
    AC::build(s);
    AC::find(s);
    dfs(0);
    for(int i=1;i<=n;i++)   cout<<res[bck[AC::idx[i]]]<<'\n';
}