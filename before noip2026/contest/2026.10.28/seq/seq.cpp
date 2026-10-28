#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
bool mem1;
const int maxn=2e5+10;
const ll INF=1e18;
int n,k;
int a[maxn];
pii b[maxn];
int lst[maxn];
ll s[maxn],f[maxn],w[maxn];
int tim[maxn];
set<int> mex;
struct line{
    ll k,b;
    line(ll _k=0,ll _b=0){k=_k;b=_b;}
    inline ll get(ll x){return k*x+b;}
};
struct Stack{
    vector<line> st;
    inline line& operator[](int x){return st[x];}
    inline void ep(line x){st.eb(x);}
    inline void pop(){st.pop_back();}
    inline line se(){return st[st.size()-2];}
    inline line top(){return st.back();}
    inline int size(){return st.size();}
    inline bool empty(){return st.empty();}
    inline void clear(){st.clear();}
}stk;
inline bool cmp(line x,line y,line z){  // y 无用
    return __int128(x.b-z.b)*(x.k-y.k)>=__int128(x.b-y.b)*(x.k-z.k);
}
struct cvx{
    Stack st;int p=-1;
    inline void eb(line x){
        while(st.size()>=2&&cmp(st.se(),st.top(),x))st.pop();
        st.ep(x);p=st.size()-1;
    }
    inline ll Q(ll x){
        if(!~p)p=st.size()-1;
        while(p&&st[p-1].get(x)>=st[p].get(x))p--;
        return st[p].get(x);
    }
};
struct convex{
    Stack st;bool sorted;int p;
    inline void eb(line x){st.ep(x);}
    inline ll Q(ll x){
        if(st.empty())return -INF;
        if(!sorted){
            vector<line> tmp;tmp.swap(st.st);
            sort(tmp.begin(),tmp.end(),[&](line x,line y){return x.k<y.k;});
            for(line x:tmp){
                while(st.size()>=2&&cmp(st.se(),st.top(),x))st.pop();
                st.ep(x);
            }
            sorted=true;
        }
        while(p+1<st.size()&&st[p+1].get(x)>=st[p].get(x))p++;
        return st[p].get(x);
    }
};
struct SGT1{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    cvx tr[maxn<<2];
    ll Q(setpos,int pl,int pr,ll x){if(pl>pr)return -INF;if(l>=pl&&r<=pr)return tr[p].Q(x);setmid;ll res=-INF;if(pl<=mid)gmx(res,Q(lson,pl,pr,x));if(pr>mid)gmx(res,Q(rson,pl,pr,x));return res;}
    void U(int x,line s){int p=1,l=0,r=n;while(l^r){setmid;tr[p].eb(s);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p].eb(s);}
}T0;
struct SGT2{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    convex tr[maxn<<2];
    void U(setpos,int pl,int pr,line x){if(pl>pr)return;if(l>=pl&&r<=pr)return tr[p].eb(x);setmid;if(pl<=mid)U(lson,pl,pr,x);if(pr>mid)U(rson,pl,pr,x);}
    ll Q(int x,ll s){int p=1,l=0,r=n;ll res=-INF;while(l^r){setmid;gmx(res,tr[p].Q(s));(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}gmx(res,tr[p].Q(s));return res;}
}T1;
__gnu_pbds::gp_hash_table<int,int> mp[maxn];
void chg(int x,int t){if(x&&tim[x]>0&&b[x].fi<=b[x].se)mp[x][tim[x]]=t-1;tim[x]=t;}
bool mem2;
int main(){
    // freopen("seq.in","r",stdin);freopen("seq.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    mems(lst,0);
    fill(b,b+n+1,pii(1,0));
    mex.ep(0);
    for(int i=1;i<=n;i++){
        int x=a[i];
        if(b[0].fi<=b[0].se)    b[0].se=i;
        else    b[0].fi=b[0].se=i,mex.ep(0);
        if(i-k>0){
            int mx=*mex.rbegin();
            if(b[mx].se==i-k){
                chg(mx,i);
                mex.erase(mx);
                b[mx]=pii(1,0);
                tim[mx]=-1;
            }
            else{
                chg(mx,i);
                b[mx].fi++;
            }
        }
        int l=b[x].fi,r=b[x].se;
        if(l<=r){
            chg(x,i);
            b[x]=pii(1,0);tim[x]=-1;
            mex.erase(x);
            for(int j=x+1;;j++){
                int p=max(i-k+1,lst[j]+1);
                chg(j,i);
                if(p<=r){
                    tim[j]=i;b[j]=pii(p,r);mex.ep(j);
                }
                if(p<=l)    break;
                gmn(r,p-1);
            }
        }
        lst[x]=i;
    }
    for(int i:mex)if(b[i].fi&&b[i].fi<=b[i].se)chg(i,n+1);
    mex.clear();mems(lst,0);fill(b,b+n+1,pii(1,0));
    
    w[0]=0;T0.U(0,line(0,0));T1.U(all,0,mp[0][0],line(0,w[0]));
    mex.ep(0);
    for(int i=1;i<=n;i++){
        f[i]=f[i-1];
        int x=a[i];
        if(b[0].fi<=b[0].se)    b[0].se=i;
        else    b[0].fi=b[0].se=i,mex.ep(0);
        if(i-k>0){
            int mx=*mex.rbegin();
            if(b[mx].se==i-k){
                mex.erase(mx);
                b[mx]=pii(1,0);
            }
            else{
                b[mx].fi++;
                w[mx]=T0.Q(all,b[mx].fi-1,b[mx].se-1,-mx);
                T1.U(all,i,mp[mx][i],line(mx,w[mx]));
            }
        }
        int l=b[x].fi,r=b[x].se;
        if(l<=r){
            b[x]=pii(1,0);
            mex.erase(x);
            for(int j=x+1;;j++){
                int p=max(i-k+1,lst[j]+1);
                // debug("j = %d %d\n",j,p);
                if(p<=r){
                    b[j]=pii(p,r);mex.ep(j);
                    w[j]=T0.Q(all,b[j].fi-1,b[j].se-1,-j);
                    T1.U(all,i,mp[j][i],line(j,w[j]));
                }
                if(p<=l)    break;
                gmn(r,p-1);
            }
        }
        f[i]=max(f[i-1],T1.Q(i,s[i]));
        // printf("f[%d] = %lld\n",i,f[i]);
        T0.U(i,line(s[i],f[i]));
        lst[x]=i;
    }
    printf("%lld\n",f[n]);
}