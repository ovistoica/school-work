package oneProducerOneConsumer;

import java.util.concurrent.Semaphore;

/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	static final int SIZE = 5;
	int[] a;
	int put;
	int get;
	Semaphore full;
	Semaphore empt;
	
	Buffer() {
		a = new int[SIZE];
		put = 0;
		get = 0;
		full = new Semaphore(5);
		empt = new Semaphore(0);
	}

	void put(int value) {
		try {
			full.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		synchronized (this) {
			a[put++] = value;
			if(put == 5) {
				put = 0;
			}
			
		}
		empt.release();
	}

	int get() {
		try {
			empt.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		synchronized(this) {
			int val = a[get++];
			if (get == 5) {
				get = 0;
			}
			full.release();
			return val;
		}
	}

}
