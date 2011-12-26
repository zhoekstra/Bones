package expr;
import util.Node;
import util.Pool;
import util.State;
class Complement extends Node{
	Node lhe;
	Node rhe;
	public Complement(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	public Pool visit(State state) throws Exception{
		Pool toreturn = lhe.visit(state);
		toreturn.removeAll(rhe.visit(state));
		return toreturn;
	}
}
