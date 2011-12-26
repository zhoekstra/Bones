package flowcontrol;
import util.Node;
import util.Pool;
import util.State;
public class VarDecl extends Node{
	String id;
	Node expr;
	public VarDecl(String id,Node expr){
		this.id = id;
		this.expr = expr;
	}
	public Pool visit(State state) throws Exception{
		state.declareVariable(id, expr.visit(state));
		return Pool.False;
	}
}