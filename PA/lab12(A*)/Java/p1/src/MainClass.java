import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;


class StateComparator implements Comparator<State> {

	enum Algorithm {
		BestFirst, AStar
	}

	private Algorithm algorithm;
	private State solutionState;

	/**
	 * Create a new StateComparator which compares two different states given
	 * the wanted algorithm and solution state.
	 * @param algorithm BestFirst or AStar
	 * @param solutionState desired solution state
	 */
	public StateComparator(Algorithm algorithm, State solutionState) {
		this.algorithm = algorithm;
		this.solutionState = solutionState;
	}

	private int computeF(State state) { 
		int result = 0;
		/* f(n) = g(n) + h(n) */
		switch(algorithm) {
		case BestFirst:
			/* g(n) = 0 */
			result = state.approximateDistance(solutionState);
		case AStar:
			/* g(n) = numarul de mutari din pozitia initiala */
			result = state.getDistance() + state.approximateDistance(solutionState);
		}
		return result;
	}

	@Override
	public int compare(State arg0, State arg1) {
		return computeF(arg0) - computeF(arg1);
	}
}

public class MainClass {

	static State initialState;
	static State solutionState;

	public static void readData(String filename) {
		int x, y;
		int numRows, numCols;

		Scanner scanner;
		try {
			scanner = new Scanner(new File(filename));

			/* read map stats */
			numRows = scanner.nextInt();
			numCols = scanner.nextInt();
			State.init(numRows, numCols);

			x = scanner.nextInt();
			y = scanner.nextInt();
			initialState = new State(x, y);

			x = scanner.nextInt();
			y = scanner.nextInt();
			solutionState = new State(x, y);

			/* read the map */
			for(int i = 0; i < State.numRows; i++)
				for(int j = 0; j < State.numCols; j++)
					if(scanner.nextInt() == 1)
						State.matrix[i][j] = true;

			scanner.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		/* Citire harta, stare initiala si finala */
		readData("Puzzle.in");

		Comparator<State> stateComparator = new StateComparator(StateComparator.Algorithm.AStar, solutionState);
		PriorityQueue<State> open = new PriorityQueue<State>(1, stateComparator);
		
		/* Initial doar nodul de start este in curs de explorare */
		open.add(initialState);

		/* Pentru nodurile care au fost deja expandate. */
		ArrayList<State> closed = new ArrayList<State>();

		/* TODO: A* */
		
	}

}
