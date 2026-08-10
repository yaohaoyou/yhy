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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
int main() {
    freopen("sign.in","r",stdin);freopen("sign.out","w",stdout);
    unordered_map<string, vector<string>> table;
    
    table["Aries"] = {"Aries", "1st House", "Mars", "Pluto", "Mars", "Sun", "Venus", "Saturn"};
    table["Taurus"] = {"Taurus", "2nd House", "Venus", "Earth", "Venus", "Moon", "Pluto, Mars", "Uranus"};
    table["Gemini"] = {"Gemini", "3rd House", "Mercury", "Mercury", "Mercury", "none", "Jupiter, Neptune", "none"};
    table["Cancer"] = {"Cancer", "4th House", "Moon", "Moon", "Moon", "Jupiter", "Saturn", "Mars"};
    table["Leo"] = {"Leo", "5th House", "Sun", "Sun", "Sun", "Pluto", "Uranus", "Neptune, Mercury"};
    table["Virgo"] = {"Virgo", "6th House", "Mercury", "Mercury", "Mercury", "Mercury", "Neptune", "Venus"};
    table["Libra"] = {"Libra", "7th House", "Venus", "Venus", "Venus", "Saturn", "Mars", "Sun"};
    table["Scorpio"] = {"Scorpio", "8th House", "Mars", "Pluto", "Pluto", "Uranus", "Venus", "Moon"};
    table["Sagittarius"] = {"Sagittarius", "9th House", "Jupiter", "Jupiter", "Jupiter, Neptune", "None", "Mercury", "Mercury"};
    table["Capricorn"] = {"Capricorn", "10th House", "Saturn", "Saturn", "Saturn", "Mars", "Moon", "Jupiter"};
    table["Aquarius"] = {"Aquarius", "11th House", "Saturn", "Uranus", "Uranus", "Neptune, Mercury", "Sun", "Pluto"};
    table["Pisces"] = {"Pisces", "12th House", "Jupiter", "Neptune", "Neptune", "Venus", "Mercury", "Mercury"};
    unordered_map<string, int> colIndex;
    colIndex["S"] = 0;
    colIndex["H"] = 1;
    colIndex["RP"] = 2;
    colIndex["RB"] = 3;
    colIndex["Do"] = 4;
    colIndex["E"] = 5;
    colIndex["De"] = 6;
    colIndex["F"] = 7;
    
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        string sign, col;
        cin >> sign >> col;
        cout << table[sign][colIndex[col]] << endl;
    }
}