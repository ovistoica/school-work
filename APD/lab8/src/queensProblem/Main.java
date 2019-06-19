package queensProblem;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

	static int[] board;
	static final int N = 7;
	
	public static void addQueens(int[] board, int step, ExecutorService tpn) {
		if (step == N) {
			printQueens(board);
			tpn.shutdown();
			return;
		}
		
		for(int i = 0; i < N; i++) {
			int[] newBoard = board.clone();
			newBoard[step] = i;
			if (verifyQueens(newBoard, step)) {
				tpn.submit(new Runnable() {
					
					@Override
					public void run() {
						addQueens(newBoard,step + 1, tpn);
					}
				});
			}
		}
	}
	
	public static Boolean verifyQueens(int[] board, int step) {
		int rowQ1,colQ1,rowQ2, colQ2;
		for (int i = 0; i <= step - 1; i++) {
			rowQ1 = board[i];
			colQ1 = i;
			for (int j = i + 1; j <= step; j++) {
				rowQ2 = board[j];
				colQ2 = j;
				if ((colQ1 == colQ2) || (rowQ1 == rowQ2)) return false;
				if ((colQ1 - colQ2) == (rowQ1 - rowQ2)) return false;
				if ((colQ1 - colQ2) == -(rowQ1 - rowQ2)) return false;
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
		ExecutorService tpn = Executors.newFixedThreadPool(4);
		tpn.shutdownNow();
		tpn.submit(new Runnable() {
			
			@Override
			public void run() {
				addQueens(board, 0, tpn);
			}
		});
	}
}
