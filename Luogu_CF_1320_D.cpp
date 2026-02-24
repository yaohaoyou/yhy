#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define pui pair<ull,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10,base=3,mod=998244353;
int n,q;
int inv;
bool a[maxn];
char s[maxn];
int pq[maxn];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){
        int res=1;
        while(y){
            if(y&1) res=1ll*res*x%mod;
            x=1ll*x*x%mod;
            y>>=1;
        }
        return res;
    }
}
using namespace MyMod;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define setpos int p,int l,int r
    #define setmid int mid=(l+r)>>1
    #define all 1,1,n
    bool tag[maxn<<2];
    int hd1[maxn<<2],en1[maxn<<2];
    int hd2[maxn<<2],en2[maxn<<2];
    int len1[maxn<<2],len2[maxn<<2];
    int hsh1[maxn<<2],hsh2[maxn<<2];
    struct tree{int len;int hsh,hd,en;bool operator==(tree x)const{return len==x.len&&hsh==x.hsh;}};
    inline void pushtag(int p){
        swap(len1[p],len2[p]);
        swap(hsh1[p],hsh2[p]);
        swap(hd1[p],hd2[p]);
        swap(en1[p],en2[p]);
        tag[p]^=1;
    }
    inline void pushdown(int p){if(!tag[p])return;pushtag(ls);pushtag(rs);tag[p]=false;}
    inline void pushup(int p){
        hd1[p]=hd1[ls];en1[p]=en1[rs];
        if(!~hd1[p])    hd1[p]=hd1[rs];
        if(!~en1[p])    en1[p]=en1[ls];
        hd2[p]=hd2[ls];en2[p]=en2[rs];
        if(!~hd2[p])    hd2[p]=hd2[rs];
        if(!~en2[p])    en2[p]=en2[ls];
        int llen1=len1[ls],rlen1=len1[rs],llen2=len2[ls],rlen2=len2[rs],lh1=hsh1[ls],lh2=hsh2[ls],rh1=hsh1[rs],rh2=hsh2[rs];
        if(en1[ls]==1&&hd1[rs]==1){if(len1[ls]==1)hd1[p]=0;if(len1[rs]==1)en1[p]=0;mdel(hsh1[ls],1);mmul(hsh1[ls],inv);mdel(hsh1[rs],pq[len1[rs]-1]);len1[ls]--;len1[rs]--;}
        if(en2[ls]==1&&hd2[rs]==1){if(len2[rs]==1)en2[p]=0;if(len2[ls]==1)hd2[p]=0;mdel(hsh2[ls],1);mmul(hsh2[ls],inv);mdel(hsh2[rs],pq[len2[rs]-1]);len2[ls]--;len2[rs]--;}
        len1[p]=imadd(len1[ls],len1[rs]);
        len2[p]=imadd(len2[ls],len2[rs]);
        hsh1[p]=imadd(hsh1[rs],immul(hsh1[ls],pq[len1[rs]]));
        hsh2[p]=imadd(hsh2[rs],immul(hsh2[ls],pq[len2[rs]]));
        if(!len1[p])    hd1[p]=en1[p]=-1;
        if(!len2[p])    hd2[p]=en2[p]=-1;
        len1[ls]=llen1,len1[rs]=rlen1,len2[ls]=llen2,len2[rs]=rlen2,hsh1[ls]=lh1,hsh2[ls]=lh2,hsh1[rs]=rh1,hsh2[rs]=rh2;
    }
    void update(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return pushtag(p);
        pushdown(p);
        setmid;
        if(pl<=mid) update(lson,pl,pr);
        if(pr>mid)  update(rson,pl,pr);
        pushup(p);
    }
    tree query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return {len1[p],hsh1[p],hd1[p],en1[p]};
        pushdown(p);
        setmid;
        if(pr<=mid) return query(lson,pl,pr);
        if(pl>mid)  return query(rson,pl,pr);
        tree L=query(lson,pl,pr),R=query(rson,pl,pr),res;
        res.hd=L.hd;res.en=R.en;
        if(!~res.hd)   res.hd=R.hd;
        if(!~res.en)   res.en=L.en;
        if(L.en==1&&R.hd==1){if(L.len==1)res.hd=0;if(R.len==1)res.en=0;mdel(L.hsh,1);mmul(L.hsh,inv);mdel(R.hsh,pq[R.len-1]);L.len--;R.len--;}
        res.len=L.len+R.len;res.hsh=imadd(immul(L.hsh,pq[R.len]),R.hsh);
        if(!res.len)    res.hd=res.en=-1;
        return res;
    }
    void build(setpos){
        if(l==r){
            hsh1[p]=hd1[p]=en1[p]=a[l];
            hsh2[p]=hd2[p]=en2[p]=!a[l];
            len1[p]=len2[p]=1;
            // printf("[%d,%d] : %d,%llu (%d,%d)\n",l,r,len1[p],hsh1[p],hd1[p],en1[p]);
            return;
        }
        setmid;
        build(lson);build(rson);
        pushup(p);
        // printf("[%d,%d] : %d,%llu (%d,%d)\n",l,r,len1[p],hsh1[p],hd1[p],en1[p]);
    }
}
using namespace SegmentTree;
int main(){
    inv=qpow(base,mod-2);
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)   a[i]=s[i]-'0';
    pq[0]=1;for(int i=1;i<=n;i++)   pq[i]=immul(pq[i-1],base);
    build(all);
    scanf("%d",&q);
    while(q--){
        int len,l,r,L,R;
        scanf("%d%d%d",&l,&L,&len);
        r=l+len-1;R=L+len-1;
        puts(query(all,l,r)==query(all,L,R)?"Yes":"No");
    }
}