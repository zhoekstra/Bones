package functions;

import util.Node;
import util.Pool;
import util.State;

public class Unique extends Node {
	Node expr;
	public Unique(Node e){
		expr = e;
	}
	public Pool visit(State state) throws Exception{
		return expr.visit(state).unique();
	}

}
