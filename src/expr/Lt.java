package expr;
import util.Node;
import util.Pool;
import util.State;
public class Lt extends Node{
	Node lhe;
	Node rhe;
	public Lt(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	public Pool visit(State state) throws Exception{
		return lhe.visit(state).asInt() < rhe.visit(state).asInt() ? Pool.True : Pool.False;
	}
}
