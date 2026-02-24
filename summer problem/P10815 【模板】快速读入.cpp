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
const int IN=3e7,OUT=2e7;
char __i[IN],*__I=__i;
inline int read(){
	int x=0,f=0;char c=*__I++;
	for(;c<'0'||c>'9';c=*__I++)f|=c==0x2d;
	for(;c>='0'&&c<='9';c=*__I++)x=(x<<3)+(x<<1)+(c^0x30);
	return f?-x:x;
}
int ___[10];char __o[OUT],*__O=__o;
inline void write(int x){
	int l=-1;do{___[++l]=x%10;x/=10;}while(x);
	while(~l)*__O++=___[l--]|0x30;*__O++=0xa;
}
int n;ll ans;
int main(){
    fread(__i,1,IN,stdin);
    n=read();n=read();
    // for(int i=1;i<=n;i++){
    	// int x=read();
    	// ans+=x;
    	// printf("%d\n",x);
	// }
	printf("%d\n",n);
}