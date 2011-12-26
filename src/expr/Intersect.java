package expr;
import util.Node;
import util.Pool;
import util.State;
class Intersect extends Node{
	Node lhe;
	Node rhe;
	public Intersect(Node lhe,Node rhe){
		this.lhe = lhe;
		this.rhe = rhe;
	}
	@SuppressWarnings("unchecked")
	public Pool visit(State state) throws Exception{
		Pool toreturn = new Pool(lhe.visit(state));
		toreturn.retainAll(rhe.visit(state));
		return toreturn;
	}
}
