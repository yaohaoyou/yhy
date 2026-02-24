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
const int maxn=3e5+10;
int q;
string s;
struct ACAM{
    vector<pair<string,int>> S;
    vector<array<int,26>> nex;
    vector<int> fail,en;
    vector<vector<int>> son;
    inline void ins(string s,int x){
        if(nex.empty()) nex.eb(array<int,26>()),en.eb(0);
        int p=0;
        for(char c:s){
            int o=c-'a';
            if(!nex[p][o])  nex[p][o]=nex.size(),nex.eb(array<int,26>()),en.eb(0);
            p=nex[p][o];
        }
        en[p]+=x;
    }
    queue<int> q;
    void build(){
        fail.resize(nex.size());son.resize(nex.size());
        for(int i=0;i<26;i++)if(nex[0][i])q.ep(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();son[fail[u]].eb(u);
            for(int i=0;i<26;i++){
                if(nex[u][i]){
                    fail[nex[u][i]]=nex[fail[u]][i];
                    q.ep(nex[u][i]);
                }
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
    }
    void dfs(int u){en[u]+=en[fail[u]];for(int t:son[u])dfs(t);}
    inline ll query(string s){
        if(nex.empty()) return 0;
        int p=0;ll ans=0;
        for(char c:s){
            int o=c-'a';
            p=nex[p][o];
            ans+=en[p];
        }
        return ans;
    }
    inline void clear(){nex.clear();fail.clear();en.clear();son.clear();}
    inline void merge(ACAM &x){
        for(pair<string,int> &s:x.S)   S.eb(s);
        x.S.clear();x.clear();clear();
    }
    inline void rebuild(){clear();for(pair<string,int> &s:S)ins(s.fi,s.se);build();dfs(0);}
    inline int size(){return S.size();}
    void print(){
        for(int i=0;i<nex.size();i++){
            for(int j=0;j<26;j++)if(nex[i][j])printf("%d %d %c\n",i,nex[i][j],j+'a');
            printf("%d : %d %d\n",i,fail[i],en[i]);
        }
    }
}T[20];
int main(){
    cin>>q;
    while(q--){
        int op;
        cin>>op>>s;
        if(op==1){
            T[0].S.eb(s,1);
            int x=0;
            while(T[x].size()==(1<<x+1))   T[x+1].merge(T[x]),x++;
            T[x].rebuild();
        }
        else if(op==2){
            T[0].S.eb(s,-1);
            int x=0;
            while(T[x].size()==(1<<x+1))    T[x+1].merge(T[x]),x++;
            T[x].rebuild();
        }
        else{
            ll ans=0;
            for(int i=0;i<20;i++)   ans+=T[i].query(s);
            printf("%lld\n",ans);fflush(stdout);
        }
    }
}