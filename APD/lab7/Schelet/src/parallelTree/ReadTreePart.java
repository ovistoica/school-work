package parallelTree;

import java.io.File;
import java.util.Scanner;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;


/**
 * @author cristian.chilipirea
 *
 */
public class ReadTreePart implements Runnable {
	TreeNode tree;
	String fileName;
	CyclicBarrier barrier;
	static Semaphore giveBirth = new Semaphore(1);

	public ReadTreePart(TreeNode tree, String fileName, CyclicBarrier barrier) {
		this.tree = tree;
		this.fileName = fileName;
		this.barrier = barrier;
	}

	@Override
	public void run() {
		try {
			Scanner scanner = new Scanner(new File(this.fileName));
			while(scanner.hasNextInt()){
				int node = scanner.nextInt();
				//http://chilipirea.ro/ap/
				
				int parent = scanner.nextInt();
				TreeNode treeParent = tree.getNode(parent);
				while (treeParent == null) {
					treeParent = tree.getNode(parent);
				}
				synchronized(treeParent) {
					treeParent.addChild(new TreeNode(node));
				}
			}
			scanner.close();
			barrier.await();
			} catch (Exception e) {
					e.printStackTrace();
		} 
	}
}