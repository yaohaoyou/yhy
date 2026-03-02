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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10;
int n,q;
char a[maxn];
int b[maxn],sl[maxn],sr[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct node{
        int L,R;
        node operator+(node y){
            if(R>=y.L)  return {L,y.R+R-y.L};
            return {L+y.L-R,y.R};
        }
    };
    node tr[maxn<<2];
    void build(setpos){if(l==r)return tr[p]={a[l]==')',a[l]=='('},void();setmid;build(lson);build(rson);tr[p]=tr[ls]+tr[rs];}
    node query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;if(pr<=mid)return query(lson,pl,pr);if(pl>mid)return query(rson,pl,pr);return query(lson,pl,pr)+query(rson,pl,pr);}
}
using namespace SegmentTree;
// struct ST{
//     int Log[maxn];
//     int st[20][maxn];
//     void build(){
//         for(int i=2;i<=n;i++)Log[i]=Log[i/2]+1;
//         for(int i=1;i<=n;i++)st[0][i]=b[i];
//         for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
//     }
//     inline int query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
// }st;
int main(){
    scanf("%d%d%s",&n,&q,a+1);
    build(all);
    // for(int i=1;i<=n;i++){
    //     if(a[i]=='(')   b[i]=b[i-1]+1;
    //     else b[i]=b[i-1]-1;
    // }
    // for(int i=1;i<=n;i++){
    //     if(a[i]==')'){sl[i]=0;continue;}
    //     int j=i;while(j<=n&&a[j]=='(')j++;j--;
    //     for(int k=i,l=j-i+1;k<=j;k++,l--)sl[k]=l;
    //     i=j;
    // }
    // for(int i=1;i<=n;i++){
    //     if(a[i]==')'){sl[i]=0;continue;}
    //     int j=i;while(j<=n&&a[j]=='(')j++;j--;
    //     for(int k=i,l=j-i+1;k<=j;k++,l--)sl[k]=l;
    //     i=j;
    // }
    // st.build();
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        // if(l==r){puts("Finite");continue;}
        node x=query(all,l,r);
        if(x.L==x.R)    puts("Infinite");
        else puts("Finite");
        // if(a[l]==')'){
        //     if(a[r]=='('){
        //         if(r==l+1){puts("Infinite");continue;}
        //         int mn=st.query(l+1,r-1);
        //         if(mn==b[l]&&b[r-1]==b[l])  puts("Infinite");
        //         else puts("Finite");
        //     }
        //     else    puts("Finite");
        // }
        // else{
        //     int mn=st.query(l,r);
        //     if(mn!=b[l-1])  puts("Finite");
        //     else{
        //         if(b[r]==b[l-1])    puts("Infinite");
        //         else puts("Finite");
        //     }
        // }
    }
}