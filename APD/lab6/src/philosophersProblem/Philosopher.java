package philosophersProblem;

/**
 * @author cristian.chilipirea
 * 
 */
public class Philosopher implements Runnable {
	Object leftFork, rightFork;
	int id;

	public Philosopher(int id, Object leftFork, Object rightFork) {
		this.id = id;
		if (this.id == 0) {
			this.leftFork = rightFork;
			this.rightFork = leftFork;
			
		} else {
			this.leftFork = leftFork;
			this.rightFork = rightFork;
		}
	}

	private void sleep() {
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
		synchronized (leftFork) {
			sleep(); // delay added to make sure the dead-lock is visible
			synchronized (rightFork) {
				System.out.println("Philosopher " + id + " is eating");
			}
		}
	}
}
