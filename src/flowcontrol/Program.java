package flowcontrol;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;

public class Program extends Node{
	Node[] stmtlist;
	public Program(Node[] stmtlist){
		this.stmtlist = stmtlist;
	}
	public Pool visit(State state) throws Exception{
		for(Node n:stmtlist)
			n.visit(state);
		return Pool.False;
	}
}
