#include <bits/stdc++.h>
using namespace std;
long long n;
bool ac[10];
int main(){
  cin>>n;
  for(int i = 1; i <= n; i++) {
    ac[i]=(((n - i + 1) % 2) == 0);
  }
  cout << ac[n] << " " << (((n-n+1)%2)==0) << "\n";
  return 0;
}