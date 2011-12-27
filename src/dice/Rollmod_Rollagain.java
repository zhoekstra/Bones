package dice;

import util.Node;
import util.Pool;
import util.State;

/**
 * 
 * @author zach
 *
 * 
 */
public class Rollmod_Rollagain extends Node implements Rollmod{
	Node on;
	public Rollmod_Rollagain(Node on){
		this.on = on;
	}
	public Pool visit(State state){
		return Pool.False;
	}
	@Override
	public Pool modRoll(State state, Pool roll, Pool dietype) throws Exception {
		Pool desplode_on = on.visit(state);
		Integer[] die = new Integer[dietype.size()];
		die = dietype.toArray(die);
		Pool toadd = new Pool();
		for(Integer i : roll){
			int rolled = i;
			while(desplode_on.contains(rolled)){
				rolled = die[State.rand.nextInt(die.length)];
				toadd.add(rolled);
			}
		}
		roll.addAll(toadd);
		return roll;
	}
}
