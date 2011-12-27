package dice;
import java.util.ArrayList;

import util.Node;
import util.Pool;
import util.State;
/**
 * 
 * @author zach
 * [5:d10:rollagain 10]
 * Roll Pool Constructor
 * 
 * constructs a pool with the specified number of dice of the specified dietype.
 * Also applies any specified roll mods as well.
 * 
 * The example above rolls 5d10, rolling one more d10 for every die that comes up a 10.
 */
public class Roll extends Node{
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
		Integer[] die = new Integer[diet.size()];
		die = diet.toArray(die);
		Pool result = new Pool();
		for (int i = 0; i < num; ++i)
			result.add(die[State.rand.nextInt(die.length)]);
		if (rollmodlist != null)
			for(Rollmod r: rollmodlist)
				result = r.modRoll(state,result, diet);
		return result;
	}
}
