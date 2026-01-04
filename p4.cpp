#include <iostream>
#include <vector>
#include <string>
#include <format>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        int count = 0;
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(grid[i][j] != '0' && !visited[i][j])
                {
                    dfs(grid, visited, i , j);
                    count++;
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int r, int c)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<pair<int, int>> directions = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };

        visited[r][c] = true;

        for(const auto& dir: directions)
        {
            int newr = r+dir.first;
            int newc = c+dir.second;

            if(newr<0||newr>=rows||newc<0||newc>=cols){continue; }

            if(grid[newr][newc] == '0' || visited[newr][newc]){continue; }

            dfs(grid, visited, newr, newc);
        }
    }
};

int main()
{
    Solution sol;

    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };

    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };

    cout << std::format("Test Case 1: {}\n", sol.numIslands(grid1));
    cout << std::format("Test Case 2: {}\n", sol.numIslands(grid2));

}
