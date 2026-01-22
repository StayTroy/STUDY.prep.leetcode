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

class Solution 
{
public:
    vector<vector<int>> generateMatrix(int n) 
    {
        if(n == 0)
        {
            return {};
        }

        int rows = n;
        int cols = n;

        vector<vector<int>> result(rows, vector<int>(cols, 0));

        vector<pair<int, int>> directions = 
        {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}
        };

        queue<State> q;
        int start = 1;
        result[0][0] = start;
        q.push({0,0,0});

        while(!q.empty())
        {
            int r = q.front().r;
            int c = q.front().c;
            int dir = q.front().direction;

            q.pop();

            for(int i = 0; i < 4; ++i)
            {
                int newdir = (dir + i) % 4;
                int newr = r+directions[newdir].first;
                int newc = c+directions[newdir].second;

                if (newr < 0 || newr >= rows || newc < 0 || newc >= cols)
                {
                    continue; 
                }
                if (result[newr][newc] != 0)
                {
                    continue; 
                } 

                q.push({newr, newc, newdir});
                result[newr][newc] = ++start;
                break;
                 // move one position at a time
            }
        }
        return result;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: n = 3
    int n1 = 3;
    auto res1 = sol.generateMatrix(n1);
    cout << format("Test Case 1 (n = {}):\n", n1);
    for (const auto& row : res1)
    {
        for (int val : row)
        {
            cout << format("{:2} ", val);
        }
        cout << "\n";
    }
    cout << "\n";

    // Test Case 2: n = 1
    int n2 = 1;
    auto res2 = sol.generateMatrix(n2);
    cout << format("Test Case 2 (n = {}):\n", n2);
    for (const auto& row : res2)
    {
        for (int val : row)
        {
            cout << format("{:2} ", val);
        }
        cout << "\n";
    }
}