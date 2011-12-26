package dice;

import util.Node;
import util.Pool;
import util.State;

class Range extends Node{
	Node from;
	Node to;
	public Range(Node from,Node to){
		this.from = from;
		this.to = to;
	}
	public Pool visit(State state) throws Exception{
		return Pool.Range(from.visit(state).asInt(), to.visit(state).asInt());
	}
}
