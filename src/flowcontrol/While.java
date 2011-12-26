package flowcontrol;
import util.Node;
import util.Pool;
import util.State;
class While extends Node{
	Node whileexpr;
	Node whileblock;
	public While(Node whileexpr,Node whileblock){
		this.whileexpr = whileexpr;
		this.whileblock = whileblock;
	}
	public Pool visit(State state) throws Exception{
		state.pushStandardScope();
		while(whileexpr.visit(state).asBool())
			whileblock.visit(state);
		state.popScope();
		return Pool.False;
	}
}
