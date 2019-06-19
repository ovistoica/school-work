import java.util.ArrayList;

public class State {
	
	public static final int E = 1;
	public static final int W = 2;
	
	public int canWest, canEast, misWest, misEast;
	public int boatPosition;
	
	private int distance;
	private State parent;
	
	public State() {
		this.canEast = 0;
		this.canWest = 0;
		this.misEast = 0;
		this.misWest = 0;
		this.distance = 0;
		this.parent = null;
	}
	
	public State(int misEast, int canEast, int misWest, int canWest,
			int boatPosition, State parent, int distance) {
		
		this.canWest = canWest;
		this.canEast = canEast;
		this.misWest = misWest;
		this.misEast = misEast;
		this.boatPosition = boatPosition;
		this.distance = distance;
		this.parent = parent;
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
	 * Verifies if this state is valid.
	 * @return true if the state is valid
	 */
	public boolean isValidState() {
		/* verifica numar valid de misionari si canibali */
		if(misEast < 0 || canEast < 0 || misWest < 0 || canWest < 0)
			return false;
		/* verifica daca sunt mai multi canibali decat misionari pe vreun mal */
		if((misEast > 0 && misEast < canEast) || (misWest > 0 && misWest < canWest))
			return false;
		return true;
	}
	
	/**
	 * Expands this state.
	 * @return array with all the states which are reachable from this position.
	 */
	public ArrayList<State> expand() {
		ArrayList<State> neighbours = new ArrayList<State>();
		State s;
		/* incerc sa mut 1 canibal + 1 misionar */
		if(boatPosition == E)
			s = new State(misEast - 1, canEast - 1, misWest + 1, canWest + 1, W, this, distance + 1);
		else
			s = new State(misEast + 1, canEast + 1, misWest - 1, canWest - 1, E, this, distance + 1);
		if(s.isValidState())
			neighbours.add(s);
		
		/* incerc sa mut 2 canibali */
		if(boatPosition == E)
			s = new State(misEast, canEast - 2, misWest, canWest + 2, W, this, distance + 1);
		else
			s = new State(misEast, canEast + 2, misWest, canWest - 2, E, this, distance + 1);
		if(s.isValidState())
			neighbours.add(s);
		
		/* incerc sa mut 2 misionari */
		if(boatPosition == E)
			s = new State(misEast - 2, canEast, misWest + 2, canWest, W, this, distance + 1);
		else
			s = new State(misEast + 2, canEast, misWest - 2, canWest, E, this, distance + 1);
		if(s.isValidState())
			neighbours.add(s);
		
		/* incerc sa mut 1 canibal */
		if(boatPosition == E)
			s = new State(misEast, canEast - 1, misWest, canWest + 1, W, this, distance + 1);
		else
			s = new State(misEast, canEast + 1, misWest, canWest - 1, E, this, distance + 1);
		if(s.isValidState())
			neighbours.add(s);
		
		/* incerc sa mut 1 misionar */
		if(boatPosition == E)
			s = new State(misEast - 1, canEast, misWest + 1, canWest, W, this, distance + 1);
		else
			s = new State(misEast + 1, canEast, misWest - 1, canWest, E, this, distance + 1);
		if(s.isValidState())
			neighbours.add(s);
		
		return neighbours;
	}
	
	/**
	 * Heuristic for computing distance to the final state
	 * @return distance to final state
	 */
	public int approximateDistance() {
		/* TODO: functie admisibila care sa estimeze costul pana la starea
		 * finala */
		
		return 0;
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
		return this.canWest == other.canWest && 
				this.canEast == other.canEast &&
				this.misWest == other.misWest &&
				this.misEast == other.misEast &&
				this.boatPosition == other.boatPosition;
	}

	@Override
	public String toString() {
		return "( M = " + misEast + ", C = " + canEast + " | M = "
				+ misWest + ", C = " + canWest + ")";
	}
}
