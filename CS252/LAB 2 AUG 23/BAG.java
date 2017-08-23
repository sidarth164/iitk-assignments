import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.Iterator;

//this implements linked list in reverse order
public class BAG<T> extends Object implements Iterable<T>{

	public static class Node<T>{
		public T item;
		Node next;
		public Node(T val){
			item=val;
			next=null;
		}
	}

	public Node head;
	public static int size=0;

	public BAG(){
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
		return new listIterator(head);
	}

	public static class listIterator<T> implements Iterator<T>{
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
			T item=current.item;
			current=current.next;
			return item;
		}
		public void remove(){
			throw new UnsupportedOperationException("illgeal operation!!");
		}

	}

	public static void main (String[] args) throws java.lang.Exception{
		BAG<Integer> b = new BAG<Integer>();
		b.add(5);
		b.add(6);
		b.add(7);
		System.out.println(b.Size());
		System.out.println(b.isEmpty()?'y':'n');
		Iterator<Integer> it = b.iterator();
		System.out.println(it.hasNext()?'y':'n');
		Integer x = it.next();
		System.out.println(x);
		System.out.println(it.hasNext()?'y':'n');
		x = it.next();
		System.out.println(x);
		System.out.println(it.hasNext()?'y':'n');
		x = it.next();
		System.out.println(x);
	}
}