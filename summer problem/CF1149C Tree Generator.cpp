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
int n,m,q;
char s1[maxn];
int s[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{
        int mxl,mxr,mx,mn,ans;  // mxl:s[p]-2*min(s[q])q>p
        inline friend tree operator+(tree x,tree y){return {max({x.mxl,y.mxl,x.mx-2*y.mn}),max({x.mxr,y.mxr,y.mx-2*x.mn}),max(x.mx,y.mx),min(x.mn,y.mn),max({x.ans,y.ans,x.mx+y.mxr,x.mxl+y.mx})};}
    }tr[maxn<<2];
    int tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,int s){tr[p].mx+=s;tr[p].mn+=s;tag[p]+=s;tr[p].mxl-=s;tr[p].mxr-=s;}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d%s",&n,&q,s1+1);
    m=2*n-1;
    for(int i=1;i<m;i++){
        s[i]=s[i-1]+(s1[i]=='('?1:-1);
        upd(all,i+1,i+1,s[i]);
    }
    printf("%d\n",tr[1].ans);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        if(s1[l]=='('){upd(all,l+1,m,-2);upd(all,r+1,m,2);}
        else{upd(all,l+1,m,2);upd(all,r+1,m,-2);}
        swap(s1[l],s1[r]);
        printf("%d\n",tr[1].ans);
    }
}
/*
0 -1 0 -1 -2 -3 -2 -1 0
*/