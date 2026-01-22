#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <format>

using namespace std;

class Solution 
{
public:
    bool isValidSudoku(vector<vector<char>>& board) 
    {
        int N = 9;

        vector<vector<int>> rows_seen(N, vector<int>(10, 0));
        vector<vector<int>> cols_seen(N, vector<int>(10, 0));
        vector<vector<int>> boxes_seen(N, vector<int>(10, 0));

        vector<vector<bool>> visited(N, vector<bool>(N, false));
        
        vector<pair<int, int>> directions = 
        {
            {0, 1},  {0, -1}, 
            {1, 0},  {-1, 0}  
        };

        queue<pair<int, int>> q;

        visited[0][0] = true;
        q.push({0, 0});

        while(!q.empty())
        {
            int r = q.front().first;
            int c = q.front().second;

            q.pop();

            if (!checkAndMark(r, c, board, rows_seen, cols_seen, boxes_seen)) 
            {
                return false;
            }

            for(const auto& dir : directions)
            {
                int newr = r + dir.first;
                int newc = c + dir.second;

                if(newr < 0 || newr >= N || newc < 0 || newc >= N)
                {
                    continue;
                }
                if(visited[newr][newc])
                {
                    continue;
                }

                visited[newr][newc] = true;
                q.push({newr, newc});
            }
        }

        return true;
    }

private:
    bool checkAndMark(int r, int c, vector<vector<char>>& board, 
                        vector<vector<int>>& rows, 
                        vector<vector<int>>& cols, 
                        vector<vector<int>>& boxes) 
    {
        if (board[r][c] == '.') return true;

        int num = board[r][c] - '0';
        int boxIndex = (r / 3) * 3 + (c / 3);

        if (rows[r][num] || cols[c][num] || boxes[boxIndex][num]) 
        {
            return false;
        }

        rows[r][num] = 1;
        cols[c][num] = 1;
        boxes[boxIndex][num] = 1;

        return true;
    }
};

int main()
{
    Solution sol;

    vector<vector<char>> board1 = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    cout << format("Test Case 1 (Valid): {}\n", sol.isValidSudoku(board1) ? "Pass" : "Fail");

    vector<vector<char>> board2 = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    cout << format("Test Case 2 (Invalid - duplicate 8 in first col): {}\n", sol.isValidSudoku(board2) ? "Pass" : "Fail");
}
