package doubleVectorElements;

public class MyThread implements Runnable {
    int id;
    static int value = 0;
    int v[];
    int start;
    int end;

//    int thread_id = *(int*)var;

    MyThread(int id, int v[], int P, int N) {
        this.id = id;
        this.start = (int)Math.ceil((double)N/ P * id );
        this.end = (int)Math.min((Math.ceil(((double)N / P) * (this.id + 1))), N);
        this.v = v;
    }

    @Override
    public void run() {
        System.out.println("Thread id:" + id + " Start: " + start + " End: " + end);

        for (int i = this.start; i < this.end ; i++) {
            v[i] = v[i] * 2;
        }

    }
}
