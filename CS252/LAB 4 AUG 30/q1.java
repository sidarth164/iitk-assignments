import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
public class q1 extends Thread
{

	private int a,c;
	private long delay;
	public q1(int a1,int a3,long del){
		a=a1;
		c=a3;
		delay=del;
	}

	public void run(){
		try{
			while(true){
				System.out.println(a);
				a=a+a;
				sleep(delay);
			}
		} catch(InterruptedException e){
			System.out.println(e);
		}
	}

	public static void main (String[] args) throws java.lang.Exception
	{
		Integer a1=Integer.parseInt(args[0]);
		Integer a2=Integer.parseInt(args[1]);
		Integer a3=Integer.parseInt(args[2]);
		long del1=(long)a3*1000;
		long del2=(long)a3*1500;
		q1 thr1= new q1(a1,a3,del1);
		q1 thr2= new q1(a2,a3,del2);

		thr1.start();
		thr2.start();
	}
}