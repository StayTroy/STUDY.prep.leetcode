#include <vector>
#include <utility>
#include <iostream>
#include <format>

using namespace std;

class Solution 
{
private:
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

public:
    int countIslands(vector<vector<int>>& grid, int k) 
    {
        int rows = grid.size();
        int cols = grid[0].size();
        
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        int count = 0;
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(grid[i][j] != 0 && !visited[i][j])
                {
                    long sum = 0;
                    dfs(grid, visited, i, j, sum, rows, cols);
                    if(sum%k==0 && sum!=0)
                    {
                        count++;
                    }
                }
            }
        }
        return count;
    }

private:
    void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int r, int c, long& sum, int rsize, int csize)
    {
        visited[r][c] = true;
        sum += grid[r][c];

        for(const auto& dir: directions)
        {
            int newr = r+dir.first;
            int newc = c+dir.second;

            if(newr<0||newr>=rsize||newc<0||newc>=csize){continue; }

            if(grid[newr][newc] == 0) {continue; }

            if(visited[newr][newc]) {continue; }

            dfs(grid, visited, newr, newc, sum, rsize, csize);
        }
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> grid1 = {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 2, 2},
        {0, 0, 2, 2}
    };
    int k1 = 4;
    cout << "Test Case 1:" << endl;
    cout << format("Result: {}", sol.countIslands(grid1, k1)) << endl; // Expected: 2 

    vector<vector<int>> grid2 = {
        {1, 2, 0, 3},
        {0, 0, 0, 0},
        {4, 0, 5, 6}
    };
    int k2 = 3;
    cout << "\nTest Case 2:" << endl;
    cout << format("Result: {}", sol.countIslands(grid2, k2)) << endl; // Expected: 2 
}