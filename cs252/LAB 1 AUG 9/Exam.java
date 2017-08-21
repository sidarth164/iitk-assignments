import java.util.*;
import java.lang.*;
import java.io.*;
import java.lang.reflect.*;

abstract class ExamCentres{
	public static final int LKO = 10;
	public static final int CNB = 20;
	public static final int AGC = 30;
	public static final int ALD = 40;
	public static final int VNS = 50;
}

public class Exam{
	String title;
	int centre_code;

	public Exam(String ti, int code){
		this.title=ti;
		this.centre_code=code;
	}

	public void SetTitle(String ti){
		this.title=ti;
	}
	public String GetTitle(){
		return this.title;
	}

	public void SetCentreCode(int code){
		this.centre_code=code;
	}
	public int GetCentreCode(){
		return this.centre_code;
	}

	public void printCentreName(ExamCentres obj){
		try{
			for (Field field : obj.getClass().getFields()) {
				if(this.centre_code == (int)field.get(null)){
					System.out.println(field.getName());
					return;
				}
			}
		}
		catch(Exception e){};
		System.out.println("Unknown");
	}

	public boolean isValidCentre(int code, ExamCentres obj){
		try{	
			for (Field field : obj.getClass().getFields()) {
				if(code==(int)field.get(null))
					return true;
			}
		}
		catch(Exception e){};
		return false;
	}

	public static void main (String[] args) {
		ExamCentres obj=new ExamCentres(){};
		String ti="JEE";
		int code=50;
		Exam exam=new Exam(ti,code);
		exam.printCentreName(obj);
		if(exam.isValidCentre(100,obj)){
			System.out.println("Centre present!");
		}
		else{
			System.out.println("No such Centre present!");
		}
	}
}