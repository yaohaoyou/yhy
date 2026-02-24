#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pil pair<int,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=45,maxm=4e6+5;
int n,a[maxn],b[maxn],pw[maxn],val[maxm];pil f[maxm],g[maxm];
inline int gtw(int i,int j){return (j<=n?b[j]:n+1)-(j>i?b[j-1]:0);}
void upd(pil&a,int b,ll c){if(a.fi>b)a.fi=b,a.se=c;else if(a.fi==b)a.se+=c;}
int main()
{
	scanf("%d",&n);f[0]=pil(0,1);
	for(int i=1;i<maxm;i++)    f[i]=pil(1e9,0);
	for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)b[j]=a[j];
		sort(b+i,b+n+1);pw[i-1]=1;int p=0,l=0;
		for(int j=i;j<=n+1;j++)
		{
			pw[j]=pw[j-1]*gtw(i,j);
			if(b[j]==a[i])p=j,l=gtw(i,j)+gtw(i,j+1);
		}
		for(int j=0;j<maxm;j++)g[j]=pil(1e9,0);
		for(int j=1;j<pw[n+1]/pw[p];j++)for(int k=p;k<=n;k++)if(j%(pw[k+1]/pw[p])/(pw[k]/pw[p])){val[j]=val[j-pw[k]/pw[p]]+1;break;}
		for(int j=0;j<maxm;j++)if(f[j].se)
		{
			int a=j%pw[p-1],b=j%pw[p]/pw[p-1],c=j%pw[p+1]/pw[p],d=j/pw[p+1];
			upd(g[a+(b+c+d*l)*pw[p-1]],f[j].fi,f[j].se);
			upd(g[a+(b+c+1+d*l)*pw[p-1]],f[j].fi+val[j/pw[p]],f[j].se);
		}
		swap(f,g);
	}
	for(int i=1;i<=n;i++)printf("%d %lld\n",f[i].fi,f[i].se);
}