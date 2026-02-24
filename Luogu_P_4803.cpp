#include<bits/stdc++.h>
#define db double
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define pdi pair<db,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2010;
const db eps=1e-12,inf=1e20;
int D,n,K,q;
bool mem1;
struct seg{
    int A,B,w;
    int b;db k;
    void init(){b=A;k=1.0*(B-A)/D;}
    inline db Y(db x){return k*x+b;}
    inline void print(){printf("(0,%d)(%d,%d) : y=%.10lfx+%d\n",A,D,B,k,b);}
}a[maxn];
inline void getmx(ll &x,ll y){(x<y)&&(x=y);}
ll s[maxn][maxn];
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2];
    inline void pushup(int p){tr[p]=max(tr[ls],tr[rs]);}
    void build(setpos,int t){
        if(l==r)    return tr[p]=s[t][l],void();
        setmid;
        build(lson,t);build(rson,t);
        pushup(p);
    }
    ll query(setpos,int pl,int pr){
        if(pl>pr)   return 0;
        if(l>=pl&&r<=pr)    return tr[p];
        setmid;ll res=0;
        if(pl<=mid) res=query(lson,pl,pr);
        if(pr>mid)  res=max(res,query(rson,pl,pr));
        return res;
    }
}T[maxn];
vector<pdi> v;
db vv[maxn][maxn];
int len[maxn];
inline db cross(seg x,seg y){return 1.0*(y.b-x.b)/(x.k-y.k);}
inline ll calc(int x,db y){
    ll now=0;
    for(int i=1;i<=n;i++)
        if(a[i].Y(y)-a[x].Y(y)>eps) now+=a[i].w;
    return now;
}
ll lstans=0;
bool mem2;
int main(){
    // fprintf(stderr,"%.2fmb\n",abs(&mem1-&mem2)/1024.0/1024.0);
    // freopen("seg.in","r",stdin);freopen("seg.out","w",stdout);
    scanf("%d%d%d%d",&D,&K,&n,&q);
    if(D==-6)   freopen("D:\\yhy\\GDFZ_yhy\\down\\seg\\seg6.in","r",stdin),scanf("%d%d%d",&D,&n,&q);
    if(D==-8)   freopen("D:\\yhy\\GDFZ_yhy\\down\\seg\\seg8.in","r",stdin),scanf("%d%d%d",&D,&n,&q);
    for(int i=1;i<=n;i++){scanf("%d%d%d",&a[i].A,&a[i].B,&a[i].w);a[i].init();}
    for(int i=1;i<=n;i++){
        v.clear();
        for(int j=1;j<=n;j++)if(fabs(a[i].k-a[j].k)>eps)v.eb(cross(a[i],a[j]),j);
        sort(v.begin(),v.end());
        len[i]=v.size();
        if(!len[i]) continue;
        ll now=0;
        for(int j=1;j<=n;j++){
            if(i==j)    continue;
            // if(((a[j].k-a[i].k<eps)||(fabs(a[j].k-a[i].k)<eps&&a[j].b>a[i].b))&&a[j].Y(v[0].fi-1)-a[i].Y(v[0].fi-1)<eps)  printf("x = %.2f\n",v[0].fi-1),a[j].print(),puts("and"),a[i].print(),puts("");
            if((fabs(a[j].k-a[i].k)>eps&&a[j].k-a[i].k<eps)||(fabs(a[j].k-a[i].k)<eps&&a[j].b>a[i].b)) now+=a[j].w;
        }
        s[i][0]=now;
        for(int j=0;j<len[i];j++){
            // if((a[v[j].se].Y(v[0].fi-1)-a[i].Y(v[0].fi-1)<eps)&&(a[v[j].se].k-a[i].k<eps)){a[v[j].se].print();puts("and");a[i].print();puts("");}
            if(a[v[j].se].k-a[i].k>eps)   now+=a[v[j].se].w;
            else    now-=a[v[j].se].w;
            s[i][j+1]=now;
        }
        for(int j=1;j<=len[i];j++)  vv[i][j]=v[j-1].fi;
        int tot=0;
        for(int j=1;j<=len[i];j++){
            int k=j;
            while(fabs(vv[i][j]-vv[i][k])<eps)k++;
            k--;
            vv[i][++tot]=vv[i][k];
            s[i][tot]=s[i][k];
            j=k;
        }
        len[i]=tot;
        vv[i][++tot]=inf;
        T[i].build(1,1,len[i],i);
    }
    // q=10;
    while(q--){
        int p,l,r;ll ans=0;
        scanf("%d%d",&p,&l);
        r=l+K;
        int L=lower_bound(vv[p]+1,vv[p]+len[p]+1,l)-vv[p];
        int R=lower_bound(vv[p]+1,vv[p]+len[p]+1,r)-vv[p]-1;
        // printf("(%d,%d,%d) : %d %d %.2f,%d\n",p,l,r,L,R,vv[p][L],s[p][L-1]);
        ans=max(ans,T[p].query(1,1,len[p],L,R));
        // printf("now = %lld\n",ans);
        // for(int i=L;i<=R;i++)   ans=max(ans,s[p][i]);
        // printf("vv : %.30lf\n",vv[p][L]);
        if(vv[p][L]-l>eps)  ans=max(ans,s[p][L-1]);
        // printf("ans = %lld\n",lstans=ans);
        // if(ans==902527223)  puts("--------------------");
        printf("%lld\n",lstans=ans);
    }
}