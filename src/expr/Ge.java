package expr;
import util.Node;
import util.Pool;
import util.State;
class Ge extends Node{
	Node lhe;
	Node rhe;
	public Ge(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	public Pool visit(State state) throws Exception{
		return lhe.visit(state).asInt() >= rhe.visit(state).asInt() ? Pool.True : Pool.False;
	}
}
