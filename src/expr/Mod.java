package expr;
import util.Node;
import util.Pool;
import util.State;
public class Mod extends Node{
	Node lhe;
	Node rhe;
	public Mod(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	public Pool visit(State state) throws Exception{
		return new Pool(lhe.visit(state).asInt() % rhe.visit(state).asInt());
	}
}
