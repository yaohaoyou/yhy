#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include "history.h"
#define ull unsigned ll
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
void assign(int x, int y, int z);
void init(int N, int m, int A, int B);
vector<int> query(int x, int y);
// namespace Grader {
//     typedef unsigned long long u64;
// 	const int N = (1 << 20), M = 2e7 + 5;
// 	int n, m, q, ct, mx, A, B, seed, chk; u64 a[M], b[N];

// 	void quit(string s) { cout << s << '\n', exit(0); }
// 	void ok() { cout << "ok.\n", exit(0); }

// 	void assign(int x, int y, int z) {
// 		int c = (x >= 0 && y >= 0 && z >= (1 << n) && x < m && y < m && z < m);
// 		if (!c) {
// 			cout << "wa. assign(" << x << ',' << y << ',' << z << ") does not meet the constraint.\n";
// 			exit(0);
// 		}
// 		if (!chk) quit("wa. You can not use assign operation outside init().\n");
// 		a[z] = a[x] + a[y], ct ++;
// 		if (ct > A) quit("wa. Too many operations.\n");
// 	}

// 	void run() {
// 		cin >> n >> m >> q >> A >> B >> seed;
// 		mt19937_64 rnd(seed);
// 		for (int i = 0; i < m; i ++) {
// 			if (i < (1 << n)) a[i] = 1<<i;
// 			else a[i] = 0;
//             // printf("%llu ",a[i]);
// 		}
//         // puts("");
// 		chk = 1, init(n, m, A, B), chk = 0;
// 		for (int test = 1; test <= q; test ++) {
// 			int x = rnd() & ((1 << n) - 1);
// 			int y = rnd() & ((1 << n) - 1);
// 			for (int i = 0; i < (1 << n); i ++)
// 				b[i] = a[i ^ x];
// 			for (int i = 0; i < (1 << n); i ++)
// 				a[i] = b[i];
// 			vector<int> p = query(x, y);
// 			if (p.size() > B) {
// 				cout << "wa. The length of the sequence is " << p.size() << ", which is bigger than " << B << '\n';
// 				exit(0);
// 			}
// 			u64 A = 0, B = 0;
// 			for (int x : p) {
// 				if (x < 0 || x >= m) {
// 					cout << "wa. The element " << x << " in p does not meet the constraint.\n";
// 					exit(0);
// 				}
// 				A += a[x];
// 			}
// 			for (int i = 0; i <= y; i ++) B += a[i];
// 			if (A != B) {
// 				printf("wrong answer %d %llu %llu\n",y,A,B);
// 				cout << "wa. Wrong Answer on test " << test << '\n';
// 				exit(0);
// 			}
// 			mx = max(mx, (int)p.size());
// 		}
// 		ok();
// 	}
// }
// void assign(int x, int y, int z) {Grader::assign(x,y,z);}  // a[z]=a[x]+a[y]
const int maxn=2e6+10,maxp=3.7e6+10;
mt19937_64 rd(20261112);
vector<int> son;
int n,m,tot,lA,lB;
int X;
vector<int> nx[maxp];
int so[maxp][2];
ull H[maxp];
__gnu_pbds::cc_hash_table<ull,int> mp;
#define ls so[p][0]
#define rs so[p][1]
vector<tuple<int,int,int>> as;
vector<int> dfs1(int &p,int l,int r,int d,int rt){
	if(l==r)	p=l;
	else if(!p)p=++tot;
    if(!~d) return nx[rt].eb(p),mp[H[p]=rd()]=p,vector<int>();
    if(!rt)rt=p;
    int mid=(l+r)>>1;
    vector<int> vl=dfs1(ls,l,mid,d-1,rt),vr=dfs1(rs,mid+1,r,d-1,rt),res;
	as.eb(ls,rs,p);
    for(int i:vl)res.eb(i),as.eb(i,rs,++tot),res.eb(tot);
    for(int i:vr)res.eb(i),as.eb(i,ls,++tot),res.eb(tot);
    res.eb(ls);res.eb(rs);
	return res;
}
bool flg;
void dfs(int &p,int l,int r,int d){
    if(l==r)    return p=l,void();
	// as.clear();
    dfs1(p,l,r,son[d]-1,p);
	vector<tuple<int,int,int>> vec=move(as);
	int K=(r-l+1)/(1<<son[d]);
    for(int i:nx[p])    dfs(i,l,l+K-1,d-1),l+=K;
	for(auto [i,j,k]:vec){
		assign(i,j,k);
		if(i>n){
			H[k]=H[i]^H[j];
			mp[H[k]]=k;
		}
	}
}
int rt;
void init(int N, int M, int A, int B){
    X=0;m=M;lA=A;lB=B;
    tot=n=(1<<20)-1;
    if(lB==5)	son={1,2,3,5,9};
	else if(lB==6)	son={1,1,2,3,5,8};
	else if(lB==7)	son={1,1,1,2,3,4,8};
	else{
		for(int i=0;i<20;i++)son.eb(1);
	}
    dfs(rt,0,n,son.size()-1);
}
vector<int> ans;
int to;
ull bry(int p,int d,int lm,int x){
	// printf("%d %d %d\n",p,d,lm);
    if(!~lm)return to=p,0;
    bool o=(x^X)&(1<<d);
    ull res=0;
    if(x&(1<<d))    res^=H[so[p][!o]];
    res^=bry(so[p][o],d-1,lm-1,x);
    return res;
}
void Q(int p,int dep,int d,int x){
	if(!~d) return;
	// debug("%d %d %d %d %d\n",p,d,x,dep,son[d]-1);
    ull h=bry(p,dep,son[d]-1,x);
	// printf("h = %d %d %d\n",h,d,to);
	if(h){
		assert(mp.find(h)!=mp.end());
		if(mp[h]<=n)	ans.eb(mp[h]^X);
		else	ans.eb(mp[h]);//printf("eb %d\n",mp[h]);
	}
    Q(to,dep-son[d],d-1,x);
}
vector<int> query(int x, int y){
    X^=x;ans.clear();
    if(y==n)    return vector<int>{rt};
    Q(rt,19,son.size()-1,y+1);
	return ans;
}
bool mem2;
// int main() {
// 	debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
// 	Grader::run();
// 	return 0;
// }