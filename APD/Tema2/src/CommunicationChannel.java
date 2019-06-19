import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Class that implements the channel used by wizards and miners to communicate.
 */
public class CommunicationChannel {
	private BlockingQueue<Message> forWizards;
	private BlockingQueue<Message> forMiners;
	ReentrantLock lock;
	
	/**
	 * Creates a {@code CommunicationChannel} object.
	 */
	public CommunicationChannel() {
		forWizards = new LinkedBlockingQueue<Message>();
		forMiners = new LinkedBlockingQueue<Message>();
		lock = new ReentrantLock();
	}

	/**
	 * Puts a message on the miner channel (i.e., where miners write to and wizards
	 * read from).
	 * 
	 * @param message
	 *            message to be put on the channel
	 */
	public void putMessageMinerChannel(Message message){
		try {
			forWizards.put(message);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Gets a message from the miner channel (i.e., where miners write to and
	 * wizards read from).
	 * 
	 * @return message from the miner channel
	 */
	public Message getMessageMinerChannel() {
		try {
			return forWizards.take();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return null;
	}

	/**
	 * Puts a message on the wizard channel (i.e., where wizards write to and miners
	 * read from).
	 * 
	 * @param message
	 *            message to be put on the channel
	 */
	public void putMessageWizardChannel(Message message) {
		try {
			lock.lock();
			forMiners.put(message);
			if (message.getData() == Wizard.END) {
				lock.unlock();
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Gets a message from the wizard channel (i.e., where wizards write to and
	 * miners read from).
	 * 
	 * @return message from the miner channel
	 */
	public Message getMessageWizardChannel() {
		Message message = null;
		try {
			message = forMiners.take();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return message;
	}
}
