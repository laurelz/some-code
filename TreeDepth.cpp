// leetcode Balanced Binary Tree
// Given a binary tree, determine if it is height-balanced.
// For this problem, a height-balanced binary tree is defined as
// a binary tree in which the depth of the two subtrees of every
// node never differ by more than 1.

#include<iostream>
using namespace std;

// 递归计算节点深度
int TreeDepth(TreeNode* root)
{
    if (root == NULL)
        return 0;
    return max(TreeDepth(root->left), TreeDepth(root->right)) + 1;
}

// 简单递归的方法，存在重复计算
bool isBalanced_m2(TreeNode* root)
{
    if (root == NULL)
        return true;
    int left = TreeDepth(root->left);
    int right = TreeDepth(root->right);
    
    if ((left - right) < -1 && (left-right) > 1)
        return false;
    return isBalanced_m2(root->left) && isBalanced_m2(root->right);
}

// 后序判断的方法，递归实现
// 在当前节点的左右字节点均为平衡节点时,才对当前节点进行判断
bool isBalanced(TreeNode* root, int *pdepth) {
  // 叶节点的深度为0
  if (root == NULL) 
  {
    *pdepth = 0;
    return true;
  }
  int left;
  int right;
  
  if (isBalanced(root->left, &left) && isBalanced(root->right, &right)) 
  {
    // 左右字节点均为平衡节点时，判断二者之差是否<=1
    // 将pdepth指针指向的数据进行更新
    int diff = left - right;
    if (diff >= -1 && diff <= 1) 
    {
      *pdepth = max(left,right) + 1;
      return true;
    }
  }
  return false;
}
bool isBalanced_m1(TreeNode* root) {
  int tmp;
  return isBalanced(root, &tmp);
}
