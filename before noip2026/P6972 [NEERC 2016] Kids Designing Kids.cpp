#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define eb emplace_back
#define ep emplace
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
using namespace std;
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
bool mem1;
namespace OIMATT{
const int maxn=1010;
int h[3],w[3];
pii mv[3];
char s[3][maxn][maxn],t[maxn][maxn];
void rb(int o){
    int x=0,y=0;
    for(int i=1;i<=h[o];i++){
        bool fl=true;
        for(int j=1;j<=w[o];j++)if(s[o][i][j]=='*'){fl=false;break;}
        if(fl)  x=i;
        else    break;
    }
    for(int i=1;i<=w[o];i++){
        bool fl=true;
        for(int j=1;j<=h[o];j++)if(s[o][j][i]=='*'){fl=false;break;}
        if(fl)  y=i;
        else    break;
    }
    for(int i=x+1;i<=h[o];i++)for(int j=y+1;j<=w[o];j++)t[i-x][j-y]=s[o][i][j];
    memc(s[o],t);h[o]-=x;w[o]-=y;
    mv[o]=pii(x,y);
    // x=h[o]+1;y=w[o]+1;
    // for(int i=h[o];i;i--){
    //     bool fl=true;
    //     for(int j=1;j<=w[o];j++)if(s[o][i][j]=='*'){fl=false;break;}
    //     if(fl)  x=i;
    //     else    break;
    // }
    // for(int i=w[o];i;i--){
    //     bool fl=true;
    //     for(int j=1;j<=h[o];j++)if(s[o][j][i]=='*'){fl=false;break;}
    //     if(fl)  y=i;
    //     else    break;
    // }
    // h[o]=x-1;w[o]=y-1;
}
int dx,dy;
bool check(int bx,int by,int x,int y,int z){
    int top = min(0, by), left = min(0, bx);
    int rows = max(h[x], by + h[y]) - top;
    int cols = max(w[x], bx + w[y]) - left;
    vector<vector<unsigned char>> canvas(rows, vector<unsigned char>(cols));
    for(int t:{x,y}){
        for (int r = 0; r < h[t]; ++r)
            for (int c = 0; c < w[t]; ++c)
                canvas[r + (t==y ? by : 0) - top][c + (t==y ? bx : 0) - left] ^= s[t][r+1][c+1] == '*';
    }
    int count = 0;
    for (const auto& row : canvas)for (unsigned char cell : row) count += cell;
    std::vector<std::pair<int, int>> target;
    for (int r = 0; r < h[z]; ++r) for (int c = 0; c < w[z]; ++c)
        if (s[z][r+1][c+1] == '*') target.eb(r, c);
    if (count != int(target.size())) return false;
    if (!count) return true;
    pii p=pii(-1,-1);for(int i=0;i<rows;i++){for(int j=0;j<cols;j++)if(canvas[i][j]){p=pii(i,j);break;}if(~p.fi)break;}
    dx=p.fi-target[0].fi,dy=p.se-target[0].se;
    // printf("# %d %d %d %d %d\n(%d,%d) (%d,%d)\n",bx,by,x,y,z,p.fi,p.se,target[0].fi,target[0].se);
    bool same = true;
    for (const auto& cell : target) {
        int r = cell.fi + dx, c = cell.se + dy;
        if (r < 0 || r >= rows || c < 0 || c >= cols || !canvas[r][c]) {
            same = false;
            break;
        }
    }
    return same;
}
bool chk(bool o){
    int mx=mv[0].se-mv[1].se,my=mv[0].fi-mv[1].fi;
    if(o)   mx=-mx,my=-my;
    if(check(0,0,0,1,2)){
        printf("YES\n%d %d\n",mx,my);
        return true;
    }
    if(check(0,0,0,2,1)){
        if(o)   dx=-dx,dy=-dy;
        printf("YES\n%d %d\n",dy+mx,dx+my);
        return true;
    }
    int x=find(s[0][1]+1,s[0][1]+w[0]+1,'*')-s[0][1],y=find(s[1][1]+1,s[1][1]+w[1]+1,'*')-s[1][1];
    // printf("%d %d\n",x,y);
    if(check(x-y,0,0,1,2)){
        dx=x-y;dy=0;
        if(o)   dx=-dx;
        printf("YES\n%d %d\n",dx+mx,dy+my);
        return true;
    }
    for(int i=1;i<=h[0];i++)if(s[0][i][1]=='*'){x=i;break;}
    for(int i=1;i<=h[1];i++)if(s[1][i][1]=='*'){y=i;break;}
    // printf("%d %d\n",x,y);
    if(check(0,x-y,0,1,2)){
        dx=0;dy=x-y;
        if(o)   dy=-dy;
        printf("YES\n%d %d\n",dx+mx,dy+my);
        return true;
    }
    x=find(s[1][1]+1,s[1][1]+w[1]+1,'*')-s[1][1],y=find(s[2][1]+1,s[2][1]+w[2]+1,'*')-s[2][1];
    // printf("+ %d %d\n",x,y);
    if(check(y-x,0,2,1,0)){
        // printf("%d %d\n",dx,dy);
        dx=-dx;dy=-dy;
        swap(dx,dy);dx+=y-x;
        if(o)   dx=-dx,dy=-dy;
        printf("YES\n%d %d\n",dx+mx,dy+my);
        return true;
    }
    for(int i=1;i<=h[1];i++)if(s[1][i][1]=='*'){x=i;break;}
    for(int i=1;i<=h[2];i++)if(s[2][i][1]=='*'){y=i;break;}
    // printf("%d %d\n",x,y);
    if(check(0,y-x,2,1,0)){
        dx=-dx;dy=-dy;
        swap(dx,dy);dy+=y-x;
        if(o)   dx=-dx,dy=-dy;
        printf("YES\n%d %d\n",dx+mx,dy+my);
        return true;
    }
    return false;
}
void matt(int _c){
    for(int o=0;o<3;o++){scanf("%d%d",&h[o],&w[o]);for(int i=1;i<=h[o];i++)scanf("%s",s[o][i]+1);rb(o);}
    if(chk(0))   return;
    swap(h[0],h[1]);swap(w[0],w[1]);swap(s[0],s[1]);swap(mv[0],mv[1]);
    // for(int o=0;o<3;o++){for(int i=1;i<=h[o];i++,puts(""))for(int j=1;j<=w[o];j++)printf("%c",s[o][i][j]);puts("");}
    if(!chk(1))  return puts("NO"),void();
}
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=1;for(int i=1;i<=T;i++)OIMATT::matt(i);
}