import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.TreeSet;

public class UpperBound {
    enum OperationType {
        UPDATE,
        QUERY
    }

    static class Operation {
        OperationType type;
        int operand;

        public Operation(OperationType type, int operand) {
            this.type = type;
            this.operand = operand;
        }
    }

    static Random random = new Random();

    static List<Integer> randomList(int size) {
        ArrayList<Integer> result = new ArrayList<>();
        for (int i = 0; i < size; ++i) {
            result.add(random.nextInt(50));
        }
        return result;
    }

    static List<Operation> generateTest(List<Integer> answers) {
        List<Operation> result = new ArrayList<>();
        for (int answer : answers) {
            result.add(new Operation(OperationType.UPDATE, answer));
            while (random.nextInt(50) <= 10) {
                int number = random.nextInt(50);
                result.add(new Operation(OperationType.UPDATE, number));
            }
            result.add(new Operation(OperationType.QUERY, answer - 1));
        }
        return result;
    }

    static List<Integer> solve(List<Operation> operations) {
        List<Integer> result = new ArrayList<>();
        //TODO Create empty TreeSet

        for (Operation op : operations) {
            if (op.type == OperationType.UPDATE) {
                //TODO update set of elements with op.operand
            }
            if (op.type == OperationType.QUERY) {
                //TODO find first element greater than op.operand and add it to result.
                //TODO it is guaranteed that such an element exists
                //TODO HINT: TreeSet has a method which does exactly this
            }
        }
        return result;
    }

    public static void main(String[] args) {
        final int[] tests = {10, 20, 30, 40};

        int failed = 0, passed = 0;
        for (int test : tests) {
            List<Integer> reference = randomList(test);
            List<Operation> operations = generateTest(reference);
            List<Integer> candidate = solve(operations);

            if (!reference.equals(candidate)) {
                failed++;
                if (reference.size() != candidate.size()) {
                    System.out.printf("Expected a list of size %d, got a list of size %d\n",
                            reference.size(), candidate.size());
                    continue;
                }
                for (int i = 0; i < reference.size(); ++i) {
                    if (reference.get(i) != candidate.get(i)) {
                        System.out.printf("Expected response %d at %d query, but got %d\n",
                                reference.get(i), i, candidate.get(i));
                    }
                }
            } else {
                passed++;
            }
        }

        System.out.printf("Passed: %d, Failed: %d\n", passed, failed);
    }
}
