#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <format>
#include <string>

using namespace std;

class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        int running_max = 0;
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                int max = 0;
                if(grid[i][j] != 0 && !visited[i][j])
                {
                    dfs(grid, visited, i, j, max);
                    running_max = std::max(running_max, max);
                }
            }
        }
        return running_max;
    }

private:
    int dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int r, int c, int& max)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        
        visited[r][c] = true;
        max+=grid[r][c];

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for(const auto& dir: directions)
        {
            int newr = r+dir.first;
            int newc = c+dir.second;

            if(newr<0||newr>=rows||newc<0||newc>=cols){continue; }
            if(grid[newr][newc] == 0){continue; }
            if(visited[newr][newc]){continue; }

            dfs(grid, visited, newr, newc, max);
        }
        return max;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> grid1 = 
    {
        {0, 2, 1, 0},
        {4, 0, 0, 3},
        {1, 0, 0, 4},
        {0, 3, 2, 0}
    };

    cout << "Test Case 1:" << endl;
    cout << format("Result: {}", sol.findMaxFish(grid1)) << endl; // 7

    vector<vector<int>> grid2 = 
    {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1}
    };

    cout << "\nTest Case 2:" << endl;
    cout << format("Result: {}", sol.findMaxFish(grid2)) << endl; // 1
}