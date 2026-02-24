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
const int maxn=60;
int n;
int col[maxn];
inline void slv6(){col[1]=col[2]=col[5]=1;col[3]=col[4]=2;col[6]=3;}
inline void slv7(){col[1]=col[2]=col[7]=1;col[3]=col[6]=2;col[4]=col[5]=3;}
inline void slv9(){col[5]=col[9]=1;col[6]=col[8]=2;col[1]=col[2]=col[3]=col[4]=col[7]=3;}
inline void slv10(){col[7]=col[10]=1;col[8]=col[9]=2;col[1]=col[2]=col[3]=col[4]=col[5]=col[6]=3;}
int main(){
    scanf("%d",&n);
    if(n<=4||n%3==2)    exit(puts("No")&0);
    int x=n;while(x>10) col[x]=col[x-5]=1,col[x-1]=col[x-4]=2,col[x-2]=col[x-3]=3,x-=6;
    if(x==6)slv6();if(x==7)slv7();if(x==9)slv9();if(x==10)slv10();
    puts("Yes");
    for(int i=n;i;i--,putchar('\n'))
        for(int j=1;j<i;j++)   putchar(col[i]==1?'R':col[i]==2?'B':'W');
}