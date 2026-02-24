#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=3e5+10,maxp=maxn;
int n,m;
int L[maxn];
int len[maxn];
int dp[maxn];  // dp[i] 表示组成 s 的前 i 个字符的最小次数
namespace AC{
    int tot;
    int nex[maxp][26],fail[maxp],dep[maxp];
    inline void insert(char *s){
        int l=strlen(s),p=0;
        for(int i=0;i<l;i++){
            int o=s[i]-'a';
            if(!nex[p][o])  nex[p][o]=++tot;
            dep[nex[p][o]]=dep[p]+1;
            p=nex[p][o];
        }
        len[p]=l;
    }
    queue<int> q;
    void build_fail(){
        for(int i=0;i<26;i++)
            if(nex[0][i])   q.push(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();
            len[u]=max(len[u],len[fail[u]]);
            for(int i=0;i<26;i++){
                int t=nex[u][i];
                if(t)   fail[t]=nex[fail[u]][i],q.push(t);
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
    }
    void query(char *s){
        int p=0;
        for(int i=1;i<=m;i++){
            int o=s[i]-'a';
            p=nex[p][o];
            L[i]=i-len[p];
        }
    }
}
char s[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    inline void pushup(int p){tr[p]=min(tr[ls],tr[rs]);}
    void update(setpos,int x,int s){
        if(l==r)    return tr[p]=s,void();
        setmid;
        if(x<=mid)  update(lson,x,s);
        else    update(rson,x,s);
        pushup(p);
    }
    int query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return tr[p];
        setmid,res=maxn;
        if(pl<=mid) res=query(lson,pl,pr);
        if(pr>mid)  res=min(res,query(rson,pl,pr));
        return res;
    }
}
using namespace SegmentTree;
int main(){
    scanf("%d%s",&n,s+1);m=strlen(s+1);
    for(int i=1;i<=n;i++){
        char t[maxn];
        scanf("%s",t);
        AC::insert(t);
    }
    AC::build_fail();
    AC::query(s);
    mems(dp,0x3f);dp[0]=0;
    mems(tr,0x3f);
    update(all,0,0);
    for(int i=1;i<=m;i++)
        if(L[i]<=i-1){
            dp[i]=query(all,L[i],i-1)+1;
            update(all,i,dp[i]);
        }
    printf("%d\n",dp[m]>m?-1:dp[m]);
}