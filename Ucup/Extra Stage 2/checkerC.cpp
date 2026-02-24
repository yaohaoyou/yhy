#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <iostream>
using namespace std;

const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool checkConnected(const vector<vector<int>>& grid, int color, int n, int m) {
    // Find first cell with given color
    int startX = -1, startY = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == color) {
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1) break;
    }
    
    if (startX == -1) return true; // No cells of this color
    
    // BFS to find all connected cells of this color
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    int count = 0;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        count++;
        
        for (int d = 0; d < 8; d++) {
            int nx = x + dx8[d];
            int ny = y + dy8[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
                !visited[nx][ny] && grid[nx][ny] == color) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    
    // Check if we visited all cells of this color
    int total = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == color) total++;
        }
    }
    
    return count == total;
}

bool checkNoThreeInRow(const vector<vector<int>>& grid, int n, int m) {
    // Check horizontal
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 2 < m; j++) {
            if (grid[i][j] == grid[i][j+1] && grid[i][j] == grid[i][j+2]) {
                return false;
            }
        }
    }
    
    // Check vertical
    for (int j = 0; j < m; j++) {
        for (int i = 0; i + 2 < n; i++) {
            if (grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j]) {
                return false;
            }
        }
    }
    
    return true;
}

bool checkCounts(const vector<vector<int>>& grid, int n, int m) {
    vector<int> count(3, 0);
    int total = n * m;
    int expected = total / 3;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] < 0 || grid[i][j] > 2) {
                return false; // Invalid number
            }
            count[grid[i][j]]++;
        }
    }
    
    return count[0] == expected && count[1] == expected && count[2] == expected;
}

int main(int argc, char* argv[]) {
    // Usage: checker <input> <output> <answer>
    // For this problem, we only need output file
    registerTestlibCmd(argc, argv);
    
    // Read input
    int T = inf.readInt();
    for (int testCase = 1; testCase <= T; testCase++) {
        int n = inf.readInt();
        int m = inf.readInt();
        
        // Check if output says "No"
        string firstLine = ouf.readToken();ouf.readString();
        string ansLine = ans.readToken();
        if(firstLine != ansLine)quitf(_wa, "Test case %d: Yes/No???", testCase);
        if (firstLine == "No") {
            // Contestant says no solution, we trust them
            // (In actual contest, you might want to verify this)
            continue;
        }
        
        // Read the matrix
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            string s=ouf.readString();
            for (int j = 0; j < m; j++) {
                grid[i][j] = s[j]-'0';
            }
        }
        
        // Verify all conditions
        if (!checkCounts(grid, n, m)) {
            quitf(_wa, "Test case %d: Numbers 0,1,2 don't appear exactly nm/3 times", testCase);
        }
        
        if (!checkNoThreeInRow(grid, n, m)) {
            quitf(_wa, "Test case %d: Three identical numbers appear consecutively", testCase);
        }
        
        for (int color = 0; color < 3; color++) {
            if (!checkConnected(grid, color, n, m)) {
                quitf(_wa, "Test case %d: Color %d is not 8-connected", testCase, color);
            }
        }
    }
    
    quitf(_ok, "All test cases passed");
    return 0;
}