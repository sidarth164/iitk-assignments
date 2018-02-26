import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.Iterator;

//this implements linked list in reverse order
public class LinkedBag<T> extends Object implements Iterable<T>{

	public class Node<T>{
		public T item;
		Node next;
		public Node(T val){
			item=val;
			next=null;
		}
	}

	public Node head;
	public static int size=0;

	public LinkedBag(){
		head=null;
		size=0;
	}

	public void add(T item){
		Node newnode=new Node(item);
		newnode.next=head;
		head=newnode;
		size+=1;
	}

	public boolean isEmpty(){
		if(size==0)
			return true;
		return false;
	}

	public int Size(){
		return size;
	}

	public Iterator<T> iterator(){
		/*Node<T> temp=head;
		int flag=0;
		while(temp!=null){
			if(temp.item=key){
				flag=1;
				break;
			}
			temp=temp.next;
		}
		if(flag)
			return new listIterator(temp);*/
		return new listIterator(head);
	}

	public class listIterator<T> implements Iterator<T>{
		public Node<T> current;
		public listIterator(Node head){
			current = head;
		}
		public boolean hasNext(){
			if(current==null || current.next==null)
				return false;
			return true;
		}
		public T next(){
			if(!hasNext())
				throw new NoSuchElementException("no positions available!!");
			current=current.next;
			return current.item;
		}
		public void remove(){
			throw new UnsupportedOperationException("illgeal operation!!");
		}

	}

	public static void main (String[] args) throws java.lang.Exception{
		LinkedBag<Integer> b = new LinkedBag<Integer>();
		b.add(5);
		b.add(7);
		System.out.println(b.Size());
		System.out.println(b.isEmpty()?'y':'n');
	}
}