package flowcontrol;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;
import util.State.RemovedGlobalScopeException;
public class If extends Node{
	Node ifexpr;
	Node ifblock;
	Node[] elseiflist;
	Node elsen;
	public If(Node ifexpr,Node ifblock,Node[] elseiflist,Node elsen){
		this.ifexpr = ifexpr;
		this.ifblock = ifblock;
		this.elseiflist = elseiflist;
		this.elsen = elsen;
	}
	public Pool visit(State state) throws RemovedGlobalScopeException, Exception{
		if(ifexpr.visit(state).asBool()){
			state.pushStandardScope();
			ifblock.visit(state);
			state.popScope();
			return Pool.False;
		}
		if(elseiflist !=null)
			for(Node i : elseiflist)
				if(i.visit(state).asBool()) return Pool.False;
		
		if (elsen !=null){
			state.pushStandardScope();
			elsen.visit(state);
			state.popScope();
		}
		return Pool.False;
		
	}
}
