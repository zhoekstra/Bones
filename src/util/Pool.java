package util;

import java.util.Collection;
import java.util.Iterator;

import com.google.common.collect.TreeMultiset;

public class Pool implements Collection<Integer> {
	private TreeMultiset<Integer> _vals = TreeMultiset.create();
	
	public final static Pool True = new Pool(1);
	public final static Pool False = new Pool();
	public final static Pool d4 = Pool.Range(1,4);
	public final static Pool d6 = Pool.Range(1,6);
	public final static Pool d8 = Pool.Range(1,8);
	public final static Pool d10 = Pool.Range(1,10);
	public final static Pool d12 = Pool.Range(1,12);
	public final static Pool d20 = Pool.Range(1,20);

	public Pool(){}
	public Pool(int... ints){
		for(Integer i:ints)
			add(i);
	}
	public Pool(Collection<Integer>... pools){
		for (Collection<Integer> p:pools)
			addAll(p);
	}
	public static Pool Range(int from, int to){
		Pool p = new Pool();
		for (int i = from; i<=to; ++i)
			p.add(i);
		return p;
	}
	
	
	public int asInt() throws NotAnIntegerException{
		if (size() == 1) return iterator().next();
		else throw new NotAnIntegerException(this);
	}
	
	public boolean asBool(){
		return !isEmpty();
	}
	
	public String toString(){
		if(size() == 0) return "[ ]";
		else if (size() == 1) return ""+iterator().next();
		else{
			String str = "[ ";
			for (Integer i:this)
				str+=i+" ";
			str+="]";
			return str;
		}
	}
	
	@Override
	public boolean add(Integer arg0) {
		return _vals.add(arg0);
	}

	@Override
	public boolean addAll(Collection<? extends Integer> arg0) {
		return _vals.addAll(arg0);
	}

	@Override
	public void clear() {
		_vals.clear();
	}

	@Override
	public boolean contains(Object arg0) {
		return _vals.contains(arg0);
	}

	@Override
	public boolean containsAll(Collection<?> arg0) {
		return _vals.containsAll(arg0);
	}

	@Override
	public boolean isEmpty() {
		return _vals.isEmpty();
	}

	@Override
	public Iterator<Integer> iterator() {
		return _vals.iterator();
	}

	@Override
	public boolean remove(Object arg0) {
		return _vals.remove(arg0);
	}

	@Override
	public boolean removeAll(Collection<?> arg0) {
		return _vals.removeAll(arg0);
	}

	@Override
	public boolean retainAll(Collection<?> arg0) {
		return _vals.retainAll(arg0);
	}

	@Override
	public int size() {
		return _vals.size();
	}

	@Override
	public Object[] toArray() {
		return _vals.toArray();
	}

	@Override
	public <T> T[] toArray(T[] arg0) {
		return _vals.toArray(arg0);
	}
	
	@SuppressWarnings("unchecked")
	public Pool unique(){
		return new Pool(_vals.elementSet());
	}
	public class NotAnIntegerException extends Exception{
		private static final long serialVersionUID = 6160750656403258024L;
		public NotAnIntegerException(Pool p){
			super("Pool "+p+" is not an Integer");
		}
	}
}