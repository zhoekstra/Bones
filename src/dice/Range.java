package dice;

import util.Node;
import util.Pool;
import util.State;
/**
 * 
 * @author zach
 * [ 10 -> 16 ]
 * Rage Pool Construction
 * 
 * Constructs a pool consisting of all the numbers from the first value to the second, inclusive.
 * the example would produce the pool [10,11,12,13,14,15,16]
 * 
 */
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
