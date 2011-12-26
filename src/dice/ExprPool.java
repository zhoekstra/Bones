package dice;

import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;

class ExprPool extends Node{
	ArrayList<Node> exprlist;
	public ExprPool(ArrayList<Node> exprlist){
		this.exprlist = exprlist;
	}
	public Pool visit(State state) throws Exception{
		Pool toreturn = new Pool();
		for(Node n:exprlist){
			toreturn.addAll(n.visit(state));
		}
		return toreturn;
	}
}
