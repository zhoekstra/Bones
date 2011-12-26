package functions;
import java.util.ArrayList;

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
	public Pool visit(State state){
	}
}
