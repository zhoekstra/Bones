package flowcontrol;
import util.Node;
import util.Pool;
import util.State;
public class Else extends Node{
	Node elseblock;
	public Else(Node elseblock){
		this.elseblock = elseblock;
	}
	public Pool visit(State state) throws Exception{
		state.pushStandardScope();
		elseblock.visit(state);
		state.popScope();
		return Pool.False;
	}
}
