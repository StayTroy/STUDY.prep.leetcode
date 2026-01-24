#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits>
#include <iostream>
#include <format>

using namespace std;

class Solution 
{
public:
    int minPathSum(vector<vector<int>>& grid) 
    {
        int rows = (int)grid.size();
        int cols = (int)grid[0].size();

        vector<pair<int, int>> directions = 
        {
            {1, 0},  
            {0, 1}   
        };
        
        int infinity = numeric_limits<int>::max();
        vector<vector<int>> min_sum(rows, vector<int>(cols, infinity));

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        int initial_sum = grid[0][0];
        min_sum[0][0] = initial_sum;
        pq.push({initial_sum, 0, 0});

        while (!pq.empty()) 
        {
            vector<int> current = pq.top();
            pq.pop();
            
            int current_total_sum = current[0];
            int r = current[1];
            int c = current[2];
            
            for (const auto& dir : directions) 
            {
                int newr = r + dir.first;
                int newc = c + dir.second;

                if (newr < 0 || newr >= rows || newc < 0 || newc >= cols) 
                {
                    continue; 
                }

                int new_total_sum = current_total_sum + grid[newr][newc];

                if (new_total_sum >= min_sum[newr][newc]) 
                {
                    continue; 
                }

                min_sum[newr][newc] = new_total_sum;
                pq.push({new_total_sum, newr, newc});
            }
        }
        int totalsum = min_sum[rows - 1][cols - 1];
        return totalsum;
    }
};

int main()
{
    Solution sol;

    // Test Case 1
    vector<vector<int>> grid1 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << format("Test Case 1: {}\n", sol.minPathSum(grid1)); // Expected: 7

    // Test Case 2
    vector<vector<int>> grid2 = {{1, 2, 3}, {4, 5, 6}};
    cout << format("Test Case 2: {}\n", sol.minPathSum(grid2)); // Expected: 12

    // Test Case 3
    vector<vector<int>> grid3 = {{5}};
    cout << format("Test Case 3: {}\n", sol.minPathSum(grid3)); // Expected: 5
}
