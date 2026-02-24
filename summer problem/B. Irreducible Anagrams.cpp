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
using namespace std;T
const int maxn=1e5+10;
int n;
int buc[maxn][30];
char s[maxn];
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++){
        memc(buc[i],buc[i-1]);
        buc[i][s[i]-'a']++;
    }
    int q;scanf("%d",&q);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        if((l==r)||(s[l]^s[r])){puts("Yes");continue;}
        int res=0;
        for(int i=0;i<26;i++)
            if(buc[r][i]^buc[l-1][i])   res++;
        puts(res<=2?"No":"Yes");
    }
}