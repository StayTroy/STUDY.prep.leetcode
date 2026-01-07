#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution 
{
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) 
    {
        int rows = grid2.size();
        int cols = grid2[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int count = 0;

        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                if (grid2[i][j] == 1 && !visited[i][j]) 
                {   
                    bool isSub = true;
                    dfs(grid1, grid2, i, j, isSub, visited);
                    if (isSub) 
                    {
                        count++;
                    }
                }
            }
        }
        return count;
    }

private:
    static constexpr int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(const vector<vector<int>>& grid1, const vector<vector<int>>& grid2, 
             int r, int c, bool& isSub, vector<vector<bool>>& visited) 
    {
        int rows = grid2.size();
        int cols = grid2[0].size();

        visited[r][c] = true;
        if (grid1[r][c] == 0) 
        {
            isSub = false; 
        }

        for (const auto& dir : dirs) 
        {
            int nr = r + dir[0];
            int nc = c + dir[1];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && 
                grid2[nr][nc] == 1 && !visited[nr][nc]) 
            {
                dfs(grid1, grid2, nr, nc, isSub, visited);
            }
        }
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> grid1_1 = 
    {
        {1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1}
    };
    vector<vector<int>> grid2_1 = 
    {
        {1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0}
    };
    cout << "Test Case 1: " << sol.countSubIslands(grid1_1, grid2_1) << " (Expected: 3)" << endl;

    vector<vector<int>> grid1_2 = 
    {
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1}
    };
    vector<vector<int>> grid2_2 = 
    {
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1}
    };
    cout << "Test Case 2: " << sol.countSubIslands(grid1_2, grid2_2) << " (Expected: 2)" << endl;
}