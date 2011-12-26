package expr;
import util.Node;
import util.Pool;
import util.State;

public class Bang extends Node{
	Node expr;
	public Bang(Node expr){
		this.expr = expr;
	}
	public Pool visit(State state) throws Exception{
		return expr.visit(state).asBool() ? Pool.False : Pool.True;
	}
}
