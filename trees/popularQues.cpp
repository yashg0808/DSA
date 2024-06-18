#include <bits/stdc++.h>
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

//https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/
class kthSmallestInBST //used INORDER TRAVERSAL
{
public:
    void solve(TreeNode *root, int &cnt, int &ans, int k)
    {
        if (root == NULL)
            return;
        // left, root, right
        solve(root->left, cnt, ans, k);
        cnt++;
        if (cnt == k)
        {
            ans = root->val;
            return;
        }
        solve(root->right, cnt, ans, k);
    }
    int kthSmallest(TreeNode *root, int k)
    {

        int cnt = 0;
        int ans;
        solve(root, cnt, ans, k);
        return ans;
    }
};

//https://leetcode.com/problems/sum-root-to-leaf-numbers/description/
class SumRootToLeafNumbers
{
public:
    int sum(TreeNode* root, int val){
        if(root==NULL) return 0;
        val=val*10 + root->val;
        if(root->left==NULL && root->right==NULL){
            return val;                                                         // 1->2->3 = 123 (root to leafpath)
        }                                                                       // 1->2->4 = 124 (another root to leafpath)
        return sum(root->left,val)+sum(root->right, val);                       // return 123+124=247
    }
    int sumNumbers(TreeNode* root) {
        return sum(root,0);
    }
};

//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
class LowestCommonAncestorOfBinaryTree //used POSTORDER TRAVERSAL
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL || root==p || root==q) return root;
        TreeNode* left=lowestCommonAncestor(root->left, p, q);
        TreeNode* right=lowestCommonAncestor(root->right, p, q);
        if(left && right) return root;
        return left?left:right;
    }
};
