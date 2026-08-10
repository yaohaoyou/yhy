#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
mt19937_64 matt(114);
const int maxn=1e5+10,B=256,Block=maxn/B+10;
const ull base=10;
int n,q;
int a[maxn];
int id[maxn],bl[Block],br[Block];
ull pq[maxn];
struct Stack{
    int s[maxn],tp;
    inline void clear(){tp=0;}
    inline bool empty(){return !tp;}
    inline void ep(int x){s[++tp]=x;}
    inline void pop(){tp--;}
    inline int top(){return s[tp];}
    inline int size(){return tp;}
    int& operator[](int x){return s[x];}
}stk;
struct hashnode{
    ull hsh;int len;
    inline void clear(){hsh=len=0;}
    inline hashnode operator+(hashnode y){return (hashnode){y.hsh+pq[y.len]*hsh,len+y.len};}
    inline hashnode operator+(int x){return (hashnode){hsh*base+x,len+1};}
    inline bool operator==(hashnode y){return hsh==y.hsh&&len==y.len;}
    inline bool operator!=(hashnode y){return !(hsh==y.hsh&&len==y.len);}
};
struct hashstr{
    vector<hashnode> s;
    inline void swap(hashstr x){s.swap(x.s);}
    inline bool empty(){return s.empty();}
    inline int size(){return s.size();}
    inline void clear(){s.clear();}
    inline void eb(hashnode x){s.eb(x);}
    inline hashnode query(int l,int r){return (hashnode){s[r].hsh-(l>0?s[l-1].hsh:0)*pq[r-l+1],r-l+1};}
};
hashstr pre[Block],suf[Block];
bool tag[Block];
void rebuild(int x){
    stk.clear();
    tag[x]=false;
    for(int i=bl[x];i<=br[x];i++){
        if(a[i]<0&&!stk.empty()&&stk.top()==-a[i])   stk.pop();
        else    stk.ep(a[i]);
    }
    for(int i=1;i<stk.size();i++)if(stk[i]>0&&stk[i+1]<0)return tag[x]=true,void();
    pre[x].clear();suf[x].clear();
    hashnode now;now.clear();
    for(int i=1;i<=stk.size();i++){if(stk[i]>0)break;now=now+abs(stk[i]);pre[x].eb(now);}
    now.clear();
    for(int i=stk.size();i;i--){if(stk[i]<0)break;now=now+abs(stk[i]);suf[x].eb(now);}
}
void build(){
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(n,i*B);
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=pq[i-1]*base;
    for(int i=1;i<=id[n];i++)   rebuild(i);
}
stack<piii> st;
inline bool query(int l,int r){
    if(id[l]==id[r]){
        stk.clear();
        for(int i=l;i<=r;i++)if(a[i]<0&&!stk.empty()&&stk.top()==-a[i])stk.pop();else stk.ep(a[i]);
        return stk.empty();
    }
    stack<piii>().swap(st);
    {
        int bll=bl[id[l]],brr=br[id[r]];
        bl[id[l]]=l;br[id[r]]=r;
        rebuild(id[l]);rebuild(id[r]);
        bl[id[l]]=bll;br[id[r]]=brr;
    }
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    bool ret=true;
    for(int i=id[l];i<=id[r];i++){
        if(tag[i]){ret=false;break;}
        int il=0,ir=(int)pre[i].size()-1;
        while(!st.empty()&&il<=ir&&(st.top().fi&1)){
            int j=st.top().fi>>1,jl=st.top().se.fi,jr=st.top().se.se;st.pop();
            if(ir-il+1>=jr-jl+1){
                if(pre[i].query(il,il+jr-jl)!=suf[j].query(jl,jr)){ret=false;break;}
                il+=jr-jl+1;
            }
            else{
                if(pre[i].query(il,ir)!=suf[j].query(jl,jl+ir-il)){ret=false;break;}
                jl+=ir-il+1;
                st.ep(j<<1|1,pii(jl,jr));
                il=ir+1;
                break;
            }
        }
        if(!ret)    break;
        if(il<=ir)  st.ep(i<<1,pii(il,ir));
        il=0,ir=(int)suf[i].size()-1;
        if(il<=ir)  st.ep(i<<1|1,pii(il,ir));
    }
    rebuild(id[l]);rebuild(id[r]);
    return ret&&st.empty();
}
int main(){
    scanf("%d%*d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build();
    scanf("%d",&q);
    while(q--){
        int op,x,y;scanf("%d%d%d",&op,&x,&y);
        if(op==1)   a[x]=y,rebuild(id[x]);
        else    puts(query(x,y)?"Yes":"No");
    }
}