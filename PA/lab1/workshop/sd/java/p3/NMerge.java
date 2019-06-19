import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class NMerge {
	
    static class Value {
    	int number;
        int arrayIndex;

        public Value(int number, int arrayIndex) {
            this.number = number;
            this.arrayIndex = arrayIndex;
        }
    }
    
    static class ValueComparator implements Comparator<Value> {
		@Override
		public int compare(Value a, Value b) {
			return a.number - b.number;
		}
    }
	
	public static ArrayList<Integer> doNMerge(int[][] arrays) {
		ArrayList<Integer> result = new ArrayList<Integer>();
		
		// TODO 1: Declare PriorityQueue to hold Value elements, using the ValueComparator
		// TODO 2: Use an array to hold the last index used from every array
		// TODO 3: Add the first value from each array to the PriorityQueue
		// TODO 4: While you can, remove the smallest value from the PriorityQueue and add
		//		   the next value from the same array to the PriorityQueue
		//		   Hint: Verify if you still have a next element in that array.
		
		return result; 
	}
	
	public static void main(String[] args) {
		try {
			Scanner s = new Scanner(new File("nmerge.in"));
			int arraysNumber = s.nextInt();
			int[] arraysSize = new int[arraysNumber];
			for (int i = 0; i < arraysNumber; i++) {
				arraysSize[i] = s.nextInt();
			}
			int[][] arrays = new int[arraysNumber][];
			ArrayList<Integer> reference = new ArrayList<Integer>();
			for (int i = 0; i < arraysNumber; i++) {
				arrays[i] = new int[arraysSize[i]];
				for (int j = 0; j < arraysSize[i]; j++) {
					arrays[i][j] = s.nextInt();
					reference.add(arrays[i][j]);
				}
			}
			Collections.sort(reference);
			
			ArrayList<Integer> candidate = doNMerge(arrays);
			
			System.out.println(candidate);
			if (reference.equals(candidate)) {
				System.out.println("Congrats. The arrays were merged correctly.");
			} else {
				System.out.println("Too bad. The arrays were not merged correctly.");
			}
		} catch (FileNotFoundException ex) {
			Logger.getLogger(NMerge.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
}
