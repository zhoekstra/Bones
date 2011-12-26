package expr;
import util.Node;
import util.Pool;
import util.State;
class IntLit extends Node{
	String val;
	public IntLit(String val){
		this.val = val;
	}
	public Pool visit(State state){
		return new Pool(Integer.parseInt(val));
	}
}
