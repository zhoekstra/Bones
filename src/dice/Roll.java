package dice;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;

class Roll extends Node{
	Node numdice;
	Node dietype;
	ArrayList<Rollmod> rollmodlist;
	public Roll(Node numdice,Node dietype,ArrayList<Rollmod> rollmodlist){
		this.numdice = numdice;
		this.dietype = dietype;
		this.rollmodlist = rollmodlist;
	}
	public Pool visit(State state) throws Exception{
		int num = numdice.visit(state).asInt();
		Pool diet = dietype.visit(state);
		Integer[] die = (Integer[])diet.toArray();
		Pool result = new Pool();
		for (int i = 0; i < num; ++i)
			result.add(die[State.rand.nextInt(die.length)]);
		for(Rollmod r: rollmodlist)
			result = r.modRoll(state,result, diet);
		return result;
	}
}
