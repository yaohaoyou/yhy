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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e5+100,maxq=1e6+10,B=128;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
int n,m,q,blo;
int a[maxn],b[maxn],c[maxn],id[maxn],f[maxn],g[maxn];  // f[i] 表示第 i 块的开头极长 1 段长，g[i] 表示第 i 块总 1 个数
int L[maxn],R[maxn];
bool vis[maxn];
int ans[maxq];
int pr[maxn],nx[maxn];
struct List{
    int hd,en;
    void init(){hd=0;en=m+1;nx[hd]=en;pr[en]=hd;}
    inline void ins(int x,int pre){pr[x]=pre;nx[x]=nx[pre];pr[nx[x]]=nx[pre]=x;}
    inline void era(int x){pr[nx[x]]=pr[x];nx[pr[x]]=nx[x];}
    inline int pre(int x){return pr[x];}
    inline int nxt(int x){return nx[x];}
}ls;
inline int bid(int x){return (x-1)/B+1;}
unordered_map<int,int> nw;
struct ques{int l,r,id;}Q[maxq];
void discrete(){
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
void baoli(int l,int r,int id){
    for(int i=l;i<=r;i++){
        int p=a[i];
        while(c[p])c[p++]=0;
        c[p]=1;vis[p]=true;
    }
    int res=0;
    for(int i=l;i<=r;i++){
        int p=a[i];
        while(vis[p])   res+=c[p],c[p]=vis[p]=0,p++;
    }
    ans[id]=res;
}
inline void add(int x){g[id[x]]++;if(id[pr[x]]^id[x])f[id[x]]=min(nx[x],R[id[x]]+1)-L[id[x]];}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        int p=a[i];
        while(nw[p])    nw[p++]=0;
        nw[p]=1;b[++m]=p;
    }
    discrete();
    for(int i=1;i<=q;i++)   Q[i]={read(),read(),i};
    sort(Q+1,Q+q+1,[&](ques x,ques y){return bid(x.l)==bid(y.l)?x.r<y.r:x.l<y.l;});
    for(int i=1;i<=q;i++){
        int ir=i,bl=Q[i].l,br=Q[i].l;while(ir<=q&&bid(Q[ir].l)==bid(Q[i].l))gmn(bl,Q[ir].l),gmx(br,Q[ir].l),ir++;
        set<int> s;
        for(int j=br;j>=bl;j--){
            int p=a[j];
            while(c[p])c[p++]=0;
            c[p]=1;s.ep(p);
        }
        for(int j:s)    c[j]=0;
        mems(b,0);
        s.ep(m+1);
        blo=0;int lst=1;
        for(int j:s){
            if(lst<j)   L[++blo]=lst,R[blo]=j-1,f[blo]=g[blo]=0;
            for(int k=lst;k<j;k++)id[k]=blo;
            lst=j;
        }
        ls.init();
        for(int i=1;i<=m;i++)   ls.ins(i,i-1);
        int r=br;
        for(int _=i;_<ir;_++){
            int ql=Q[_].l,qr=Q[_].r,qid=Q[_].id;
            if(qr<=br){baoli(ql,qr,qid);continue;}
            while(r<qr){
                r++;
                int x=a[r];
                if(!b[x]){ls.era(x);add(x);b[x]=1;}
                else{
                    int p=x;
                    while(b[p]) b[p++]=0;
                    b[p]=1;
                    if(L[id[x]]+f[id[x]]-1>=x)  f[id[x]]=x-L[id[x]];
                    ls.ins(x,pr[p]);ls.era(p);
                    g[id[x]]--;
                    for(int k=x+1;k<=p;k++){
                        if(k^p) g[id[k]]--;
                        ls.ins(k,k-1);
                        if(id[k]^id[x]) f[id[k]]=0;
                    }
                    ls.era(p);add(p);
                }
            }
            for(int j=br;j>=ql;j--){
                int p=a[j];
                while(c[p])c[p++]=0;
                c[p]=1;vis[p]=true;
            }
            int tag=0,res=0;
            for(int j=1;j<=blo;j++){
                int A=c[L[j]];
                if(b[L[j]]){
                    if(!A&&!tag)    res+=g[j];
                    else if(A+tag==1){
                        if(f[j]==R[j]-L[j]+1)   tag=1;
                        else    res+=g[j]-f[j]+1,tag=0;
                    }
                    else{
                        if(f[j]==R[j]-L[j]+1)   res++,tag=1;
                        else    res+=g[j]-f[j]+2,tag=0;
                    }
                }
                else{
                    if(A+tag<=1)    res+=g[j]+A+tag,tag=0;
                    else{
                        if(nx[L[j]]>R[j])   tag=1;
                        else    res+=g[j]-(nx[L[j]]-L[j]-1)+1,tag=0;
                    }
                }
            }
            ans[qid]=res;
            for(int j=br;j>=ql;j--){int p=a[j];while(vis[p])c[p]=vis[p]=0,p++;}
        }
        i=ir-1;
    }
    for(int i=1;i<=q;i++)   print(ans[i],'\n');Flush();
}