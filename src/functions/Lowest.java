package functions;
import java.util.Arrays;

import util.Node;
import util.Pool;
import util.State;
public class Lowest extends Node{
	Node pool;
	Node num;
	public Lowest(Node pool,Node num){
		this.pool = pool;
		this.num = num;
	}
	public Pool visit(State state) throws Exception{
		Pool toreturn = new Pool();
		Integer[] arr = (Integer[])pool.visit(state).toArray();
		Arrays.sort(arr);
		int n = num == null ? 1 : num.visit(state).asInt();
		for(int i = 0; i < n; ++i)
			toreturn.add(i);
		return toreturn;
	}
}
