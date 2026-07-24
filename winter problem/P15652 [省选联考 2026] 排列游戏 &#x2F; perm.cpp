#include "perm.h"
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
const int maxn=3e4+10;
vector<int> ans;
int lim[maxn];
set<int> st;
void init(int c, int t) {return;}
std::vector<int> perm(int n) {
	st.clear();for(int i=0;i<n;i++)st.insert(i);
	ans.resize(n);
	for(int &i:ans)	i=-1;
	int now=-1,cnt=0;
    ans[0]=0;
	for(int i=n-1;i;i--){
		int x=query(0,i-1);cnt++;
		if(now^x)	ans[i]=now=x,st.erase(x);
		else lim[i]=x;
		if(!x){ans[0]=-1;break;}
	}
	now=-1;
	for(int i=0;i+1<n;i++){
		if(!ans[i])	break;
		int x=query(i+1,n-1);cnt++;
		if(now^x)	ans[i]=now=x,st.erase(x);
		else lim[i]=x;
	}
	for(int i=0;i<ans.size();i++)if(!~ans[i]){
		ans[i]=*st.upper_bound(lim[i]);
		st.erase(ans[i]);
	}
	return ans;
}