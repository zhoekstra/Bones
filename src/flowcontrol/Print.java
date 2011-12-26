package flowcontrol;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;
class Print extends Node{
	ArrayList<Object> printlist;
	private static final Node n = new Node();
	public Print(ArrayList<Object> printlist){
		this.printlist = printlist;
	}
	public Pool visit(State state) throws Exception{
		for (Object i : printlist){
			if(i.getClass().isInstance(n))
				System.out.print(((Node)i).visit(state));
			else
				System.out.print(i);
		}
		System.out.println();
		return Pool.False;
	}
}
