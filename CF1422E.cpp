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
const int maxn=2e5+10;
int n;
char s[maxn],lst,pre;
int len[maxn];
char ans[maxn][11];
struct Stack{
    char st[maxn];int len;
    inline char& operator[](int x){return st[x];}
    inline void ep(char x){st[++len]=x;}
    inline void pop(){len--;}
    inline char top(){return st[len];}
    inline int size(){return len;}
    inline bool empty(){return !len;}
    inline void clear(){len=0;}
}stk;
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    bool flag=false;
    for(int i=n;i;i--){
        if(!flag||stk.empty()||s[i]!=stk.top()){
            if(stk.empty()) lst=0;
            else if(s[i]!=stk.top())    pre=lst,lst=stk.top();
            stk.ep(s[i]),flag=true;
        }
        else{
            // if(s[i]=='j') printf("%c %c %c\n",stk.top(),s[i],lst);
            if(stk.size()==1||lst<s[i])  stk.pop(),flag=false,lst=pre;
            else{
                if(s[i]!=stk.top()) pre=lst,lst=stk.top();
                stk.ep(s[i]),flag=true;
            }
        }
        if(stk.size()<=10){
            len[i]=stk.size();for(int j=1;j<=len[i];j++)ans[i][j]=stk[len[i]-j+1];
        }
        else{
            len[i]=stk.size();
            for(int j=1;j<=5;j++)ans[i][j]=stk[len[i]-j+1];
            for(int j=6;j<=8;j++)ans[i][j]='.';
            ans[i][9]=stk[2];ans[i][10]=stk[1];
        }
    }
    // for(int i=stk.len;i;i--)printf("%c",stk[i]);puts("");
    for(int i=1;i<=n;i++){
        printf("%d ",len[i]);
        for(int j=1;j<=min(10,len[i]);j++)printf("%c",ans[i][j]);
        puts("");
    }
}