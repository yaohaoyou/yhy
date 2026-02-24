//  P3369 【模板】普通平衡树
#include<bits/stdc++.h>
using namespace std;
const int Size=1e5+10;
struct Treap{
	int l,r;  // 左右儿子的下标 
	int val,dat;  // 节点关键码、权值 
	int cnt,siz;  // 副本数、字数大小 
}a[Size];
int tot=0,root,n,inf=0x7fffffff;
int New(int val){
	a[++tot].val=val;
	a[tot].dat=rand();
	a[tot].cnt=a[tot].siz=1; 
	return tot;
}
void Update(int p){
	a[p].siz=a[a[p].l].siz+a[a[p].r].siz+a[p].cnt;
}
void Build(){
	New(-inf),New(inf);
	root=1;
	a[1].r=2;
	Update(root);
}
int GetRankByVal(int p,int val){
	if(p==0)	return 0;
	if(val==a[p].val)	return a[a[p].l].siz+1;
	if(val<a[p].val)	return GetRankByVal(a[p].l,val);
	return GetRankByVal(a[p].r,val)+a[a[p].l].siz+a[p].cnt;
}
int GetValByRank(int p,int rank){
	if(p==0)	return inf;
	if(a[a[p].l].siz>=rank)	return GetValByRank(a[p].l,rank);
	if(a[a[p].l].siz+a[p].cnt>=rank)	return a[p].val;
	return GetValByRank(a[p].r,rank-a[a[p].l].siz-a[p].cnt);
}
void zig(int &p){
	int q=a[p].l;
	a[p].l=a[q].r;
	a[q].r=p;
	p=q;
	Update(a[p].r);
	Update(p);
}
void zag(int &p){
	int q=a[p].r;
	a[p].r=a[q].l;
	a[q].l=p;
	p=q;
	Update(a[p].l);
	Update(p);
}
void Insert(int &p,int val){
	if(p==0){
		p=New(val);
		return;
	}
	if(val==a[p].val){
		a[p].cnt++;
		Update(p);
		return;
	}
	if(val<a[p].val){
		Insert(a[p].l,val);
		if(a[p].dat<a[a[p].l].dat)	zig(p);
	}
	else{
		Insert(a[p].r,val);
		if(a[p].dat<a[a[p].r].dat)	zag(p);
	}
	Update(p);
}
int GetPre(int val){
	int ans=1;
	int p=root;
	while(p){
		if(val==a[p].val){
			if(a[p].l>0){
				p=a[p].l;
				while(a[p].r>0)	p=a[p].r;
				ans=p;
			}
			break;
		}
		if(a[p].val<val&&a[p].val>a[ans].val)	ans=p;
		p=val<a[p].val?a[p].l:a[p].r;
	}
	return a[ans].val;
}
int GetNext(int val){
	int ans=2;
	int p=root;
	while(p){
		if(val==a[p].val){
			if(a[p].r>0){
				p=a[p].r;
				while(a[p].l>0)	p=a[p].l;
				ans=p;
			}
			break;
		}
		if(a[p].val>val&&a[p].val<a[ans].val)	ans=p;
		p=val<a[p].val?a[p].l:a[p].r;
	}
	return a[ans].val;
}
void Remove(int &p,int val){
	if(p==0)	return;
	if(val==a[p].val){
		if(a[p].cnt>1){
			a[p].cnt--;
			Update(p);
			return;
		}
		if(a[p].l||a[p].r){
			if(a[p].r==0||a[a[p].l].dat>a[a[p].r].dat){
				zig(p);
				Remove(a[p].r,val);
			}
			else{
				zag(p);
				Remove(a[p].l,val);
			}
			Update(p);
		}
		else	p=0;
		return;
	}
	val<a[p].val? Remove(a[p].l,val):Remove(a[p].r,val);
	Update(p);
}
int main(){
//	srand(time(0));
	Build();
	cin>>n;
	while(n--){
		int opt,x;
		scanf("%d%d",&opt,&x);
		switch(opt){
			case 1:
				Insert(root,x);
				break;
			case 2:
				Remove(root,x);
				break;
			case 3:
				printf("%d\n",GetRankByVal(root,x)-1);
				break;
			case 4:
				printf("%d\n",GetValByRank(root,x+1));
				break;
			case 5:
				printf("%d\n",GetPre(x));
				break;
			case 6:
				printf("%d\n",GetNext(x));
				break;
		}
	}
}