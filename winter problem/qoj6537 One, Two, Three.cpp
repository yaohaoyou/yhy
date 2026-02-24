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
const int maxn=6e5+10;
int n;
int a[maxn],pre[4][maxn];
int b[maxn],c[maxn],d[maxn];
vector<int> v[4];
vector<pii> v1,v2;
queue<int> q1,q2;
inline int S(int x,int l,int r){return l>r?0:pre[x][r]-pre[x][l-1];}
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),v[a[i]].eb(i);
    for(int i=1;i<=n;i++){
        pre[1][i]=pre[1][i-1];pre[2][i]=pre[2][i-1];pre[3][i]=pre[3][i-1];
        pre[a[i]][i]++;
    }
    b[n+1]=c[n+1]=d[n+1]=1e9;
    for(int i=n;i;i--){
        b[i]=min(b[i+1],S(3,i+1,n)+S(1,i+1,n)+S(2,1,i));
        c[i]=min(c[i+1],S(2,1,i)+S(3,i+1,n));
        d[i]=min(d[i+1],S(2,1,i)+S(1,i+1,n));
    }
    int A=1e9,B=1e9,AB=1e9;
    for(int i=1;i<=n;i++){
        int x=S(1,1,i-1)+S(3,1,i-1)-S(2,1,i-1);
        gmn(AB,x+b[i]);
        x=S(1,1,i-1)-S(2,1,i-1);
        gmn(A,x+c[i]);
        // printf("%d : %d %d\n",i,x,c[i]);
        x=S(3,1,i-1)-S(2,1,i-1);
        gmn(B,x+d[i]);
        // printf("%d %d %d\n",AB,A,B);
    }
    gmn(A,pre[1][n]-B);
    gmn(A,pre[3][n]-B);
    gmn(AB,A+B);
    gmn(A,AB-B);
    printf("%d\n",AB);
    for(int i=0;i<A;i++)   v1.eb(v[1][i],v[3][int(v[3].size())-A+i]);
    for(int i=0;i<B;i++)   v2.eb(v[3][i],v[1][int(v[1].size())-B+i]);
    for(int i=1,j=0,k=0;i<=n;i++){
        while(j<v1.size()&&v1[j].fi==i) q1.ep(j++);
        while(k<v2.size()&&v2[k].fi==i) q2.ep(k++);
        if(a[i]==2){
            if(!q1.empty()&&!q2.empty()){
                if(v1[q1.front()].se<v2[q2.front()].se) printf("%d %d %d\n",v1[q1.front()].fi-1,i-1,v1[q1.front()].se-1),q1.pop();
                else printf("%d %d %d\n",v2[q2.front()].fi-1,i-1,v2[q2.front()].se-1),q2.pop();
            }
            else if(!q1.empty()) printf("%d %d %d\n",v1[q1.front()].fi-1,i-1,v1[q1.front()].se-1),q1.pop();
            else if(!q2.empty()) printf("%d %d %d\n",v2[q2.front()].fi-1,i-1,v2[q2.front()].se-1),q2.pop();
        }
    }
}