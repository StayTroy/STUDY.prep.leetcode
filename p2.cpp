#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution 
{
public:
    bool isPossibleToCutPath(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        if (grid[0][0] == 0) 
        {
            return true;
        }

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        if (!dfs(grid, visited, 0, 0, rows, cols))
        {
            return true;
        }

        visited[0][0] = false;
        visited[rows - 1][cols - 1] = false;

        return !dfs(grid, visited, 0, 0, rows, cols);
    }
    
private:

    bool dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int r, int c, int& rows, int& cols)
    {
        vector<pair<int, int>> directions = 
        {
            {1, 0},
            {0, 1}
        };

        if (r == rows - 1 && c == cols - 1) 
        {
            visited[r][c] = true;
            return true;
        }

        visited[r][c] = true;

        for (const auto& dir : directions)
        {
            int newr = r + dir.first;
            int newc = c + dir.second;

            if (newr < 0 || newr >= rows || newc < 0 || newc >= cols) 
            {
                continue; 
            }
            if (grid[newr][newc] == 0 || visited[newr][newc]) 
            {
                continue; 
            }
            if (dfs(grid, visited, newr, newc, rows, cols)) 
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = 
    {
        {1, 1, 1},
        {1, 1, 0},
        {1, 1, 1}
    };

    bool result = sol.isPossibleToCutPath(grid);
    cout << (result ? "true" : "false") << endl;

}