#include <vector>
#include <string>
#include <deque>
#include <unordered_map>
#include <tuple>
#include <cctype>
#include <limits>
#include <iostream>
#include <format>

using namespace std;

class Solution 
{
public:
    int minMoves(vector<string>& matrix) 
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        const int INF = rows * cols + 1;

        // build map of teleportation stones
        unordered_map<char, vector<pair<int, int>>> portals;

        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                char curr = matrix[i][j];
                if (isupper(curr))
                {
                    portals[curr].push_back({i, j});
                }
            }
        }

        deque<pair<int, int>> dq;
        
        vector<vector<int>> dist(rows, vector<int>(cols, INF));

        // track letters have been used once
        vector<bool> visited_portals(26, false);

        dq.push_front({0, 0});
        dist[0][0] = 0;

        vector<pair<int, int>> directions = 
        {
            {0, 1}, 
            {0, -1},
            {1, 0},   
            {-1, 0}  
        };

        while (!dq.empty()) 
        {
            auto [r, c] = dq.front();
            dq.pop_front();

            if (r == rows - 1 && c == cols - 1) 
            {
                return dist[r][c];
            }

            char cell_val = matrix[r][c];

            // first check
            if (isalpha(cell_val)) {
                int portalIdx = cell_val - 'A';
                
                if (!visited_portals[portalIdx]) 
                {
                    visited_portals[portalIdx] = true;
                    
                    for (auto& pos : portals[cell_val]) 
                    {
                        int nr = pos.first;
                        int nc = pos.second;
                        
                        if (dist[nr][nc] > dist[r][c]) 
                        { 
                            dist[nr][nc] = dist[r][c];
                            dq.push_front({nr, nc});
                        }
                    }
                }
            }

            // now move
            for (const auto& dir : directions) 
            {
                int nr = r + dir.first;
                int nc = c + dir.second;
                int new_dist = dist[r][c] + 1;

                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) 
                {
                    continue;
                }
                if (matrix[nr][nc] == '#') 
                {
                    continue; 
                }
                
                if (dist[nr][nc] > new_dist) 
                {
                    dist[nr][nc] = new_dist;
                    dq.push_back({nr, nc});
                }
            }
        }

        return -1; 
    }
};

int main()
{
    Solution sol;

    vector<string> matrix1 = 
    {
        "A.B",
        "###",
        "B.A"
    };
    cout << format("Test Case 1: {}\n", sol.minMoves(matrix1));

    vector<string> matrix2 = 
    {
        "A...",
        "####",
        "..A."
    };
    cout << format("Test Case 2: {}\n", sol.minMoves(matrix2));

    vector<string> matrix3 = 
    {
        "A.A",
        ".#.",
        "A.A"
    };
    cout << format("Test Case 3: {}\n", sol.minMoves(matrix3));
}
