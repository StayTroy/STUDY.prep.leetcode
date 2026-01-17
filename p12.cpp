#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <format>

using namespace std;

struct State 
{
    int r;
    int c;
    int direction; 
};

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) 
    {
        if (matrix.empty() || matrix[0].empty()) 
        {
            return {};
        }

        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<int> result;

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        vector<pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}
        };
        
        queue<State> q;
        State current_state = {0, 0, 0};

        visited[current_state.r][current_state.c] = true;
        q.push(current_state);
        result.push_back(matrix[current_state.r][current_state.c]);

        while (!q.empty()) {
            
            int r = q.front().r;
            int c = q.front().c;
            int dir_index = q.front().direction;

            q.pop(); 

            for (int i = 0; i < 4; i++) {
                int currDir = (dir_index + i) % 4;
                int newr = r + directions[currDir].first;
                int newc = c + directions[currDir].second;
                
                if (newr < 0 || newr >= rows || newc < 0 || newc >= cols)
                    continue;
                
                if (visited[newr][newc])
                    continue;

                visited[newr][newc] = true;
                q.push({newr, newc, currDir});
                result.push_back(matrix[newr][newc]);
                break; // move to one direction per iteration
            }
        }
        return result;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    auto result1 = sol.spiralOrder(matrix1);
    cout << "Test Case 1:" << endl;
    for (int x : result1)
    {
        cout << format("{} ", x);
    }
    cout << endl;

    vector<vector<int>> matrix2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    auto result2 = sol.spiralOrder(matrix2);
    cout << "\nTest Case 2:" << endl;
    for (int x : result2)
    {
        cout << format("{} ", x);
    }
    cout << endl;
}