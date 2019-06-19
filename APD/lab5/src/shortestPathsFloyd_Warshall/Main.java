package shortestPathsFloyd_Warshall;

import java.util.concurrent.CyclicBarrier;

/**
 * @author cristian.chilipirea
 *
 */
public class Main {

	public static void main(String[] args) {
		int M = 9;
		int graph[][] = { { 0, 1, M, M, M }, 
				          { 1, 0, 1, M, M }, 
				          { M, 1, 0, 1, 1 }, 
				          { M, M, 1, 0, M },
				          { M, M, 1, M, 0 } };
		int P = 4;

		Thread threads[] = new Thread[P];
		CyclicBarrier barrier = new CyclicBarrier(P);

		for (int i = 0; i < P; i++)
			threads[i] = new Thread(new MyThread(i,graph,P, barrier));
		for (int i = 0; i < P; i++)
			threads[i].start();
		for (int i = 0; i < P; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph[i][j] + " ");
			}
			System.out.println();
		}
	}
}
