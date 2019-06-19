import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.PointerInfo;
import java.awt.image.ImageObserver;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Random;

import javax.swing.JApplet;



@SuppressWarnings("serial")
public class Main extends JApplet implements Runnable {
	Random r = new Random(42);
	int x = 0;
	int y = 0;
	String hour = "";
	String minute = "";
	String second = "";
	long fib = 0;
	Thread timeT = new Thread(){
		@Override
		public void run() {
			Calendar cal = new GregorianCalendar();
			while(true) {
				hour = String.valueOf(cal.get(Calendar.HOUR));
				minute = String.valueOf(cal.get(Calendar.MINUTE));
				second = String.valueOf(cal.get(Calendar.SECOND));
				
			}
		}
	};

	Thread fiboT = new Thread(){
		@Override
		public void run() {
			while (true) {
				fib = Math.abs(calculateFibonacci(Math.abs(r.nextInt())));
			}
		}
	};
	
	Thread pointerT = new Thread() {
		@Override
		public void run() {
			while(true) {
				PointerInfo a = MouseInfo.getPointerInfo();
				Point b = a.getLocation();
				x = (int) b.getX();
			}
		}
	};

	public void start() {
		Thread t = new Thread(this);
		t.start();
		fiboT.start();
		pointerT.start();
		timeT.start();

	}

	public static long calculateFibonacci(long n) {
		long a = 0;
		long b = 1;
		for (long i = 0; i < n; i++) {
			long c = a + b;
			a = b;
			b = c;
		}
		return b;
	}

	public void run() {
		
		long prevTime = 0;
		while (true) {
			long time = System.currentTimeMillis();
			if (time - prevTime > 40) { // Make sure we stay at 25 FPS max
				prevTime = time;
				repaint();
			}
		}
	}

	public void paint(Graphics g) {
		// draw everything
		Image img = createImage(500, 500); 
		Graphics gr = img.getGraphics();
		gr.setColor(Color.WHITE);
		gr.fillRect(0, 0, 500, 500);
		gr.setColor(Color.BLACK);
		gr.drawString("Time " + hour + ":" + minute + ":" + second, 10, 20);
		gr.drawString("Mouse at " + x, 10, 30);
		gr.drawString("Last digit Fibonacci is " + (fib % 10), 10, 40);
		g.drawImage(img, 0, 0, null);
		// get pointer location

	}
}