package prob_colocviu;

import java.util.concurrent.CyclicBarrier;

public class MyThread implements Runnable {
	
	public int id;
	public int start;
	public int end;
	public MyThread(int id) {
		// TODO Auto-generated constructor stub
		this.id = id;
		this.start = (int)Math.ceil(Main.N / Main.P * id);
		this.end = Math.min((int)Math.ceil(Main.N / Main.P * (id + 1)), Main.N);
		end = end - 1;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		for (int i = start; i < end; ++i) {
			int count = 0;
			for(int j = 0; i < Main.N; ++j) {
				if (Main.arr[j] < Main.arr[i]) {
					++count;
				}
			}
			Boolean assigned = false;
			int steps = 0;
			while (!assigned) {
				synchronized (MyThread.class) {
					if (Main.positions[count] == Integer.MAX_VALUE) {
						Main.positions[count] = Main.arr[i];
						assigned = true;
					}
					else {
						count++;
					}
				}
				if (steps > 5) {
					break;
				}
				++steps;
			}
		}
	}

}
