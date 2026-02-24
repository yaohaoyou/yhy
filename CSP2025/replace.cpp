#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define puu pair<ull,ull>
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,maxl=5e6;
const ull bs=173,bss=31ull,b2=57432896234431ull,bs2=79843276894685413ull;
int n,q;
string a[maxn],b[maxn],s[maxn],t[maxn];
pii p[maxn];
int ans[maxn];
int tot;
map<puu,int> mp;
struct BIT{
    int siz;
    int tr[maxl];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=siz){tr[x]+=s;x+=lowbit(x);}}
    inline int query(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline void upd(int l,int r,int s){add(l,s);add(r+1,-s);}
    inline void clear(){for(int i=0;i<=siz;i++)tr[i]=0;siz=0;}
}bit;
struct Trie{
    int cnt;
    vector<array<int,26>> nex;
    vector<int> L,R;
    inline void build(){nex.eb(array<int,26>());L.eb(0);R.eb(0);}
    inline int ins(string s,int typ){
        int len=s.length(),p=0;
        for(int i=0;i<len;i++){
            int o=s[i]-'a';
            if(!nex[p][o])  nex[p][o]=nex.size(),nex.eb(array<int,26>()),L.eb(0),R.eb(0);
            p=nex[p][o];
        }
        return p;
    }
    void dfs(int u){
        L[u]=++cnt;
        for(int i=0;i<26;i++)if(nex[u][i])dfs(nex[u][i]);
        R[u]=cnt;
    }
}T[maxn][2];
vector<piii> vec[maxn];
vector<pii> ins[maxl],era[maxl],vq[maxl];
inline ull hsh(string s){ull res=0;for(char i:s)res=res*bs+i;return res;}
inline ull hsh2(string s){ull res=0;for(char i:s)res=res*b2+i;return res;}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        string x="",y="",yy="",z="";
        int l,r,len=a[i].length();
        for(int j=0;j<len;j++)if(a[i][j]!=b[i][j]){l=j;break;}else x+=a[i][j];
        for(int j=len-1;~j;j--)if(a[i][j]!=b[i][j]){r=j;break;}else z+=a[i][j];
        reverse(x.begin(),x.end());reverse(z.begin(),z.end());
        for(int j=l;j<=r;j++)   y+=a[i][j],yy+=b[i][j];
        ull h1=hsh(y)*bss+hsh(yy),h2=hsh2(y)*bs2+hsh2(yy);int &id=mp[puu(h1,h2)];
        if(!id) id=++tot,T[id][0].build(),T[id][1].build();
        int pa=T[id][0].ins(x,0),pb=T[id][1].ins(z,0);
        vec[id].eb(pii(pa,pb),0);
    }
    mems(ans,-1);
    for(int i=1;i<=q;i++){
        cin>>s[i]>>t[i];
        if(s[i].length()^t[i].length()){ans[i]=0;continue;}
        string x="",y="",yy="",z="";
        int l,r,len=s[i].length();
        for(int j=0;j<len;j++)if(s[i][j]!=t[i][j]){l=j;break;}else x+=s[i][j];
        for(int j=len-1;~j;j--)if(s[i][j]!=t[i][j]){r=j;break;}else z+=s[i][j];
        reverse(x.begin(),x.end());reverse(z.begin(),z.end());
        for(int j=l;j<=r;j++)   y+=s[i][j],yy+=t[i][j];
        // if(i==151)  cout<<s[i]<<'\n'<<t[i]<<'\n'<<x<<'\n'<<z<<'\n';
        ull h1=hsh(y)*bss+hsh(yy),h2=hsh2(y)*bs2+hsh2(yy);
        if(mp.find(puu(h1,h2))==mp.end()){ans[i]=0;continue;}
        int id=mp[puu(h1,h2)],px=T[id][0].ins(x,i),py=T[id][1].ins(z,i);
        vec[id].eb(pii(px,py),i);
    }
    for(int i=1;i<=tot;i++){
        T[i][0].dfs(0);T[i][1].dfs(0);
        // printf("i = %d\n",i);
        for(piii t:vec[i]){
            int x=t.fi.fi,y=t.fi.se,o=t.se;
            // printf("%d %d %d\n",x,y,o);
            if(!o){ins[T[i][0].L[x]].eb(T[i][1].L[y],T[i][1].R[y]);era[T[i][0].R[x]+1].eb(T[i][1].L[y],T[i][1].R[y]);}
            else vq[T[i][0].L[x]].eb(T[i][1].L[y],o);
        }
        int m=T[i][0].cnt;bit.siz=T[i][1].cnt;
        for(int j=1;j<=m;j++){
            for(pii k:ins[j])   bit.upd(k.fi,k.se,1);ins[j].clear();
            for(pii k:era[j])   bit.upd(k.fi,k.se,-1);era[j].clear();
            for(pii k:vq[j])    ans[k.se]=bit.query(k.fi);vq[j].clear();
        }
        era[m+1].clear();
        bit.clear();
    }
    for(int i=1;i<=q;i++)   cout<<ans[i]<<'\n';
}