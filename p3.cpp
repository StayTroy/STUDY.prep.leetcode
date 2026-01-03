#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) 
    {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                bool isBorder = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1);
                if(isBorder && board[i][j] == 'O')
                {
                    dfs(board, visited, i, j);
                }
            }
        }

        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                if (board[i][j] == 'O' && !visited[i][j]) 
                {
                    board[i][j] = 'X';
                }
            }
        }
    }

private:
    void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, int r, int c)
    {
        vector<pair<int, int>> directions = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };

        stack<pair<int,int>> s;
        s.push({r,c});
        visited[r][c] = true;

        while(!s.empty())
        {
            auto r = s.top().first;
            auto c = s.top().second;
            s.pop();

            for(const auto dir: directions)
            {
                int newr = r+dir.first;
                int newc = c+dir.second;

                if(newr<0 || newr>=board.size() || newc<0 || newc>=board[r].size()) {continue; }

                if(board[newr][newc] != board[r][c]) {continue; }

                if(visited[newr][newc]) {continue; }
                
                visited[newr][newc] = true;
                s.push({newr, newc});
            }
        }
    }
};

int main()
{
    Solution sol;
    vector<vector<char>> board = 
    {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };

    auto printBoard = [](const vector<vector<char>>& b) 
    {
        for (const auto& row : b) 
        {
            for (char cell : row) 
            {
                cout << cell << " ";
            }
            cout << endl;
        }
    };

    cout << "Board before solve:" << endl;
    printBoard(board);

    sol.solve(board);

    cout << "\nBoard after solve:" << endl;
    printBoard(board);

    return 0;
}
