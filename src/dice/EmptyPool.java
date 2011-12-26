package dice;

import util.Node;
import util.Pool;
import util.State;
class EmptyPool extends Node{
	public EmptyPool(){
		super();
	}
	public Pool visit(State state){
		return new Pool();
	}
}
