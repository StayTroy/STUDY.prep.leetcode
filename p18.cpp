#include <vector>
#include <queue>
#include <iostream>
#include <format>
#include <limits>
#include <algorithm>

using namespace std;

class Solution 
{

    const std::vector<std::pair<int, int>> directions = 
    {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

public:
    int maxDistance(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        int infinity = numeric_limits<int>::max();
        vector<vector<int>> distance(rows, vector<int>(cols, infinity));

        queue<pair<int, int>> q;

        int max_distance = -1;
        for(int i = 0; i<rows; ++i)
        {
            for(int j = 0; j<cols; ++j)
            {
                if(grid[i][j] == 1)
                {
                    q.push({i,j});
                    distance[i][j] = 0;
                }
            }
        }

        bfs(q, distance, max_distance, rows, cols);
        return max_distance;
    }

private:
    void bfs(queue<pair<int, int>>& q, vector<vector<int>>& distance, int& max_distance, int R, int C)
    {
        while(!q.empty())
        {
            int r = q.front().first;
            int c = q.front().second;

            q.pop();

            for(const auto& dir: directions)
            {
                int nr = r+dir.first;
                int nc = c+dir.second;

                if(nr<0||nr>=R||nc<0||nc>=C){continue; }

                if(distance[r][c] + 1 >= distance[nr][nc]){continue; }

                distance[nr][nc] = distance[r][c] + 1;
                max_distance = max(max_distance, distance[nr][nc]);
                q.push({nr,nc});
            }
        }
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> grid1 = {
        {1, 0, 1},
        {0, 0, 0},
        {1, 0, 1}
    };
    cout << format("Test Case 1: {}\n", sol.maxDistance(grid1));

    vector<vector<int>> grid2 = {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    cout << format("Test Case 2: {}\n", sol.maxDistance(grid2));
}
