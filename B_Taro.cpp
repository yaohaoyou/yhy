#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=110;
int n,m;
int a[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x;char y;
        cin>>x>>y;
        if(y=='M'&&!a[x]){puts("Yes");a[x]=1;}
        else    puts("No");
    }
}