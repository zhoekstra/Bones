package functions;
import util.Node;
import util.Pool;
import util.State;
public class Sum extends Node{
	Node pool;
	public Sum(Node pool){
		this.pool = pool;
	}
	public Pool visit(State state) throws Exception{
		Pool p = pool.visit(state);
		int sum = 0;
		for(Integer i : p)
			sum+=i;
		return new Pool(sum);
	}
}
