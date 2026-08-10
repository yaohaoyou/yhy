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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=4e5+10;
int n,m,len;
char s[maxn],t[maxn],a[maxn];
int buc[maxn],rk[maxn],sa[maxn],y[maxn],ht[maxn];
int pre[maxn],nxt[maxn];
void SA(){
    int V='b';
    for(int i=1;i<=len;i++) buc[rk[i]=a[i]]++;
    for(int i=1;i<=V;i++)   buc[i]+=buc[i-1];
    for(int i=1;i<=len;i++) sa[buc[rk[i]]--]=i;
    for(int w=1;w<=len;w++){
        int p=0;
        for(int i=len-w+1;i<=len;i++)   y[++p]=i;
        for(int i=1;i<=len;i++)if(sa[i]>w)y[++p]=sa[i]-w;
        mems(buc,0);
        for(int i=1;i<=len;i++)   buc[rk[i]]++;
        for(int i=1;i<=V;i++)   buc[i]+=buc[i-1];
        for(int i=len;i;i--)    sa[buc[rk[y[i]]]--]=y[i];
        memc(y,rk);
        rk[sa[1]]=V=1;
        for(int i=2;i<=len;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+w]==y[sa[i-1]+w])  rk[sa[i]]=V;
            else    rk[sa[i]]=++V;
        }
        // for(int i=1;i<=len;i++) printf("%d ",sa[i]);puts("");
        // for(int i=1;i<=len;i++) printf("%d ",rk[sa[i]]);puts("");
        if(V==len)    return;
    }
}
void build_ht(){
    int k=0;a[len+1]='?';
    for(int i=1;i<=len;i++){
        if(k)   k--;
        while(a[i+k]==a[sa[rk[i]-1]+k]) k++;
        ht[rk[i]]=k;
    }
}
struct st{
    int st[20][maxn],Log[maxn];
    void build(){
        for(int i=2;i<=len;i++)   Log[i]=Log[i/2]+1;
        memc(st[0],ht);
        for(int i=1;i<=Log[len];i++)
            for(int j=1;j+(1<<i)-1<=len;j++)    st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
int main(){
    scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);
    for(int i=1;i<=n;i++)   a[++len]=s[i];
    a[++len]='#'; 
    for(int i=1;i<=m;i++)   a[++len]=t[i];
    SA();build_ht();st.build();
    // for(int i=1;i<=len;i++) printf("%c",a[i]);puts("");
    // for(int i=1;i<=len;i++) printf("%d ",sa[i]);puts("");
    for(int i=1,pr=0;i<=len;i++){
        if(sa[i]>n+1)   pr=i;
        if(sa[i]<=n)    pre[sa[i]]=pr;
    }
    for(int i=len,nx=0;i;i--){
        if(sa[i]>n+1)   nx=i;
        if(sa[i]<=n)    nxt[sa[i]]=nx;
    }
    for(int i=1;i<=n;i++){
        int x=pre[i]?st.query(pre[i]+1,rk[i]):0,y=nxt[i]?st.query(rk[i]+1,nxt[i]):0;
        // printf("lcp[%d] = %d %d\n",i,x,nxt[i]);
        ht[i]=-max(x,y);
    }
    len=n;st.build();
    int q;scanf("%d",&q);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        int L=1,R=r-l+1,ans=0;
        while(L<=R){
            int mid=(L+R)>>1;
            if(-st.query(l,r-mid+1)>=mid)  ans=mid,L=mid+1;
            else R=mid-1;
        }
        printf("%d\n",ans);
    }
}