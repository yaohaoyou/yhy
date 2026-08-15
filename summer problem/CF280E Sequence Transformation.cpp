#include<bits/stdc++.h>
#define db long double
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
const int maxn=6010;
int n,m,l,r;
int a[maxn];
db p[maxn],ans[maxn];
struct point{db x,y;point(db _x=0,db _y=0){x=_x;y=_y;}};
vector<point> v[2];
int main(){
    scanf("%d%d%d%d",&n,&m,&l,&r);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    v[1].eb(1,2*(1-a[1]));v[1].eb(m,2*(m-a[1]));
    // for(auto [j,k]:v[1])    printf("(%.2f,%.2f) ",j,k);puts("");
    for(int i=2;i<=n;i++){
        v[i&1].clear();
        if(v[(i-1)&1][0].y>=0){
            p[i]=v[(i-1)&1][0].x;
            if(v[i&1].empty()||p[i]+l!=v[i&1].back().x)v[i&1].eb(p[i]+l,0);
            if(v[i&1].empty()||p[i]+r!=v[i&1].back().x)v[i&1].eb(p[i]+r,0);
            for(int j=0;j<v[(i-1)&1].size();j++)    v[i&1].eb(v[(i-1)&1][j].x+r,v[(i-1)&1][j].y);
        }
        else if(v[(i-1)&1].back().y<=0){
            for(int j=0;j<v[(i-1)&1].size();j++)    v[i&1].eb(v[(i-1)&1][j].x+l,v[(i-1)&1][j].y);
            p[i]=v[(i-1)&1].back().x;
            if(v[i&1].empty()||p[i]+l!=v[i&1].back().x)v[i&1].eb(p[i]+l,0);
            if(v[i&1].empty()||p[i]+r!=v[i&1].back().x)v[i&1].eb(p[i]+r,0);
        }
        else{
            int q=-1;
            for(int j=0;j+1<v[(i-1)&1].size();j++)
                if(v[(i-1)&1][j].y<=0&&v[(i-1)&1][j+1].y>=0){
                    db x0=v[(i-1)&1][j].x,y0=v[(i-1)&1][j].y,x1=v[(i-1)&1][j+1].x,y1=v[(i-1)&1][j+1].y;
                    p[i]=(x0*y1-x1*y0)/(y1-y0);q=j;
                    break;
                }
            assert(~q);
            for(int j=0;j<=q;j++)    v[i&1].eb(v[(i-1)&1][j].x+l,v[(i-1)&1][j].y);
            if(v[i&1].empty()||p[i]+l!=v[i&1].back().x)v[i&1].eb(p[i]+l,0);
            if(v[i&1].empty()||p[i]+r!=v[i&1].back().x)v[i&1].eb(p[i]+r,0);
            for(int j=q+1;j<v[(i-1)&1].size();j++)  v[i&1].eb(v[(i-1)&1][j].x+r,v[(i-1)&1][j].y);
        }
        // printf("p[%d] = %.3f\n",i,p[i]);
        for(auto &x:v[i&1])   x.y+=2*(x.x-a[i]);
        // for(auto [j,k]:v[i&1])    printf("(%.2f,%.2f) ",j,k);puts("");
    }
    db L=1+l*(n-1),R=m;
    int q=-1;
    if(v[n&1][0].y>=0)    ans[n]=L;
    else if(v[n&1].back().y<=0)   ans[n]=R;
    else{
        for(int j=0;j+1<v[n&1].size();j++)
            if(v[n&1][j].y<=0&&v[n&1][j+1].y>=0){
                db x0=v[n&1][j].x,y0=v[n&1][j].y,x1=v[n&1][j+1].x,y1=v[n&1][j+1].y;
                ans[n]=(x0*y1-x1*y0)/(y1-y0);q=j;
            }
        if(ans[n]<L)  ans[n]=L;
        else if(ans[n]>R) ans[n]=R;
    }
    // printf("%.6lf ",p[n]);
    for(int i=n-1;i;i--){
        db x=ans[i+1];
        if(x>=p[i+1]+r)   x-=r;
        else if(x>=p[i+1]+l)  x=p[i+1];
        else    x-=l;
        ans[i]=x;
    }
    db out=0;
    for(int i=1;i<=n;i++)   printf("%.10LF ",ans[i]),out+=(ans[i]-a[i])*(ans[i]-a[i]);puts("");
    printf("%.10LF\n",out);
}