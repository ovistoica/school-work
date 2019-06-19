package prob_colocviu;
import java.util.ArrayList;
import java.util.concurrent.CyclicBarrier;
import java.math.*;

public class Main {
	public static int N = 10;
	public static int P = 4;
	public static int[] arr = new int[N];
	public static int id;
	public static int x = 50;
	public static int[] positions = new int[N];
	public static void main(String[] args) {

		for (int i = 0; i < N; i++) {
			arr[i] =  (int)Math.random();
		}
		for (int i = 0; i < N; i++) {
			positions[i] = Integer.MAX_VALUE;
		}
		Thread threads[] = new Thread[P];

		for (int i = 0; i < P; i++) {
			//TODO
			threads[i] = new Thread(new MyThread(i));
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
//		int[] copy = new int[N];
//		for (int i = 0; i < N; ++i) {
//			copy[i] = arr[i];
//		}
//		
//		for(int i = 0; i < N; ++i) {
//			arr[i] = copy[positions[i]];
//		}
		
		for (int i = 0; i < N; ++i) {
			System.out.print(positions[i] + ' ');
			
		}

		

		
	}
}
