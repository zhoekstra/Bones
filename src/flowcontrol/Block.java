package flowcontrol;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;

public class Block extends Node{
	Node[] stmtlist;
	public Block(Node[] stmtlist){
		this.stmtlist = stmtlist;
	}
	public Pool visit(State state) throws Exception{
		state.pushStandardScope();
		for(Node n:stmtlist)
			n.visit(state);
		state.popScope();
		return Pool.False;
	}
}
