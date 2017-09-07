import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
public class q3 extends Thread
{	
	private static Queue<Integer> queue = new LinkedList<>();
	private Integer t_id;
	private Integer customer=1;
	public static Random rand = new Random();
	public q3(Integer id){
		t_id = id;
	}
	public void run(){
		try{
			while(true){
			if(t_id==1){
				synchronized(queue){
					while(queue.size()==0){
						System.out.println("Queue is empty!!");
						queue.wait();
					}
					
					Integer cust=queue.remove();
					System.out.println("Removing Customer #"+cust+" from the Queue.");
					queue.notifyAll();
					sleep(5000);
				}
			}
			else{
				synchronized(queue){
					while(queue.size()==100){
						System.out.println("Queue is full!!");
						queue.wait();
					}
				
					System.out.println("Adding Customer #"+customer+" to the Queue.");
					queue.add(customer);
					customer+=1;
					long delay=(long)(rand.nextInt(981)+20);
					queue.notifyAll();
					sleep(delay);
				}
			}}

		}catch(Exception e){
			System.out.println(e);
		}
	}
	public static void main (String[] args) throws java.lang.Exception
	{
		q3 pio=new q3(1);
		q3 guard=new q3(2);
		guard.start();
		pio.start();
	}
}