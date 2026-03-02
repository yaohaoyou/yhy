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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=5e4+10;
int n;
struct ope{
    int x,y,z[2][2];
    int*operator[](int x){return z[x];}
}Q[maxn];
bool visx[maxn],visy[maxn];
void divide(int l,int r,vector<int> vx,vector<int> vy,vector<vector<ll>> &mat,vector<vector<ll>> &tag){
    if(l==r){
        for(int i:{0,1})for(int j:{0,1})printf("%lld\n",mat[i][j]);
        for(int i:{0,1})for(int j:{0,1})tag[i][j]+=Q[l][i][j];
        return;
    }
    vector<int> belx(vx.size()-1),bely(vy.size()-1);
    int mid=(l+r)>>1;
    for(auto [L,R]:{pii(l,mid),pii(mid+1,r)}){
        vector<int> x({1}),y({1});
        for(int i=L;i<=R;i++)   visx[Q[i].x]=visy[Q[i].y]=true;
        visx[1]=visy[1]=false;
        for(int i:vx)if(visx[i])x.eb(i);
        for(int i:vy)if(visy[i])y.eb(i);
        if(!visx[n+1])x.eb(n+1);
        if(!visy[n+1])y.eb(n+1);
        for(int i=L;i<=R;i++)   visx[Q[i].x]=visy[Q[i].y]=false;
        {
            int j=0;
            for(int i=0;i+1<vx.size();i++){
                while(j+1<x.size()&&x[j+1]<vx[i+1])   j++;
                assert(j+1<x.size());
                belx[i]=j;
            }
        }
        {
            int j=0;
            for(int i=0;i+1<vy.size();i++){
                while(j+1<y.size()&&y[j+1]<vy[i+1])   j++;
                assert(j+1<y.size());
                bely[i]=j;
            }
        }
        vector<vector<ll>> M(x.size()-1,vector<ll>(y.size()-1,0)),T(x.size()-1,vector<ll>(y.size()-1,0));
        for(int i=0;i+1<vx.size();i++)
            for(int j=0;j+1<vy.size();j++)  gmx(M[belx[i]][bely[j]],mat[i][j]+tag[i][j]);
        divide(L,R,x,y,M,T);
        for(int i=0;i+1<vx.size();i++)
            for(int j=0;j+1<vy.size();j++)  tag[i][j]+=T[belx[i]][bely[j]];
    }
}
int main(){
    freopen("matrix.in","r",stdin);freopen("matrix.out","w",stdout);
    scanf("%d",&n);
    vector<int> vx,vy;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&Q[i].x,&Q[i].y);
        vx.eb(Q[i].x);vy.eb(Q[i].y);
        for(int j:{0,1})for(int k:{0,1})scanf("%d",&Q[i][j][k]);
    }
    vx.eb(n+1);vy.eb(n+1);vx.eb(1);vy.eb(1);
    sort(vx.begin(),vx.end());vx.erase(unique(vx.begin(),vx.end()),vx.end());
    sort(vy.begin(),vy.end());vy.erase(unique(vy.begin(),vy.end()),vy.end());
    vector<vector<ll>> M(vx.size()-1,vector<ll>(vy.size()-1)),T(vx.size()-1,vector<ll>(vy.size()-1));
    divide(1,n,vx,vy,M,T);
}