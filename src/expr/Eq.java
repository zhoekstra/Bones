package expr;
import util.Node;
import util.Pool;
import util.State;
class Eq extends Node{
	Node lhe;
	Node rhe;
	public Eq(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	public Pool visit(State state) throws Exception{
		return lhe.visit(state).equals(rhe.visit(state)) ? Pool.True : Pool.False;
	}
}
