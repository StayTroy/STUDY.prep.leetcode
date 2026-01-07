#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) 
    {
        int rows = grid1.size();
        int cols = grid1[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        int count = 0;
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(grid2[i][j] != 0 && !visited[i][j])
                {   
                    bool sub = true;
                    dfs(grid1, grid2, i, j, sub, visited);
                    if(sub)
                    {
                        count++;
                    }
                }
            }
        }
        return count;
    }
private:
    void dfs(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int r, int c, bool& s, vector<vector<bool>>& visited)
    {
        int rows = grid2.size();
        int cols = grid2[0].size();

        vector<pair<int,int>> directions = 
        {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
        };

        if(grid1[r][c] == 0)
        {
            s = false;
        }

        visited[r][c] = true;

        for(const auto& dir: directions)
        {
            int newr = r+dir.first;
            int newc = c+dir.second;

            if(newr<0||newr>=rows||newc<0||newc>=cols){continue; }
            
            if(grid2[newr][newc] == 0 || visited[newr][newc]){continue; }

            dfs(grid1, grid2, newr, newc, s, visited);
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