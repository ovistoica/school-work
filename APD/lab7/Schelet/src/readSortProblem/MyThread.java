package readSortProblem;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Semaphore;

public class MyThread implements Runnable{
	
	int id;
	static Semaphore sem = new Semaphore(-2);
	static ArrayBlockingQueue<Integer> queue;
	
	public MyThread(int id) {
		this.id = id;
	}

	@Override
	public void run() {
		if (id >= 1 && id <= 3) {
			try {
				File file = new File("/home/stoica/workspace/APD/lab7/Schelet/elemente" + this.id + ".txt");
				BufferedReader br = new BufferedReader(new FileReader(file));
				String st; 
				Integer i;
				while ((st = br.readLine()) != null) { 
					i = Integer.parseInt(st);
					queue.put(i);
			  	} 
				br.close();
				sem.release();
			} catch (InterruptedException | NumberFormatException | IOException e) {
				e.printStackTrace();
			}
		}
		else {
				try {
					sem.acquire();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				Integer[] arr = queue.toArray(new Integer[0]);
				Arrays.sort(arr);
				for(int i = 0; i < arr.length; i++ ) {
					System.out.println(arr[i]);
				}
				System.out.println("Am ajuns aici");
		}
	}
}
