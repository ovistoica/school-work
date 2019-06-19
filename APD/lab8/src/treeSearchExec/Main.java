package treeSearchExec;

/**
 * @author cristian.chilipirea
 * 
 * This program should print SOME of the numbers between 0 and 10.
 * Because of the way we shutdown the ExecutorService some tasks do not get submitted.
 * This is OK in cases where we want to find at least one solution, but not necessarily all solutions.
 */

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

	public static void main(String[] args) {

		TreeNode tn = new TreeNode(2);
		tn.addChild(new TreeNode(4));
		tn.addChild(new TreeNode(5));
		tn.addChild(new TreeNode(6));
		tn.addChild(new TreeNode(7));
		tn.addChild(new TreeNode(8));
		tn.addChild(new TreeNode(9));
		tn.addChild(new TreeNode(10));
		tn.addChild(new TreeNode(224));
		tn.addChild(new TreeNode(2234));
		tn.addChild(new TreeNode(2));
		tn.addChild(new TreeNode(874));
		ExecutorService tpe = Executors.newFixedThreadPool(4);
		tpe.submit(new NodeParser(tpe, tn, 7));
	}
}
