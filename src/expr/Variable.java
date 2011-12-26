package expr;
import util.Node;
import util.Pool;
import util.State;
import util.State.Scope.VariableNotFoundException;
public class Variable extends Node{
	String id;
	public Variable(String id){
		this.id = id;
	}
	public Pool visit(State state) throws VariableNotFoundException{
		return state.getVariable(id);
	}
}
