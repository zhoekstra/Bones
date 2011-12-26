package dice;

import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;
/**
 * 
 * @author zach
 * [ d6, 5, 6, [1 -> 3] ]
 * Expression based Pool Constructor
 * 
 * evaluates all the expressions and returns a pool that is the union of all expressions
 */
public class ExprPool extends Node{
	ArrayList<Node> exprlist;
	public ExprPool(ArrayList<Node> exprlist){
		this.exprlist = exprlist;
	}
	public Pool visit(State state) throws Exception{
		Pool toreturn = new Pool();
		for(Node n:exprlist){
			toreturn.addAll(n.visit(state));
		}
		return toreturn;
	}
}
