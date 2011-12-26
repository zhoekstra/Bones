package flowcontrol;
import util.Node;
import util.Pool;
import util.State;
class ConstVarDecl extends Node{
	String id;
	Node expr;
	public ConstVarDecl(String id,Node expr){
		this.id = id;
		this.expr = expr;
	}
	public Pool visit(State state) throws Exception{
		state.declareConstVariable(id, expr.visit(state));
		return Pool.False;
	}
}
