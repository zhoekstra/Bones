package functions;
import java.util.Scanner;

import util.Node;
import util.Pool;
import util.State;
public class Input extends Node{
	String s;
	Scanner scan = new Scanner(System.in);
	public Input(String s){
		this.s = s;
	}
	public Pool visit(State state){
		if(s != null)
			System.out.println(s);
		Pool p = new Pool();
		while(scan.hasNextInt())
			p.add(scan.nextInt());
		return p;
	}
}
