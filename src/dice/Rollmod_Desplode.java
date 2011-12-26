package dice;

import util.Node;
import util.Pool;
import util.State;

class Rollmod_Desplode extends Node implements Rollmod{
	Node on;
	public Rollmod_Desplode(Node on){
		this.on = on;
	}
	public Pool visit(State state){return Pool.False;}
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
					total -= rolled;
				}while(desplode_on.contains(rolled));
				toadd.add(total);
			}
		roll.removeAll(toremove);
		roll.addAll(toadd);
		return roll;
	}
}
