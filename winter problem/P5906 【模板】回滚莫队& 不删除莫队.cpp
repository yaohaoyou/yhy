#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,B=450;
int n,q,now,tot;
int a[maxn],ans[maxn],beg[maxn],en[maxn],en2[maxn];
unordered_map<int,int> mp;
piii Q[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline void add(int x){if(!beg[a[x]])beg[a[x]]=x;en[a[x]]=x;gmx(now,x-beg[a[x]]);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(mp.find(a[i])==mp.end()) mp[a[i]]=++tot;
        a[i]=mp[a[i]];
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].se.fi,&Q[i].se.se),Q[i].fi=i;
    sort(Q+1,Q+q+1,[&](piii x,piii y){return (x.se.fi-1)/B==(y.se.fi-1)/B?x.se.se<y.se.se:x.se.fi<y.se.fi;});
    int lst=0,l=1,r=0;
    for(int i=1;i<=q;i++){
        int qid=Q[i].fi,ql=Q[i].se.fi,qr=Q[i].se.se;
        if(qr-ql+1<=B){
            for(int i=qr;i>=ql;i--){
                if(!en2[a[i]])  en2[a[i]]=i;
                gmx(ans[qid],en2[a[i]]-i);
            }
            for(int i=ql;i<=qr;i++) en2[a[i]]=0;
            continue;
        }
        int id=(ql-1)/B+1;
        if(id^lst){
            lst=id;mems(beg,0);mems(en,0);mems(en2,0);
            l=min(n,id*B);r=l-1;now=0;
        }
        while(r<qr) add(++r);
        if(ql<l){
            const int L=l;ans[qid]=now;
            while(l>ql){
                l--;
                if(!en2[a[l]])en2[a[l]]=l;
                gmx(ans[qid],max(en2[a[l]],en[a[l]])-l);
            }
            while(l<L)  en2[a[l++]]=0;
        }
        else ans[qid]=now;
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}