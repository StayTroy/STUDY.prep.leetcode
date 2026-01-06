#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();
        if(rows == 0) {return false; }
        
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(!visited[i][j])
                {
                    if(dfs(grid, visited, i, j, -1, -1))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

private:

    bool dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int r, int c, int parent_r, int parent_c)
    {
        vector<pair<int, int>> directions = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };

        visited[r][c] = true;

        for(auto dir: directions)
        {
            int new_r = r + dir.first;
            int new_c = c + dir.second;

            if(new_r<0 || new_r>=grid.size() || new_c<0 || new_c>=grid[r].size()){continue; }

            if(grid[new_r][new_c] != grid[r][c]) {continue; }
            if(new_r == parent_r && new_c == parent_c) {continue; }
            
            if(!visited[new_r][new_c])
            {
                if(dfs(grid, visited, new_r, new_c, r, c)){return true; }
            }
            else{return true; }
        }
        return false;
    }
};

int main()
{
    Solution s;

    vector<vector<char>> grid1 = {
        {'a', 'a', 'a', 'a'},
        {'a', 'b', 'b', 'a'},
        {'a', 'b', 'b', 'a'},
        {'a', 'a', 'a', 'a'}
    };
    cout << "Test Case 1 (Cycle): " << (s.containsCycle(grid1) ? "True" : "False") << " (Expected: True)" << endl;

    vector<vector<char>> grid2 = {
        {'c', 'c', 'c', 'a'},
        {'c', 'd', 'c', 'c'},
        {'c', 'c', 'e', 'c'},
        {'f', 'c', 'c', 'c'}
    };
    cout << "Test Case 2 (Cycle): " << (s.containsCycle(grid2) ? "True" : "False") << " (Expected: True)" << endl;

    vector<vector<char>> grid3 = {
        {'a', 'b', 'b'},
        {'b', 'z', 'b'},
        {'b', 'b', 'a'}
    };
    cout << "Test Case 3 (No Cycle): " << (s.containsCycle(grid3) ? "True" : "False") << " (Expected: False)" << endl;

}
