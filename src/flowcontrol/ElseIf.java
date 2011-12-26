package flowcontrol;
import util.Node;
import util.Pool;
import util.State;
import util.State.RemovedGlobalScopeException;
class ElseIf extends Node{
	Node ifexpr;
	Node ifblock;
	public ElseIf(Node ifexpr,Node ifblock){
		this.ifexpr = ifexpr;
		this.ifblock = ifblock;
	}
	public Pool visit(State state) throws RemovedGlobalScopeException, Exception{
		if(ifexpr.visit(state).asBool()){
			state.pushStandardScope();
			ifblock.visit(state);
			state.popScope();
			return Pool.True;
		}
		else return Pool.False;
	}
}
