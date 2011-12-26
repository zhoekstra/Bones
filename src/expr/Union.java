package expr;
import util.Node;
import util.Pool;
import util.State;

class Union extends Node{
	Node lhe;
	Node rhe;
	public Union(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	@SuppressWarnings("unchecked")
	public Pool visit(State state) throws Exception{
		return new Pool(lhe.visit(state), rhe.visit(state));
	}
}
