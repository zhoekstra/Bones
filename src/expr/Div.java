package expr;
import util.Node;
import util.Pool;
import util.State;
class Div extends Node{
	Node lhe;
	Node rhe;
	public Div(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	public Pool visit(State state) throws Exception{
		return new Pool( lhe.visit(state).asInt() / rhe.visit(state).asInt());
	}
}
