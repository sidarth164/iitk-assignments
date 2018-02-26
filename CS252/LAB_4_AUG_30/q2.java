import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
public class q2 extends Thread
{
	private Integer[] array;
	private Integer max;
	public static Random rand= new Random();

	public q2(Integer arrSize){
		array=new Integer[arrSize];
		for(int i=0;i<arrSize;i++){
			array[i]=rand.nextInt(1000);
		}
	}

	public void run(){
		try{
			max=array[0];
			for(int i=1;i<array.length;i++){
				if(max<array[i]){
					max=array[i];
				}
			}
			System.out.println(max);
		} catch(Exception e){
			System.out.println(e);
		}
	}

	public Integer getMax(){
		return max;
	}

	public static void main (String[] args) throws java.lang.Exception
	{
		Integer n=Integer.parseInt(args[0]);
		Integer m=Integer.parseInt(args[1]);

		long start = System.currentTimeMillis();
		q2[] thr = new q2[n];
		Integer arrSize= m/n;
		for(int i=0;i<n;i++){
			thr[i]= new q2(arrSize);
			thr[i].start();
		}
		try{
			for(int i=0;i<n;i++){
				thr[i].join();
			}
		} catch(InterruptedException e){
			System.out.println(e);
		}

		Integer maximum=0;
		for(int i=0;i<n;i++){
			Integer max=thr[i].getMax();
			if(maximum<max)	
				maximum=max;
		}
		System.out.println("Maxima of all maxima = "+maximum);
		long duration = System.currentTimeMillis()- start;
		System.out.println("Time consumed = "+ duration);
	}
}