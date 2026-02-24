#include<bits/stdc++.h>
using namespace std;
vector<int> a[5];
int main(){
	srand(time(0));
	for(int i=1;i<=13;i++){
		a[rand()%3].push_back(i);
	}
	puts("cyz2010");
	for(int j:a[0])	printf("%c ",j+'A'-1);
	puts("");
	puts("misaka_sama");
	for(int j:a[1])	printf("%c ",j+'A'-1);
	puts("");
	puts("matt");
	for(int j:a[2])	printf("%c ",j+'A'-1);
	puts("");
}