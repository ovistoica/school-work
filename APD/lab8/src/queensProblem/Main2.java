package queensProblem;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main2 {

	static int[] board;
	static final int N = 4;
	
	public static void addQueens(int[] board, int step) {
		if (step == N) {
			printQueens(board);
			return;
		}
		
		for(int i = 0; i < N; i++) {
			int[] newBoard = board.clone();
			newBoard[step] = i;
			if (verifyQueens(newBoard, step)) {
				addQueens(newBoard,step + 1);
			}
		}
	}
	
	public static Boolean verifyQueens(int[] board, int step) {
		int rowQ1,colQ1,rowQ2, colQ2;
		for (int i = 0; i <= step; i++) {
			rowQ1 = board[i];
			colQ1 = i;
			for (int j = 0; j <= step && i != j; j++) {
				rowQ2 = board[j];
				colQ2 = j;
				if ((colQ1 == colQ2) || (rowQ1 == rowQ2)) return false;
				if ((colQ1 - colQ2) == (rowQ1 - rowQ2)) return false;
			}
		}
		return true;
	}
	
	public static void printQueens(int[] board) {
		String aux = "";
		for (int i = 0; i < board.length; i++) {
			aux += board[i] + " ";
		}
		System.out.println(aux);
	}

	public static void main(String[] args) {
		int[] board = new int[N];
		addQueens(board, 0);
	}
}
