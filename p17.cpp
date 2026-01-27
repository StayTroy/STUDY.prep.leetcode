#include <vector>
#include <queue>
#include <iostream>
#include <format>

using namespace std;

class Solution 
{
    vector<vector<int>> h;
    int rows;
    int cols;
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) 
    {
        h = heights;
        rows = h.size();
        cols = h[0].size();
        vector<vector<int>> result;

        queue<pair<int, int>> pacificbfs, atlanticbfs;

        for (int i = 0; i < rows; i++) 
        {
            pacificbfs.push({i, 0});
            atlanticbfs.push({i, cols - 1});
        }

        for (int j = 1; j < cols; j++) 
        {
            pacificbfs.push({0, j});
        }
        
        for (int j = 0; j < cols - 1; j++) 
        {
            atlanticbfs.push({rows - 1, j});
        }

        vector<vector<bool>> pacific = bfs(pacificbfs);
        vector<vector<bool>> atlantic = bfs(atlanticbfs);

        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                if (pacific[i][j] && atlantic[i][j])
                {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }

private:
    vector<vector<bool>> bfs(queue<pair<int, int>>& q) 
    {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        vector<pair<int,int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!q.empty()) 
        {
            int i = q.front().first;
            int j = q.front().second;
            visited[i][j] = true;
            q.pop();

            for (auto& d : directions) 
            {
                int newRow = i + d.first;
                int newCol = j + d.second;

                if (newRow < 0 || newCol < 0 || newRow >= rows || newCol >= cols)
                    continue;
                if (visited[newRow][newCol])
                    continue;
                if (h[newRow][newCol] < h[i][j])
                    continue;

                visited[newRow][newCol] = true;
                q.push({newRow, newCol});
            }
        }
        return visited;
    }
};


int main()
{
    Solution sol;
    vector<vector<int>> heights = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}
    };

    auto result = sol.pacificAtlantic(heights);

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << format("[{},{}]", result[i][0], result[i][1]);
        if (i < result.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "]" << endl;
}
