package flowcontrol;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;

class Block extends Node{
	ArrayList<Node> stmtlist;
	public Block(ArrayList<Node> stmtlist){
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
