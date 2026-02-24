//  P5906 【模板】回滚莫队&不删除莫队
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=2e5+10,B=450;
int n,q;
int a[maxn];
int id[maxn],bl[460],br[460];
struct ques{
    int l,r,id;
}Q[maxn];
inline bool cmp(ques x,ques y){
    if(id[x.l]!=id[y.l])    return x.l<y.l;
    return x.r<y.r;
}
int b[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   b[i]=a[i];
    sort(b+1,b+n+1);
    int siz=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+siz+1,a[i])-b;
}
int now;
int st[maxn],en1[maxn],en2[maxn];
int ans[maxn];
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        id[i]=(i-1)/B+1;
    }
    discrete();
    for(int i=1;i<=B;i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].id=i;
    }
    sort(Q+1,Q+q+1,cmp);
    for(int i=1,l=0,r=0,lstblo=0;i<=q;i++){
        int ql=Q[i].l,qr=Q[i].r;
        if(id[ql]==id[qr]){
            for(int j=ql;j<=qr;j++) st[a[j]]=0;
            now=0;
            for(int j=ql;j<=qr;j++){if(!st[a[j]])st[a[j]]=j;now=max(now,j-st[a[j]]);}
            for(int j=ql;j<=qr;j++) st[a[j]]=0;
            ans[Q[i].id]=now;
            continue;
        }
        if(id[ql]!=lstblo){  // 访问到新块则清空
            now=0;
            // while(r>br[id[ql]]){st[a[r]]=en1[a[r]]=0;r--;}
            // while(l<br[id[ql]]+1){st[a[l]]=en1[a[l]]=0;l++;}
            for(int j=l;j<=r;j++)   st[a[j]]=en1[a[j]]=0;
            r=br[id[ql]];l=r+1;
            lstblo=id[ql];
        }
        while(r<qr){
            r++;
            if(!st[a[r]])   st[a[r]]=r;
            en1[a[r]]=r;
            now=max(now,r-st[a[r]]);
        }
        ans[Q[i].id]=now;
        int lstl=l;
        while(lstl>ql){
            lstl--;
            if(!en2[a[lstl]])  en2[a[lstl]]=lstl;
            ans[Q[i].id]=max(ans[Q[i].id],max(en1[a[lstl]],en2[a[lstl]])-lstl);
        }
        // 回滚
        while(l>lstl)   en2[a[lstl++]]=0;
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}