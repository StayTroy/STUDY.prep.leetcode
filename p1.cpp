#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) 
    {
        vector<vector<bool>> visited(board.size());

        for(int i = 0; i < board.size(); ++i)
        {
            visited[i] = vector<bool>(board[i].size(), false);
        }

        for(int i = 0; i < board.size(); i++) 
        {
            for(int j = 0; j < board[i].size(); j++) 
            {
                if (board[i][j] == word[0]) 
                {
                    if (dfs(board, visited, word, i, j, 0)) 
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, 
             string& word, int r, int c, int index) 
             {
        
        if (index == word.size() - 1) 
        {
            return true;
        }
        
        visited[r][c] = true; // Mark current node
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (const auto& dir : directions) 
        {
            int newR = r + dir.first;
            int newC = c + dir.second;
            
            if (newR < 0 || newR >= board.size() || newC < 0 || newC >= board[0].size()) 
            {
                continue;
            }
            if (visited[newR][newC])
            {
                continue;
            }
            if (board[newR][newC] != word[index + 1])
            {
                continue;
            }
            if (dfs(board, visited, word, newR, newC, index + 1)) 
            {
                return true;
            }
        }
        visited[r][c] = false;
        return false;
    }
};

int main() 
{
    Solution s;    
    vector<vector<char>> board = 
    {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    
    string word = "ABCCED";
    cout << (s.exist(board, word) ? "true" : "false") << endl;
}

