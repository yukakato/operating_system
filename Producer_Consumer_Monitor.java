import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

class Producer extends Thread {
    private Queue<Integer> B;
    private int N, data;

    public Producer(Queue<Integer> B, int N) {
        this.B = B;
        this.N = N;
    }

    public void run() {
        for (int i = 0; i < 20; i++) {
            synchronized (B) {
                data = i;
                while (B.size() == N) {
                    System.out.println("Queue is full.");
                    try {
                        B.wait();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                B.add(data);
                System.out.println("Producing value : " + data);
                B.notifyAll();
            }
        }
    }
}

class Consumer extends Thread {
    private Queue<Integer> B;
    private int N, data;

    public Consumer(Queue<Integer> B, int N) {
        this.B = B;
        this.N = N;
    }

    public void run() {
        for (int i = 0; i < 20; i++) {
            synchronized (B) {
                while (B.isEmpty()) {
                    System.out.println("Queue is empty.");
                    try {
                        B.wait();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                data = B.remove();
                System.out.println("Consuming value : " + data);
                B.notifyAll();
            }
        }
    }
}

public class Producer_Consumer_Monitor {

    public static void main(String args[]) {
        Queue<Integer> B = new LinkedList<>();
        int N = 4;

        Thread thread_A = new Producer(B, N);
        Thread thread_B = new Consumer(B, N);

        thread_A.start();
        thread_B.start();
    }
}
