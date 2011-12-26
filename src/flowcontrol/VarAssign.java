package flowcontrol;
import util.Node;
import util.Pool;
import util.State;
import util.State.Scope.VariableIsConstException;
import util.State.Scope.VariableNotFoundException;
public class VarAssign extends Node{
	String id;
	Node expr;
	public VarAssign(String id,Node expr){
		this.id = id;
		this.expr = expr;
	}
	public Pool visit(State state) throws VariableIsConstException, VariableNotFoundException, Exception{
		state.changeVariable(id,expr.visit(state));
		return Pool.False;
	}
}
