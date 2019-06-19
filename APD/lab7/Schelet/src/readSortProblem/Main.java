package readSortProblem;

import java.util.concurrent.ArrayBlockingQueue;

public class Main {
	
	public static void main(String[] args) {
		Thread threads[] = new Thread[4];
		MyThread.queue = new ArrayBlockingQueue<>(10000);
		
			for (int i = 0; i < 4; i++)
				threads[i] = new Thread(new MyThread(i));
			for (int i = 0; i < 4; i++)
				threads[i].start();
			for (int i = 0; i < 4; i++) {
				try {
					threads[i].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
	}
}
