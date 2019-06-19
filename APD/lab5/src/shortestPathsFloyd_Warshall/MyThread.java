package shortestPathsFloyd_Warshall;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class MyThread implements Runnable {
    int id;
    static int value = 0;
    int v[][];
    int start;
    int end;
    CyclicBarrier barrier;

//    int thread_id = *(int*)var;

    MyThread(int id, int v[][], int P, CyclicBarrier barrier) {
        this.id = id;
        this.start = (int)Math.ceil((double)5/ P * id );
        this.end = (int)Math.min((Math.ceil(((double)5 / P) * (this.id + 1))), 5);
        this.v = v;
        this.barrier = barrier;
    }

    @Override
    public void run() {

        // Parallelize me (You might want to keep the original code in order to compare)
        for (int k = 0; k < 5; k++) {
            try
            {
                barrier.await();
            }
            catch (InterruptedException | BrokenBarrierException e ) {
                e.printStackTrace ();
            }
            for (int i = 0; i < 5; i++) {
                for (int j = start; j < end; j++) {
                    v[i][j] = Math.min(v[i][k] + v[k][j], v[i][j]);
                }
            }
        }

    }
}
