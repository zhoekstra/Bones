package functions;
import java.util.ArrayList;

import util.Function;
import util.Node;
import util.Pool;
import util.State;

class FuncDecl extends Node{
	String id;
	ArrayList<String> paramlist;
	ArrayList<Node> stmtlst;
	Node returnexpr;
	public FuncDecl(String id,ArrayList<String> paramlist,ArrayList<Node> stmtlst,Node returnexpr){
		this.id = id;
		this.paramlist = paramlist;
		this.stmtlst = stmtlst;
		this.returnexpr = returnexpr;
	}
	public Pool visit(State state) throws Exception{
		Function func = new Function(id,paramlist,stmtlst,returnexpr);
		state.addFunction(func);
		return Pool.False;
	}
}
