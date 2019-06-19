package binarySearch;

import java.util.concurrent.CyclicBarrier;

public class Main {
	public static int N = 1000;
	public static int P = 4;
	public static int arr[];
	public static int left = 0;
	public static int right = 1000;
	public static boolean found = false;
	public static int id;
	public static int x = 50;

	public static void main(String[] args) {
		CyclicBarrier barrier = new CyclicBarrier(P);

		for (int i = 0; i < N; i++) {
			arr[i] = i;
		}
		Thread threads[] = new Thread[P];

		for (int i = 0; i < P; i++) {
			threads[i] = new Thread(new Searcher(i, barrier));
		}
		for (int i = 0; i < P; i++)
			threads[i].start();
		
		for (int i = 0; i < P; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
	}
}
