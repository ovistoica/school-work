import java.util.ArrayList;

public class State {
	
	public static int numRows, numCols;
	public static boolean[][] matrix;

	public int x, y;
	
	private int distance;
	private State parent;
	
	/**
	 * Init method for initializing static members of this class. Should be
	 * called before the algorithm is run.
	 * @param numRows
	 * @param numCols
	 */
	public static void init(int numRows, int numCols) {
		State.numRows = numRows;
		State.numCols = numCols;
		State.matrix = new boolean[numRows][numCols];
	}
	
	/**
	 * Constructor for parent-less state.
	 * @param x column position
	 * @param y row position
	 */
	public State(int x, int y) {
		this.x = x;
		this.y = y;
		this.parent = null;
		this.distance = 0;
	}
	
	/**
	 * Constructor for states with parents + distance init.
	 * @param x column position
	 * @param y row position
	 * @param parent parent state for this state
	 * @param distance distance to the new state (should be old distance + 1)
	 */
	public State(int x, int y, State parent, int distance) {
		this(x,y);
		this.parent = parent;
		this.distance = distance;
	}
	
	public void setDistance(int distance) {
		this.distance = distance;
	}
	
	public int getDistance() {
		return distance;
	}
	
	public void setParent(State parent) {
		this.parent = parent;
	}
	
	public State getParent() {
		return parent;
	}
	
	/**
	 * Expands this state.
	 * @return array with all the states which are reachable from this position.
	 */
	public ArrayList<State> expand() {
		ArrayList<State> neighbours = new ArrayList<State>();
		
		/* above */
		if(y > 0 && matrix[y - 1][x])
			neighbours.add(new State(x, y - 1, this, this.distance + 1));
		/* below */
		if(y < numRows - 1 && matrix[y + 1][x])
			neighbours.add(new State(x, y + 1, this, this.distance + 1));
		/* left */
		if(x > 0 && matrix[y][x - 1])
			neighbours.add(new State(x - 1, y, this, this.distance + 1));
		/* right */
		if(x < numCols - 1 && matrix[y][x + 1])
			neighbours.add(new State(x + 1, y, this, this.distance + 1));
		
		return neighbours;
	}
	
	/**
	 * Heuristic for computing distance to @other state
	 * @param other destination state.
	 * @return distance to @other
	 */
	public int approximateDistance(State other) {
		int d = 0;
		/* TODO: functie admisibila care sa estimeze costul pana la starea
		 * finala */
		
		return d;
	}
	
	private void printReversePath(State current) {
		if(current == null)
			return;
		printReversePath(current.getParent());
		System.out.println(current);
	}
	
	/**
	 * Prints the path from initial state to the solution state.
	 */
	public void printPath() {
		printReversePath(this);
	}
	
	@Override
	public boolean equals(Object obj) {
		State other = (State)obj;
		return this.x == other.x && this.y == other.y;
	}

	@Override
	public String toString() {
		return "(" + y + ", " + x + ")";
	}
}