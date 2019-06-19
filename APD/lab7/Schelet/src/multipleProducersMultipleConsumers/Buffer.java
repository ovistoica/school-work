package multipleProducersMultipleConsumers;

import java.util.concurrent.ArrayBlockingQueue;

/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	ArrayBlockingQueue<Integer> q;

	public Buffer() {
		q = new ArrayBlockingQueue<Integer>(5);
	}

	void put(int value) {
		try {
			q.put(value);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	Integer get() {
		try {
			return q.take();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return -1;
	}
}
