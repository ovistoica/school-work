#include <iostream>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <stack>

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
                        node->father = aux;
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



    int treeDiameter(TreeNode* root){
        unordered_map<int, bool> visited;
        TreeNode *leaf1;
        if(root->left == NULL){
          leaf1 = root;
        }else {
          TreeNode *aux = root->left;
          while(aux->left != NULL){
            aux = aux->left;
          }
          leaf1 = aux;
        }
        int dist;
        TreeNode *furthest;
        stack<TreeNode*> st;
        st.push(leaf1);
        visited[leaf1->val] = true;

        while(!st.empty()){
            TreeNode *u = st.top();
            st.pop();
            if(u->father != NULL && !visited[u->father->val]){
              st.push(u->father);
              visited[u->father->val] = true;
            }
            if(u->left != NULL && !visited[u->left->val]){
              st.push(u->left);
            }
            if(u->right != NULL && !visited[u->right->val]){
              st.push(u->right);
            }

        }

        return 0;
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
    cout << t.treeDiameter(t.getRoot());
    return 0;
}
