#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <format>
#include <string>

using namespace std;

class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) 
    {
        if (grid[0][0] != 0) return false;

        int i = 0;
        int j = 0;
        int count = 0;

        return dfs(grid, i, j, count);
    }

private:
    bool dfs(vector<vector<int>>& grid, int r, int c, int& count)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        int area = rows*cols;

        vector<pair<int,int>> directions = 
        {
            {-2, -1},
            {-1, -2},
            {-2, 1},
            {-1, 2},
            {1, 2},
            {2, 1},
            {2, -1},
            {1, -2}
        };

        if(count == area - 1)
        {
            return true;
        }

        count++;

        for(const auto& dir: directions)
        {
            int newr = r+dir.first;
            int newc = c+dir.second;

            if(newr<0||newr>=rows||newc<0||newc>=cols){continue; }
            if(grid[newr][newc] != count) {continue; }
            
            return dfs(grid, newr, newc, count);
        } 
        return false;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> grid1 = 
    {
        {0, 11, 16, 5, 20},
        {17, 4, 19, 10, 15},
        {12, 1, 8, 21, 6},
        {3, 18, 23, 14, 9},
        {24, 13, 2, 7, 22}
    };

    cout << "Test Case 1 (Valid 5x5 Tour):" << endl;
    cout << format("Result: {}", sol.checkValidGrid(grid1)) << endl;

    vector<vector<int>> grid2 = 
    {
        {0, 3, 6},
        {5, 8, 1},
        {2, 7, 4}
    };

    cout << "\nTest Case 2 (Invalid 3x3 Tour):" << endl;
    cout << format("Result: {}", sol.checkValidGrid(grid2)) << endl;
}
