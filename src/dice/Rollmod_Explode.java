package dice;

import util.Node;
import util.Pool;
import util.State;
/**
 * 
 * @author zach
 * explode highest(d10)
 * 
 * dice with this mod will explode on the specified numbers. If a die rolls the
 * number specified, roll the die again and add it to the original. For example,
 * [1:d6:explode 6] will roll 1d6. If it rolls a 6, roll it again and add it to
 * the original. So [1:d6:explode 6] may roll 6 - 6 - 4 and return a result of [16].
 * 
 */
public class Rollmod_Explode extends Node implements Rollmod{
	Node on;
	public Rollmod_Explode(Node on){
		this.on = on;
	}
	public Pool visit(State state){
		return Pool.False;
	}
	@Override
	public Pool modRoll(State state, Pool roll, Pool dietype) throws Exception {
		Pool desplode_on = on.visit(state);
		Integer[] die = (Integer[])dietype.toArray();
		Pool toadd = new Pool();
		Pool toremove = new Pool();
		for(Integer i : roll)
			if(desplode_on.contains(i)){
				toremove.add(i);
				int rolled = i;
				int total = i;
				do{
					rolled = die[State.rand.nextInt(die.length)];
					total += rolled;
				}while(desplode_on.contains(rolled));
				toadd.add(total);
			}
		roll.removeAll(toremove);
		roll.addAll(toadd);
		return roll;
	}
}
