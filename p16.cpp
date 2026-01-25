#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <format>

class Solution 
{
    const std::vector<std::pair<int, int>> directions = 
    {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

public:
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) 
    {
        int R = mat.size();
        int C = mat[0].size();
        
        if (R == 0) return {};

        int MAX_DIST = R * C; 

        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<int>> dist(R, std::vector<int>(C, MAX_DIST)); 

        for (int i = 0; i < R; ++i) 
        {
            for (int j = 0; j < C; ++j) 
            {
                if (mat[i][j] == 0) 
                {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }
        bfs(q, dist, R, C);
        return dist;
    }

private:
    void bfs(std::queue<std::pair<int, int>>& q, std::vector<std::vector<int>>& dist, int R, int C) 
    {
        while (!q.empty()) 
        {
            std::pair<int, int> current = q.front();
            q.pop();

            int r = current.first;
            int c = current.second;
            
            for (const auto& dir : directions) 
            {
                int nr = r + dir.first;
                int nc = c + dir.second;

                if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
                    continue;
                }

                if (dist[r][c] + 1 >= dist[nr][nc]) {
                    continue;
                }

                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
};

int main()
{
    Solution sol;

    auto printMatrix = [](const std::vector<std::vector<int>>& matrix)
    {
        for (const auto& row : matrix)
        {
            std::cout << "[ ";
            for (int val : row)
            {
                std::cout << val << " ";
            }
            std::cout << "]\n";
        }
    };

    // Test Case 1
    std::vector<std::vector<int>> mat1 = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    std::cout << "Test Case 1:\n";
    printMatrix(sol.updateMatrix(mat1));
    // Expected: [[0,0,0],[0,1,0],[0,0,0]]

    // Test Case 2
    std::vector<std::vector<int>> mat2 = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    std::cout << "\nTest Case 2:\n";
    printMatrix(sol.updateMatrix(mat2));
    // Expected: [[0,0,0],[0,1,0],[1,2,1]]
}