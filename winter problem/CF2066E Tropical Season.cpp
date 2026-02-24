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
const int maxn=2e5+10,maxv=1e6+10;
int n,q;
int a[maxn];
int Log[maxv],cnt[maxv];
ll sum[25];
int mn[25];
set<int> db;
multiset<int> st[25];
priority_queue<int,vector<int>,greater<int>> c1[25],c2[25];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline void ins(int x){
    cnt[x]++;
    if(cnt[x]==2)   db.ep(x);
    int lg=Log[x];
    sum[lg]+=x;
    auto it=st[lg].ep(x);
    int nx=0,pr=0;
    if(it!=st[lg].begin()){
        it--;
        c1[lg].ep(x-(pr=*it));
        it++;
    }
    if((++it)!=st[lg].end())    c1[lg].ep((nx=*it)-x);
    if(pr&&nx)  c2[lg].ep(nx-pr);
}
inline void era(int x){
    cnt[x]--;
    if(cnt[x]==1)   db.erase(x);
    int lg=Log[x];
    sum[lg]-=x;
    auto it=st[lg].erase(st[lg].find(x));
    int nx=0,pr=0;
    if(it!=st[lg].end())    nx=*it,c2[lg].ep(*it-x);
    if(it!=st[lg].begin())  pr=*(--it),c2[lg].ep(x-*it);
    if(nx&&pr)  c1[lg].ep(nx-pr);
}
inline int cmn(int x){while(!c1[x].empty()&&!c2[x].empty()&&c1[x].top()==c2[x].top())c1[x].pop(),c2[x].pop();return c1[x].top();}
inline bool check(){
    if(n==1)    return true;
    if(db.empty())  return false;
    int x=*prev(db.end());ll s=0;
    // printf("mn : ");
    for(int i=0;i<20;i++){
        mn[i]=1e9;
        if(c1[i].size()^c2[i].size())   mn[i]=cmn(i);
        if(!st[i].empty()&&!st[i+1].empty())    gmn(mn[i],*st[i+1].begin()-*prev(st[i].end()));
    }
    for(int i=18;~i;i--)    gmn(mn[i],mn[i+1]);
    int i=0,cc=0;
    for(;i<=Log[x];i++)  s+=sum[i],cc+=st[i].size();
    while(i<20&&cc<n-1){
        if(st[i].empty()) i++;
        else if(s>=*st[i].begin())  s+=sum[i],cc+=st[i].size(),i++;
        else if(mn[i]<=s)   s+=sum[i],cc+=st[i].size(),i++;
        else return false;
    }
    return true;
}
int main(){
    for(int i=2;i<=1000000;i++) Log[i]=Log[i/2]+1;
    n=read();q=read();
    for(int i=1;i<=n;i++)   ins(read());
    pus(check()?"Yes":"No");putc('\n');
    for(int i=1;i<=q;i++){
        char op=getc();int x;
        while(op!='-'&&op!='+') op=getc();x=read();
        if(op=='-') era(x),n--;
        else    ins(x),n++;
        pus(check()?"Yes":"No");putc('\n');
    }
    flush();
}