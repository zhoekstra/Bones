package flowcontrol;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;
public class Print extends Node{
	ArrayList<Object> printlist;
	public Print(ArrayList<Object> printlist){
		this.printlist = printlist;
	}
	public Pool visit(State state) throws Exception{
		for (Object i : printlist){
			if(i instanceof Node)
				System.out.print(((Node)i).visit(state));
			else if(i instanceof String){
				String s = (String)i;
				s = s.substring(1, s.length()-1);
				System.out.print(s);
			}
		}
		System.out.println();
		return Pool.False;
	}
}
