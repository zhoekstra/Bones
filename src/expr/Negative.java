package expr;
import util.Node;
import util.Pool;
import util.State;
public class Negative extends Node{
	Node expr;
	public Negative(Node expr){
		this.expr = expr;
	}
	public Pool visit(State state) throws Exception{
		return new Pool(-expr.visit(state).asInt());
	}
}
