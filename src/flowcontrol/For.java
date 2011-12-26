package flowcontrol;
import util.Node;
import util.Pool;
import util.State;
class For extends Node{
	String id;
	Node forexpr;
	Node forblock;
	public For(String id,Node forexpr,Node forblock){
		this.id = id;
		this.forexpr = forexpr;
		this.forblock = forblock;
	}
	public Pool visit(State state) throws Exception{
		Pool loopover = forexpr.visit(state);
		state.pushStandardScope();
		state.declareVariable(id,Pool.False);
		for(Integer i:loopover){
			state.changeVariable(id,new Pool(i));
			forblock.visit(state);
		}
		state.popScope();
		return Pool.False;
	}
}
