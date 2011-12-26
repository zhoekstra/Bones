package dice;

import util.Node;
import util.Pool;
import util.State;

public class Dietypes extends Node {
	enum Die{d4,d6,d8,d10,d12,d20}
	Die d;
	public Dietypes(Die d){
		this.d = d;
	}
	public Pool visit(State state){
		switch(d){
		case d4: return Pool.d4;
		case d6: return Pool.d6;
		case d8: return Pool.d8;
		case d10: return Pool.d10;
		case d12: return Pool.d12;
		case d20: return Pool.d20;
		}
		return Pool.False;
	}
}
