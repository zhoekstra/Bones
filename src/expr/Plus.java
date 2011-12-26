package expr;
import util.Node;
import util.Pool;
import util.State;
public class Plus extends Node{
	Node lhe;
	Node rhe;
	public Plus(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	public Pool visit(State state) throws Exception{
		return new Pool(lhe.visit(state).asInt() + rhe.visit(state).asInt());
	}
}
