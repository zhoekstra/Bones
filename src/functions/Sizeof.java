package functions;
import util.Node;
import util.Pool;
import util.State;
public class Sizeof extends Node{
	Node pool;
	public Sizeof(Node pool){
		this.pool = pool;
	}
	public Pool visit(State state) throws Exception{
		return new Pool(pool.visit(state).size());
	}
}
