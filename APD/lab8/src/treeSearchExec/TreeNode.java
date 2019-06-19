package treeSearchExec;

/**
 * @author cristian.chilipirea
 *
 */
public class TreeNode {
	int name;
	public TreeNode left = null;
	public TreeNode right = null;

	TreeNode(int name) {
		this.name = name;
	}

	void addChild(TreeNode child) {
		if (left == null) {
			left = child;
			return;
		}
		right = child;
	}

	TreeNode getNode(int name) {
		TreeNode aux = null;
		if (this.name == name)
			return this;
		return null;
	}
}
