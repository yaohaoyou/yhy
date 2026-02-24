#pragma GCC optimize(2,3,"Ofast","inline")
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define if(sth) if(__builtin_expect(sth,1))
#define while(sth) while(__builtin_expect(sth,1))
using namespace std;
const int maxn=2010,dir[4][2]={{-1,1},{1,1},{1,-1},{-1,-1}};
int n;
char ss[maxn][maxn];
#define no exit(puts("NONE")&0)
#define mul exit(puts("MULTIPLE")&0)
inline bool check(int x,int y){return x>0&&x<=n&&y>0&&y<=n;}
int ans[maxn][maxn];
int S[maxn],F[maxn];
bool multag;
namespace IO{
    static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf,cc[20];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<1000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    #define flush fwrite(obuf,p3-obuf,1,stdout)
    inline int read(){
        int x=0; int f=1; char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
        while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
}
using namespace IO;
inline void work(int &x,int &y,int &flag,int t,bool &s,int d){
    #pragma unroll(4)
    while(check(x,y)){
        if(ss[x][y]^46){
            if(!(~flag))    F[t]=flag=(ss[x][y]=='S')^s;
            if(flag^((ss[x][y]=='S')^s))   no;
            if(flag^(ss[x][y]=='S'))   S[t]=1;
        }
        if(~flag)   ans[x][y]=flag^s;
        x+=dir[d][0];y+=dir[d][1];s^=1;
    }
    x-=dir[d][0];y-=dir[d][1];s^=1;
}
void solve(int t){
    int flag=F[t],x,y;
    bool s=0;
    x=t;y=1;
    work(x,y,flag,t,s,0);
    y++;
    
    work(x,y,flag,t,s,1);
    x++;

    work(x,y,flag,t,s,2);
    y--;

    work(x,y,flag,t,s,3);
    x--;
    if(!(~flag))    multag=true;
    F[t]=flag;
}
void print(){
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%c",ans[i][j]==-1?46:ans[i][j]==1?'*':'#');
}
int main(){
    n=read();
    if(n&1) no;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)ss[i][j]=getchar();
        ss[i][0]=getchar();
    }
    memset(S,0,sizeof(S));
    memset(F,-1,sizeof(F));
    for(int i=1;i<=n;i+=2){
        memset(ans,-1,sizeof(ans));
        solve(i);
    }
    if(multag)  mul;
    puts("UNIQUE");
    memset(ans,-1,sizeof(ans));
    for(int i=1;i<=n;i+=2)  solve(i);
    for(int i=1;i<=n;i++,putchar('\n'))
        for(int j=1;j<=n;j++)   putchar(ans[i][j]?'S':'G');
    flush;
}