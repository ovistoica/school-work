import java.util.Set;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Class for a miner.
 */
public class Miner extends Thread {

	private Integer parentRoom;
	private Integer currentRoom;
	private String data;

	private Integer hashCount;
	private Set<Integer> solved;
	private CommunicationChannel channel;

	// helper messages
	private static String NO_PARENT = "NO_PARENT";

	/**
	 * Message body that specifies the end of the list of unlocked adjacent rooms
	 * sent by the wizards to the miners.
	 */
	public static String END = "END";

	/**
	 * Message body that specifies the end of the program (sent to each miner).
	 */
	public static String EXIT = "EXIT";

	/**
	 * Creates a {@code Miner} object.
	 * 
	 * @param hashCount
	 *            number of times that a miner repeats the hash operation when
	 *            solving a puzzle.
	 * @param solved
	 *            set containing the IDs of the solved rooms
	 * @param channel
	 *            communication channel between the miners and the wizards
	 */
	public Miner(Integer hashCount, Set<Integer> solved, CommunicationChannel channel) {
		this.hashCount = hashCount;
		this.solved = solved;
		this.channel = channel;
	}

	private String encryptMultipleTimes(String input) {
		String hashed = input;
		for (int i = 0; i < this.hashCount; ++i) {
			hashed = encryptThisString(hashed);
		}

		return hashed;
	}

	private String encryptThisString(String input) {
		try {
			MessageDigest md = MessageDigest.getInstance("SHA-256");
			byte[] messageDigest = md.digest(input.getBytes(StandardCharsets.UTF_8));

			// convert to string
			StringBuffer hexString = new StringBuffer();
			for (int i = 0; i < messageDigest.length; i++) {
				String hex = Integer.toHexString(0xff & messageDigest[i]);
				if(hex.length() == 1) hexString.append('0');
				hexString.append(hex);
			}
			return hexString.toString();

		} catch (NoSuchAlgorithmException e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public void run() {
		Message message;

		while(true) {
			synchronized (Miner.class) {

				message = channel.getMessageWizardChannel();
				if (message.getData() == Miner.END) {
					this,wait();
					continue;
				}
				else if (message.getData() == Miner.EXIT) {
					break;
				}
				else {
					parentRoom = message.getCurrentRoom();
					message = channel.getMessageWizardChannel();
					currentRoom = message.getCurrentRoom();
					data = message.getData();
				}

				if (solved.contains(currentRoom)) {
					continue;
				} else {
					solved.add(currentRoom);
				}
			}
			data = encryptMultipleTimes(data);
			channel.putMessageMinerChannel(new Message(parentRoom, currentRoom, data));

		}
	}
}
