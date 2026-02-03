#include <iostream>
#include <climits>
#include <format>
#include <vector>

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
    bool isValid;
    
public:
    bool isValidBST(TreeNode* root)
    {
        isValid = true;
        traverse(root, LLONG_MIN, LLONG_MAX);
        return isValid;
    }

private:
    void traverse(TreeNode* node, long long minBound, long long maxBound)
    {
        if (node == nullptr) 
        {
            return;
        }

        processItem(node, minBound, maxBound);
        if(isValid)
        {
            traverse(node->left, minBound, node->val);
            traverse(node->right, node->val, maxBound);
        }
    }
    
    void processItem(TreeNode* node, long long minBound, long long maxBound)
    {
        if (node->val <= minBound || node->val >= maxBound)
        {
            isValid = false;
        }
    }
};

void deleteTree(TreeNode* root)
{
    if (root == nullptr)
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete(root);
}

int main()
{
    Solution sol;

    // Test Case 1: Valid BST

    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);
    std::cout << std::format("Test Case 1 (Valid BST): {}\n", sol.isValidBST(root1) ? "Pass" : "Fail");
    deleteTree(root1);

    // Test Case 2: Invalid BST

    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4, new TreeNode(3), new TreeNode(6));
    std::cout << std::format("Test Case 2 (Invalid BST): {}\n", sol.isValidBST(root2) ? "Pass" : "Fail");
    deleteTree(root2);

    // Test Case 3: Invalid BST (duplicate value)
    
    TreeNode* root3 = new TreeNode(2);
    root3->left = new TreeNode(2);
    root3->right = new TreeNode(2);
    std::cout << std::format("Test Case 3 (Invalid BST - duplicates): {}\n", sol.isValidBST(root3) ? "Pass" : "Fail");
    deleteTree(root3);
}