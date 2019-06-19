#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// DO NOT MODIFY
class Node {
private:
	int id;
	vector<Node*> children;

public:
	Node() {}
	~Node() {}

	int get_id() { return id; }
	void set_id(int i) { id = i; }

	vector<Node*> get_children() { return children; }
	void add_child(Node *n) { children.push_back(n); }
};

// DO NOT MODIFY
// Function to read tree data. Returns root pointer
Node* get_tree() {
	int n;
	cin >> n;
	vector<Node*> nodes;
	for (int i = 0; i < n; i++) {
		nodes.push_back(new Node());
	}

	string line;
	getline(cin, line);
	for (int i = 0; i < n; i++) {
		getline(cin, line);

		istringstream iss(line);
		int aux;
		iss >> aux;
		nodes[i]->set_id(aux);
	    for(; iss >> aux; )
			nodes[i]->add_child(nodes[aux]);
	}

	return nodes[0];
}


// Function which finds if a tree contains a given node
bool has_node(Node* root, int id) {
	// WRITE YOUR CODE HERE! (you can create any additional functions you need)
    if(root == NULL) return false;
    if(root->get_id() == id)return true;
		vector<Node*> c = root->get_children();
		for(auto it = c.begin(); it != c.end(); ++it){
			if(has_node(*it, id) == true) return true;
		}
		return false;
}

// DO NOT MODIFY
int main() {
	Node* root = get_tree();

	int n, id;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> id;
		cout << has_node(root, id) << "\n";
	}

	return 0;
}
