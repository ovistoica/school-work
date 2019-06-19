package treeSearchExec;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;

public class NodeParser implements Runnable{
	ExecutorService tpe;
	public TreeNode tn;
	public int toFind;
	
	public NodeParser(ExecutorService tpe, TreeNode tn, int toFind) {
		this.tpe = tpe;
		this.tn = tn;
		this.toFind = toFind;
	}
	
	@Override
	public void run() {
		if (tn.getNode(toFind) != null) {
			System.out.println("Found to find");
			tpe.shutdown();
			return;
		} else {
			tpe.submit(new NodeParser(tpe, tn.left, toFind));
			tpe.submit(new NodeParser(tpe, tn.right, toFind));
		}
	}
		
}
