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
const int maxn=1e6+10;
int n,tot;
char s[maxn];
int nex[maxn][26],dep[maxn],mxd[maxn],fa[maxn];
bool en[maxn];
char cid[maxn];
string ans;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline void ins(char *s){
    int len=strlen(s+1);
    int p=0;
    for(int i=1;i<=len;i++){
        int o=s[i]-'a',&t=nex[p][o];
        if(!t)  dep[t=++tot]=dep[p]+1,fa[tot]=p,cid[tot]=s[i];
        p=t;
    }
    en[p]=true;
}
void dfs(int u){mxd[u]=dep[u];for(int i=0;i<26;i++)if(nex[u][i])dfs(nex[u][i]),gmx(mxd[u],mxd[nex[u][i]]);}
string now="";
void dfs2(int u){
    sort(nex[u],nex[u]+26,[&](int x,int y){return mxd[x]<mxd[y];});
    if(u)now+=cid[u];
    int lst=0;
    if(en[u])   ans+='E',lst=u;
    for(int i=0;i<26;i++){
        int t=nex[u][i];
        if(!t)  continue;
        // debug("%d %d %c\n",u,lst,id[i]+'a');
        if(lst&&lst==u)  ans+='T',ans+=cid[t],dfs2(t);
        else if(!lst)    ans+=cid[t],dfs2(t);
        else{
            // TBBBB
            if(1+mxd[lst]-dep[u]<=dep[u]){ans+='T';for(int j=1;j<=mxd[lst]-dep[u];j++)ans+='B';}
            else    ans+=now;
            ans+=cid[t];
            dfs2(t);
        }
        lst=t;
    }
    now.pop_back();
}
int main(){
    // freopen("C:\\Users\\User\\Downloads\\ex_26TG01T4_test\\ex_26TG01T4_test5.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        ins(s);
    }
    dfs(0);
    string tmp="";dfs2(0);
    printf("%d\n%s\n",ans.length(),ans.c_str());
}