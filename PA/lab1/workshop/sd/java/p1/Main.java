import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class Main {
    static List<Integer> generateTest(int distinct, int repeatFactor) {
        List<Integer> result = new ArrayList<>();
        while (repeatFactor-- != 0) {
            for (int i = 0; i < distinct; ++i) {
                result.add(i);
            }
        }
        return result;
    }

    static int countDistinct(List<Integer> numbers) {
        // Create empty HashSet
        HashSet<Integer> set = new HashSet<>();

        //TODO Process numbers from input. HINT: a HashSet contains only distinct elements
        for (Integer number : numbers) {
        }

        //TODO Return the number of distinct elements HINT: a HashSet contains only distinct elements
        return 0;
    }

    public static void main(String[] args) {
        final int repeatFactor = 3;
        final int[] testsSizes = {10, 100, 1000, 10000};

        int numFailed = 0, numPassed = 0;

        for (int testSize : testsSizes) {
            List<Integer> numbers = generateTest(testSize, repeatFactor);

            int reference = testSize;
            int candidate = countDistinct(numbers);

            if (reference != candidate) {
                System.out.printf("Expected %d distinct elements but got %d distinct elements\n",
                        reference, candidate);
                numFailed++;
            } else {
                numPassed++;
            }
        }

        System.out.printf("Passed: %d, Failed: %d\n", numPassed, numFailed);
    }
}

