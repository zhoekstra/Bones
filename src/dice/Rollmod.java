package dice;

import util.Pool;
import util.State;

public interface Rollmod {
	public Pool modRoll(State state, Pool roll, Pool dietype) throws Exception;
}
