package functions;
import java.util.ArrayList;

import util.Function;
import util.Node;
import util.Pool;
import util.State;
class CallFunc extends Node{
	String id;
	ArrayList<Node> exprlist;
	public CallFunc(String id,ArrayList<Node> exprlist){
		this.id = id;
		this.exprlist = exprlist;
	}
	public Pool visit(State state) throws Exception{
		Function func = state.getFunction(id, exprlist.size());
		state.pushFunctionScope();
		for(int i = 0; i < exprlist.size(); ++i)
			state.declareVariable(func.params.get(i), exprlist.get(i).visit(state));
		Pool toreturn = func.visit(state);
		state.popScope();
		return toreturn;
	}
}
