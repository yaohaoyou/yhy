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
int n;
char s[20];
int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%s",s);
        for(int i=0;i<=4;i++){
            if(s[0]>='a'+i*3&&s[0]<='a'+i*3+2)  printf("%d",i+2);
        }
        if(s[0]>='p'){
            if(s[0]>='w')   printf("9");
            else if(s[0]>='t')  printf("8");
            else    printf("7");
        }
    }
}