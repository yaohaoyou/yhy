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
const int maxn=210;
int n;
int a[maxn],b[maxn];
bool ask(int x,int y){printf("? %d %d\n",x,y);fflush(stdout);char s[5];scanf("%s",s);return s[0]=='<';}
void matt(int _cases){
    scanf("%d",&n);
    int x=(n+1)/2,y=n+1-x,z=n+2;
    for(int i=1;i<=x;i++)   a[i]=i;
    for(int i=x+1;i<=n+1;i++) b[i-x]=i;
    sort(a+1,a+x+1,[&](int x,int y){return !ask(x,y);});
    sort(b+1,b+y+1,[&](int x,int y){return !ask(x,y);});
    for(int i=1;i<n;i++,z++){
        if(ask(a[x],b[y])){
            // debug("kick %d\n",a[x]);
            for(int j=x;j;j--){
                if(!ask(a[j],z)){
                    for(int k=x;k>=j+2;k--) a[k]=a[k-1];
                    a[j+1]=z;
                    break;
                }
                else if(j==1){
                    for(int k=x;k>=2;k--)   a[k]=a[k-1];
                    a[1]=z;
                    break;
                }
            }
        }
        else{
            // debug("kick %d\n",b[y]);
            for(int j=y;j;j--){
                if(!ask(b[j],z)){
                    for(int k=y;k>=j+2;k--) b[k]=b[k-1];
                    b[j+1]=z;
                    break;
                }
                else if(j==1){
                    for(int k=y;k>=2;k--)   b[k]=b[k-1];
                    b[1]=z;
                    break;
                }
            }
        }
    }
    if(ask(a[x],b[y]))x--;else y--;
    puts("!");fflush(stdout);
    // for(int i=1;i<=x;i++)debug("%d ",a[i]);for(int i=1;i<=y;i++)debug("%d ",b[i]);debug("\n");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}