package binarySearch;

import java.util.concurrent.*;

public class Searcher implements Runnable {
	int id;
	int start;
	int end;
    CyclicBarrier barrier;
	
	
	Searcher(int id, CyclicBarrier barrier) {
		this.id = id;
        this.start = (int)Math.ceil((double)Main.right/ Main.P * id );
        this.end = (int)Math.min((Math.ceil(((double)Main.right / Main.P) * (this.id + 1))), Main.right);
        this.barrier = barrier;
	}

	public int search(int start, int end, int x) {
		if (end >= start) {
			int mid = start + (end - start) / 2;
			if (Main.arr[mid] == x) {
				return mid;
			}
			if (Main.arr[mid] > x) {
				return search(start, mid-1, x);
			} else {
				return search(mid+1, end, x);
			}
		}
		return -1;
	}
	
	@Override
	public void run() {
			if (start >= Main.x && Main.x <= end) {
				Main.found = true;
				Main.id = this.id;
				Main.left = start;
				Main.right = end;
			}
            try
            {
                barrier.await();
            }
            catch (InterruptedException | BrokenBarrierException e ) {
                e.printStackTrace ();
            }
            
	}
}
