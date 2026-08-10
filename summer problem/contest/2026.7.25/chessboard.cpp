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
const int maxn=2000+10,B=2047,dir[4][2]={{-1,-1},{-1,0},{0,-1},{0,0}};
bool out;
int n,m,cnt;
queue<pii> q;
bool st[maxn][maxn];
char a[maxn][maxn];
inline ll H(ll x,int y){return (x<<11)|y;}
inline int get(char c){return c=='?'?-1:c=='1';}
inline int chk(int i,int j){
    int x=get(a[i][j]),y=get(a[i][j+1]),z=get(a[i+1][j]),w=get(a[i+1][j+1]);
    if((x==-1)+(y==-1)+(z==-1)+(w==-1)>1)   return 0;
    if(x==-1)   swap(x,w),swap(y,z);
    if(x==1){x^=1;if(~y)y^=1;if(~z)z^=1;if(~w)w^=1;}
    if(y==0||z==0||w==1)    return 0;
    int c=(x==0)+(y==1)+(z==1)+(w==0);
    if(c==4)    return -1;
    if(c==3)    return 1;
    return 0;
}
void solve(int i,int j){
    if(i==n||j==m)  return;
    int c=chk(i,j);
    if(c==-1){
        puts("No");out=true;
        return;
    }
    if(c==1){
        cnt++;
        if(a[i][j]=='?'){
            a[i][j]=a[i+1][j+1]^1;
            q.ep(i,j);st[i][j]=true;
        }
        if(a[i][j+1]=='?'){
            a[i][j+1]=a[i+1][j]^1;
            q.ep(i,j+1);st[i][j+1]=true;
        }
        if(a[i+1][j]=='?'){
            a[i+1][j]=a[i][j+1]^1;
            q.ep(i+1,j);st[i+1][j]=true;
        }
        if(a[i+1][j+1]=='?'){
            a[i+1][j+1]=a[i][j]^1;
            q.ep(i+1,j+1);st[i+1][j+1]=true;
        }
    }
}
void matt(int _cases){
    scanf("%d%d",&n,&m);out=false;queue<pii>().swap(q);cnt=0;mems(st,0);
    for(int i=1;i<=n;i++){
        scanf("%s",a[i]+1);
        for(int j=1;j<=m;j++){
            if(a[i][j]!='?')st[i][j]=true,cnt++;
            // if(a[i][j]=='B')a[i][j]='0';
            // if(a[i][j]=='W')a[i][j]='1';
        }
    }
    // if(_cases==2122){
    //     debug("%d %d\n",n,m);
    //     for(int i=1;i<=n;i++,debug("\n"))for(int j=1;j<=m;j++)debug("%c",a[i][j]);
    // }
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++){solve(i,j);if(out)return;}
    int x=1,y=1;
    while(true){
        while(!q.empty()){
            auto [x,y]=q.front();q.pop();
            for(int d=0;d<4;d++){
                int i=x+dir[d][0],j=y+dir[d][1];
                if(!i||!j)  continue;
                solve(i,j);
            }
        }
        if(cnt==n*m)    break;
        while(x<=n){
            while(y<=m&&st[x][y])y++;
            if(y<=m){
                if(!out)puts("Yes");
                cnt++;out=true;
                st[x][y]=true;
                a[x][y]='1';q.ep(x,y);
                break;
            }
            else    x++,y=1;
        }
    }
    if(!out)    puts("Yes");
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++){
        // if(a[i][j]=='0')a[i][j]='B';
        // else a[i][j]='W';
        putchar(a[i][j]);
    }
}
int main(){int T=1;for(int i=1;i<=T;i++)matt(i);}