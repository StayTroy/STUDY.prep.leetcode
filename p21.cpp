#include <iostream>
#include <vector>
#include <algorithm>
#include <format>

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution 
{
private:
    TreeNode* prevNode = nullptr;
    TreeNode* firstNode = nullptr;
    TreeNode* secondNode = nullptr;

public:
    void recoverTree(TreeNode* root) 
    {
        prevNode = nullptr;
        firstNode = nullptr;
        secondNode = nullptr;

        inOrderTraversal(root);

        swap(firstNode->val, secondNode->val);
    }

private:
    void inOrderTraversal(TreeNode* root)
    {
        if(root == nullptr){return; }

        inOrderTraversal(root->left);
        processItem(root);
        inOrderTraversal(root->right);
    }

    void processItem(TreeNode* currentNode)
    {
        if(prevNode != nullptr && prevNode->val > currentNode->val)
        {
            if(firstNode == nullptr)
            {
                firstNode = prevNode;
            }
            
            secondNode = currentNode;
        }

        prevNode = currentNode;
    }
};

void deleteTree(TreeNode* root)
{
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printInOrder(TreeNode* root, std::vector<int>& result)
{
    if (root == nullptr) return;
    printInOrder(root->left, result);
    result.push_back(root->val);
    printInOrder(root->right, result);
}

bool checkSorted(TreeNode* root)
{
    std::vector<int> result;
    printInOrder(root, result);
    for (size_t i = 1; i < result.size(); ++i)
    {
        if (result[i] < result[i-1]) return false;
    }
    return true;
}

int main()
{
    Solution sol;

    // Test Case 1: Root = [1,3,null,null,2]
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(3);
    root1->left->right = new TreeNode(2);

    std::cout << "Test Case 1 Before: ";
    std::vector<int> v1;
    printInOrder(root1, v1);
    for(int x : v1) std::cout << x << " ";
    std::cout << "\n";

    sol.recoverTree(root1);

    std::cout << "Test Case 1 After: ";
    v1.clear();
    printInOrder(root1, v1);
    for(int x : v1) std::cout << x << " ";
    std::cout << "\n";
    
    std::cout << std::format("Test Case 1 Result: {}\n", checkSorted(root1) ? "Pass" : "Fail");
    deleteTree(root1);

    // Test Case 2: Root = [3,1,4,null,null,2]
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(2);

    std::cout << "Test Case 2 Before: ";
    std::vector<int> v2;
    printInOrder(root2, v2);
    for(int x : v2) std::cout << x << " ";
    std::cout << "\n";

    sol.recoverTree(root2);

    std::cout << "Test Case 2 After: ";
    v2.clear();
    printInOrder(root2, v2);
    for(int x : v2) std::cout << x << " ";
    std::cout << "\n";

    std::cout << std::format("Test Case 2 Result: {}\n", checkSorted(root2) ? "Pass" : "Fail");
}