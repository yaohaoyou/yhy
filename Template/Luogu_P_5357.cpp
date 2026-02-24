//  P5357 【模板】AC 自动机
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=2e5+10;
int n;
string ss[maxn];
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
        }
    }
    using namespace Trie;
    queue<int> q;
    int fail[maxn*30],in[maxn*30],ans[maxn],res[maxn];
    void find(string s){
        int p=0;
        for(int i=0;i<s.length();i++){
            p=nex[p][getnum(s[i])];
            res[p]++;
        }
    }
    void topu(){
        for(int i=1;i<=cnt;i++)
            if(!in[i])  q.push(i);
        while(!q.empty()){
            int u=q.front(),v;
            q.pop();
            ans[en[u]]=res[u];
            v=fail[u];
            res[v]+=res[u];
            if(!(--in[v]))  q.push(v);
        }
    }
    void build(string s){
        for(int i=1;i<=26;i++)  if(nex[0][i])   q.push(nex[0][i]);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=1;i<=26;i++){
                if(nex[u][i]){
                    fail[nex[u][i]]=nex[fail[u]][i];
                    in[nex[fail[u]][i]]++;
                    q.push(nex[u][i]);
                }
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
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
    AC::topu();
    for(int i=1;i<=n;i++)   cout<<AC::ans[AC::idx[i]]<<'\n';
}