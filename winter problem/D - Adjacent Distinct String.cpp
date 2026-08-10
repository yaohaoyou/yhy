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
const int maxn=1e6+10;
int n;
char a[maxn],ans[maxn];
int buc[30];
void matt(int _cases){
    mems(buc,0);
    scanf("%s",a+1);n=strlen(a+1);
    for(int i=1;i<=n;i++)   buc[a[i]-'a']++;
    int lst=-1;
    for(int i=1;i<=n;i++){
        int p=-1;
        for(int j=0;j<26;j++)if((j^lst)&&(buc[j]>buc[p]))p=j;
        if(p==-1)   return puts("No"),void();
        ans[i]=char(p+'a');buc[p]--;lst=p;
    }
    puts("Yes");
    for(int i=1;i<=n;i++)putchar(ans[i]);
    putchar('\n');
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}