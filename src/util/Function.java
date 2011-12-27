package util;

import java.util.ArrayList;

public class Function extends Node {
	public final String name;
	public final ArrayList<String> params;
	Node[] stmts;
	Node returnval;
	
	public Function(String name, ArrayList<String> params, Node[] stmts, Node returnval){
		this.name = name;
		this.params = params;
		this.stmts = stmts;
		this.returnval = returnval;
	}
	
	public Pool visit(State state) throws Exception{
		for(Node n : stmts)
			n.visit(state);
		if(returnval !=null)
			return returnval.visit(state);
		else return Pool.False;
	}
}
