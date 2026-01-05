#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                // process boundary cells
                if(i == 0 || i == rows-1 || j == 0 || j == cols-1)
                {
                    if(grid[i][j] == 1 && !visited[i][j])
                    {
                        dfs(grid, visited, i, j);
                    }
                }
            }
        }
        
        int count = 0;
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(grid[i][j] == 1 && !visited[i][j])
                {
                    count++;
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int r, int c)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        visited[r][c] = true;
        
        vector<pair<int,int>> directions = {
            {1, 0}, 
            {-1, 0}, 
            {0, 1}, 
            {0, -1}
        };
        
        for(auto dir: directions)
        {
            int new_r = r + dir.first;
            int new_c = c + dir.second;
            
            if(new_r < 0 || new_r >= rows || new_c < 0 || new_c >= cols){continue; }
            
            if(grid[new_r][new_c] == 0 || visited[new_r][new_c]) {continue; }
            
            dfs(grid, visited, new_r, new_c);
        }
    }
};

int main()
{
    Solution s;

    vector<vector<int>> grid1 = {
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    cout << "Test Case 1: " << s.numEnclaves(grid1) << " (Expected: 3)" << endl;

    vector<vector<int>> grid2 = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };
    cout << "Test Case 2: " << s.numEnclaves(grid2) << " (Expected: 0)" << endl;
}