package functions;
import util.Node;
import util.Pool;
import util.State;
public class Gt extends Node{
	Node pool;
	Node val;
	public Gt(Node pool,Node val){
		this.pool = pool;
		this.val = val;
	}
	public Pool visit(State state) throws Exception{
		Pool p = pool.visit(state);
		int tocheck = val.visit(state).asInt();
		int total = 0;
		for (Integer i:p)
			if(i > tocheck) total++;
		return new Pool(total);
	}
}
