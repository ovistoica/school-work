import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Proiectarea Algoritmilor, 2016
 * Crash-course debugging & structuri de date
 * Task 1 debugging: Generare de permutari
 *
 * @author 	Cosmin Dragomir
 * @email	cosmin.gabriel.dragomir@gmail.com
 */

public class Permutations {
	public static int solutionsCounter;
	public static int elementsNumber;
	// stores the solution
	public static int[] solution;
	// true if i+1 was selected in the current partial solution, false otherwise
	public static boolean[] usedElements;
	
	//TODO There are 2 bugs in this method. Find them :)
	public static void generatePermutations(int level) {
		if (level == elementsNumber) {
			for (int i = 0; i < level; i++) {
				System.out.print(solution[i] + " ");
			}
			System.out.println();
			solutionsCounter++;
			return;
		}
		
		for (int i = 0; i < usedElements.length; i++) {
			if (!usedElements[i]) {
				usedElements[i] = true;
				solution[level] = i + 1;
				generatePermutations(++level);
			}
		}
	}
	
	public static void main(String[] args) {
		try {
			Scanner s = new Scanner(new File("permutations.in"));
			int testsNumber = s.nextInt();
			for (int i = 0; i < testsNumber; i++) {
				solutionsCounter = 0;
				elementsNumber = s.nextInt();
				System.out.println("Numbers interval: 1 - " + elementsNumber);
				System.out.println("Solutions:");
				usedElements = new boolean[elementsNumber];
				solution = new int[elementsNumber];
	            
				generatePermutations(0);
				System.out.println("Number of solutions: " + solutionsCounter + "\n");
			}
		} catch (FileNotFoundException ex) {
			Logger.getLogger(Permutations.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
}
