#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <format>

using namespace std;

class Solution {
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) 
    {
        int rows = land.size();
        int cols = land[0].size();
        vector<vector<int>> result;
        
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(land[i][j] != 0 && !visited[i][j])
                {
                    int r2 = i;
                    int c2 = j;
                    
                    dfs(land, visited, i, j, r2, c2);
                    result.push_back({i, j, r2, c2});
                }
            }
        }       
        return result;
    }

private:
    void dfs(vector<vector<int>>& land, vector<vector<bool>>& visited, int r, int c, int& r2, int& c2)
    {
        int rows = land.size();
        int cols = land[0].size();

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
   
        visited[r][c] = true;

        r2 = std::max(r, r2);
        c2 = std::max(c, c2);

        for(const auto& dir: directions)
        {
            int newr = r+dir.first;
            int newc = c+dir.second;

            if(newr<0||newr>=rows||newc<0||newc>=cols){continue; }
            
            if(land[newr][newc] == 0 || visited[newr][newc]){continue; }

            dfs(land, visited, newr, newc, r2, c2);
        }
    }
};

int main()
{
    Solution sol;

    // Test Case 1
    vector<vector<int>> land1 = 
    {
        {1, 0, 0},
        {0, 1, 1},
        {0, 1, 1}
    };
    
    cout << "Test Case 1:" << endl;
    auto result1 = sol.findFarmland(land1);
    for (const auto& rect : result1)
    {
        cout << format("[{}, {}, {}, {}]", rect[0], rect[1], rect[2], rect[3]) << endl;
    }

    // Test Case 2
    vector<vector<int>> land2 = 
    {
        {1, 1},
        {1, 1}
    };

    cout << "\nTest Case 2:" << endl;
    auto result2 = sol.findFarmland(land2);
    for (const auto& rect : result2)
    {
        cout << format("[{}, {}, {}, {}]", rect[0], rect[1], rect[2], rect[3]) << endl;
    }

    // Test Case 3
    vector<vector<int>> land3 = 
    {
        {0}
    };

    cout << "\nTest Case 3:" << endl;
    auto result3 = sol.findFarmland(land3);
    for (const auto& rect : result3)
    {
        cout << format("[{}, {}, {}, {}]", rect[0], rect[1], rect[2], rect[3]) << endl;
    }
}
