#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=4e5+10;
bool mem1;
int n,m,k;
int a[maxn],b[maxn],c[maxn];
vector<int> ans;
int buc[maxn],bc[maxn],nx[maxn];
int sa[maxn],rnk[maxn],y[maxn];
void solve(){
    for(int i=1;i<=k;i++)   buc[i]=0;
    for(int i=1;i<=m;i++)   buc[rnk[i]=b[i]]++;
    int l=k;for(int i=1;i<=l;i++)   buc[i]+=buc[i-1];
    for(int i=m;i;i--)  sa[buc[b[i]]--]=i;
    for(int w=1;w<=m;w<<=1){
        for(int i=1;i<=l;i++)   buc[i]=0;
        int p=0;
        for(int i=m-w+1;i<=m;i++)   y[++p]=i;
        for(int i=1;i<=m;i++)if(sa[i]>w)y[++p]=sa[i]-w;
        for(int i=1;i<=m;i++)   buc[rnk[i]]++;
        for(int i=1;i<=l;i++)   buc[i]+=buc[i-1];
        for(int i=m;i;i--)  sa[buc[rnk[y[i]]]--]=y[i];
        for(int i=1;i<=m;i++)   y[i]=rnk[i];
        l=rnk[sa[1]]=1;
        for(int i=2;i<=m;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+w]==y[sa[i-1]+w])  rnk[sa[i]]=l;
            else    rnk[sa[i]]=++l;
        }
    }
    for(int i=1;i<=k;i++)buc[i]=bc[i];
    l=0;for(int i=1;i<=m;i++)c[++l]=b[i];for(int i=1;i<=n;i++)c[++l]=a[i];
    for(int i=2;i<=l;i++){
        int j=nx[i-1];
        while(j&&c[j+1]!=c[i])  j=nx[j];
        if(c[j+1]==c[i])    j++;
        nx[i]=j;
    }
    int beg=1;while(beg<=n&&a[beg]==a[1])beg++;
    if(n>=m){
        bool fl=false;
        for(int i=1,j=0;i<=n;i++){
            while(j&&b[j+1]!=a[i])j=nx[j];
            if(b[j+1]==a[i])j++;
            if(j==m){fl=true;break;}
        }
        if(fl){
            for(int i=1;i<=k;i++)c[i]=buc[i];
            vector<int> res;
            for(int i=1;i<=n;i++)if((--c[a[i]])<0)return;
            for(int i=1;i<=k;i++)if((i<a[1])||(i==a[1]&&a[beg]>i))while(c[i]--)res.eb(i);
            for(int i=1;i<=n;i++)res.eb(a[i]);
            for(int i=1;i<=k;i++)if(!((i<a[1])||(i==a[1]&&a[beg]>i)))while(c[i]--)res.eb(i);
            if(ans.empty())ans=res;
            else ans=min(ans,res);
        }
    }
    int L=nx[l],lst,mn=0;while(L>n||L>m)L=nx[L];
    for(int i=1;i<=n;i++)   buc[a[i]]--;
    for(int i=L+1;i<=m;i++) buc[b[i]]--;
    for(int i=1;i<=k;i++)if(buc[i]<0)return;
    mn=lst=L;L=nx[L];
    for(;L;lst=L,L=nx[L]){
        bool fl=true;
        for(int i=L+1;i<=lst;i++){
            int x=b[i];
            buc[x]--;
            if(buc[x]<0){fl=false;break;}
            if(x<a[1]||(x==a[1]&&a[beg]>x)){fl=false;break;}
        }
        if(!fl)break;
        if(rnk[mn+1]>rnk[L+1])  mn=L;
    }
    for(int i=1;i<=k;i++)buc[i]=bc[i];
    for(int i=1;i<=n;i++)   buc[a[i]]--;
    for(int i=mn+1;i<=m;i++) buc[b[i]]--;
    vector<int> res;
    for(int i=1;i<=k;i++)if((i<a[1])||(i==a[1]&&a[beg]>i))while(buc[i]--)res.eb(i);
    for(int i=1;i<=n;i++)res.eb(a[i]);
    for(int i=mn+1;i<=m;i++) res.eb(b[i]);
    for(int i=1;i<=k;i++)if(!((i<a[1])||(i==a[1]&&a[beg]>i)))while(buc[i]--)res.eb(i);
    if(ans.empty())ans=res;
    else ans=min(ans,res);
}
bool mem2;
void matt(int _cases){
    ans.clear();fill(bc+1,bc+k+1,0);
    scanf("%d%d%d",&n,&m,&k);a[n+1]=b[m+1]=0;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=k;i++){int x;scanf("%d",&x);bc[x]++;}
    solve();
    auto SWP=[&](){for(int i=1;i<=n+1||i<=m+1;i++)swap(a[i],b[i]);swap(n,m);};
    SWP();
    solve();
    if(n>m)SWP();
    for(int i=1;i<=n&&i<=m;i++)if(a[i]>b[i]){
        SWP();
        break;
    }
    else if(a[i]<b[i])break;
    int bega=1,begb=1;
    while(bega<=n&&a[bega]==a[1])bega++;
    while(begb<=m&&b[begb]==b[1])begb++;
    for(int i=1;i<=k;i++)   buc[i]=bc[i];
    for(int i=1;i<=n;i++)   buc[a[i]]--;
    for(int i=1;i<=m;i++)   buc[b[i]]--;
    if(*min_element(buc+1,buc+k+1)>=0){
        vector<int> v[3],res;
        for(int i=1;i<=k;i++){
            if((i<a[1])||(i==a[1]&&a[bega]>i)){while(buc[i]--)v[0].eb(i);}
            else if((i<b[1])||(i==b[1]&&b[begb]>i)){while(buc[i]--)v[1].eb(i);}
            else{while(buc[i]--)v[2].eb(i);}
        }
        for(int i:v[0]) res.eb(i);
        for(int i=1;i<=n;i++)res.eb(a[i]);
        for(int i:v[1]) res.eb(i);
        for(int i=1;i<=m;i++)res.eb(b[i]);
        for(int i:v[2]) res.eb(i);
        if(ans.empty())ans=res;
        else ans=min(ans,res);
    }
    if(ans.empty()) puts("-1");
    else{
        for(int i:ans)printf("%d ",i);puts("");
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}