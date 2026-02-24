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
int ans=2e9;
int h,w,s;
void solve(){
    for(int l=1,R;l<=s;l=R+1){
        R=min(s,s/(s/l));
        if(l>h)   continue;
        int r=min(R,w);
        int c1=max(0,h/r-1);
        while(c1&&(h+c1)/(c1+1)<r) c1--;
        while((h+c1)/(c1+1)>r) c1++;
        // printf("[%d,%d] %d : %d\n",l,r,s/l,c1);
        if((!~c1)||(h+c1)/(c1+1)>r) continue;
        int c2=s/r;
        c2=max(0,w/c2-1);
        while(c2&&(w+c2)/(c2+1)<s/r)    c2--;
        while((w+c2)/(c2+1)>s/r)    c2++;
        // printf("%d %d %d %d %d\n",l,r,c1,h/(c1+1),c2);
        if(c2==-1) continue;
        // printf("test %d %d\n",c1,c2);
        if(1ll*(h+c1)/(c1+1)*((w+c2)/(c2+1))<=s)ans=min(ans,c1+c2);
    }
}
void matt(){
    int a,b,c;scanf("%d%d%d",&a,&b,&c);
    if(c>=1ll*a*b)   return puts("0"),void();
    ans=2e9;
    h=a;w=b;s=c;
    solve();
    h=b;w=a;s=c;
    solve();
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}