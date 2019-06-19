#include <iostream>
#include <queue>
#include <cstring>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *father;
    TreeNode() {
        left = NULL;
        right = NULL;
        father = NULL;
    }
};

class Tree {
private:
    TreeNode* root = NULL;

public:
    void add(TreeNode* node) {
        if (root == NULL) {
            root = node;
        }
        else {
            TreeNode* aux = root;
            while (aux != NULL) {
                if (aux->val > node->val) {
                    if (aux->right != NULL) {
                        aux = aux->right;
                    }
                    else {
                        node -> father = aux;
                        aux->right = node;
                        break;
                    }
                }
                else {
                    if (aux->left != NULL) {
                        aux = aux->left;
                    }
                    else {
                        node -> father = aux;
                        aux->left = node;
                        break;
                    }
                }
            }
        }
    }

    TreeNode* getRoot() {
        return root;
    }



    int getBestElem(TreeNode* root){
      if(root == NULL)return 0;
      queue<TreeNode*> q;
      unordered_map<int, int> freq;
      int max_freq = 0;
      int max_val = -1;
      q.push(root);
      while(!q.empty()){
        TreeNode *u = q.front();
        q.pop();
        freq[u->val]++;
        if(freq[u->val] > max_freq){
          max_freq = freq[u->val];
          max_val = u->val;
        }
        if(u->left != NULL)
          q.push(u->left);
        if(u->right != NULL)
          q.push(u->right);
      }
      return max_val;
    }
};

int main()
{
    int n, x;
    cin >> n;
    Tree t;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        TreeNode* aux = new TreeNode;
        aux -> val = x;
        t.add(aux);
    }
    cout << t.getBestElem(t.getRoot());
    return 0;
}
