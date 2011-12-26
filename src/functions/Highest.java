package functions;
import java.util.Arrays;

import util.Node;
import util.Pool;
import util.State;
public class Highest extends Node{
	Node pool;
	Node num;
	public Highest(Node pool,Node num){
		this.pool = pool;
		this.num = num;
	}
	public Pool visit(State state) throws Exception{
		Pool tocheck = pool.visit(state);
		Integer[] arr = (Integer[])tocheck.toArray();
		Arrays.sort(arr);
		int n = num == null ? 1 : num.visit(state).asInt();
		Pool toreturn = new Pool();
		for(int i = arr.length-1, j = 0; j < n; j++,i-- )
			toreturn.add(arr[i]);
		return toreturn;
	}
}
