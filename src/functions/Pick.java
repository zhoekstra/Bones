package functions;
import java.util.ArrayList;
import java.util.Collections;

import util.Node;
import util.Pool;
import util.State;
public class Pick extends Node{
	Node pool;
	Node num;
	public Pick(Node pool,Node num){
		this.pool = pool;
		this.num = num;
	}
	public Pool visit(State state) throws Exception{
		ArrayList<Integer> arr = new ArrayList<Integer>(pool.visit(state));
		Collections.shuffle(arr);
		int n = num == null ? 1 : num.visit(state).asInt();
		Pool toreturn = new Pool();
		for(int i = 0; i < n; ++i)
			toreturn.add(arr.get(i));
		return toreturn;
	}
}
