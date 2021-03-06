package util;

import java.util.Random;
import java.util.Stack;
import java.util.TreeMap;
import java.util.TreeSet;

import util.State.Scope.VariableIsConstException;
import util.State.Scope.VariableNotFoundException;

public class State {
	public final static Random rand = new Random();
	
	private Stack<Scope> _scopestack =  new Stack<Scope>();
	private Scope _globalscope = new Scope(null);
	public TreeMap<String,Function> _functiontable = new TreeMap<String,Function>();
	public State(){
		_scopestack.push(_globalscope);
	}
	public Scope pushStandardScope(){
		Scope newscope = new Scope(_scopestack.peek());
		_scopestack.push(newscope);
		return newscope;
	}
	public Scope pushFunctionScope(){
		Scope newscope = new Scope(_globalscope);
		_scopestack.push(newscope);
		return newscope;
	}
	public Scope getTopScope(){
		return _scopestack.peek();
	}
	public Scope popScope() throws RemovedGlobalScopeException{
		if (_scopestack.size() > 1)
			return _scopestack.pop();
		else throw new RemovedGlobalScopeException();
	}
	public void declareVariable(String id,Pool expr){
		_scopestack.peek().declareVar(id, expr, false);
	}
	public void declareConstVariable(String id, Pool expr){
		_scopestack.peek().declareVar(id, expr, true);
	}
	public Pool getVariable(String id) throws VariableNotFoundException{
		return _scopestack.peek().getVar(id);
	}
	public void changeVariable(String id, Pool expr) throws VariableIsConstException, VariableNotFoundException{
		_scopestack.peek().changeVar(id, expr);
	}
	
	public void addFunction(Function f) throws FunctionAlreadyExistsException{
		String key = f.name+"$$"+f.params.size();
		if(_functiontable.containsKey(key))
			throw new FunctionAlreadyExistsException(f,_functiontable.get(key));
		else
			_functiontable.put(key, f);
	}
	
	public Function getFunction(String name, int numargs) throws FunctionDoesNotExistException{
		String key = name+"$$"+numargs;
		if(_functiontable.containsKey(key))
			return _functiontable.get(key);
		else
			throw new FunctionDoesNotExistException(name,numargs);
	}
	
	
	public class Scope{
		TreeMap<String,Pool> _map = new TreeMap<String,Pool>();
		TreeSet<String> _constvars = new TreeSet<String>();
		Scope _parent;
		public Scope(Scope parentscope){_parent = parentscope;}
		
		public boolean hasVar(String id){
			return _map.containsKey(id);
		}
		public boolean existsVar(String id){
			if (hasVar(id)) return true;
			else if (_parent == null) return false;
			else return _parent.existsVar(id);
		}
		public void declareVar(String id, Pool expr, boolean isconst){
			_map.put(id, expr);
			if(isconst) _constvars.add(id);
		}
		public Pool getVar(String id) throws VariableNotFoundException{
			if (_map.containsKey(id))
				return _map.get(id);
			else if (_parent == null)
				throw new VariableNotFoundException(id);
			else
				return _parent.getVar(id);
		}
		public void changeVar(String id, Pool expr) throws VariableIsConstException, VariableNotFoundException{
			if(_map.containsKey(id)){
				if(_constvars.contains(id))
					throw new VariableIsConstException(id);
				else _map.put(id, expr);
			}
			else if (_parent == null)
				throw new VariableNotFoundException(id);
			else _parent.changeVar(id, expr);
		}
		public class VariableNotFoundException extends Exception{
			private static final long serialVersionUID = 4274331584178123786L;
			public VariableNotFoundException(String id){
				super("Variable "+id+" could not be found. Have you declared it yet?");
			}
		}
		public class VariableIsConstException extends Exception{
			private static final long serialVersionUID = 8202071370190611571L;
			public VariableIsConstException(String id){
				super("Variable "+id+" is constant - you cannot assign a new value to it!");
			}
		}	
	}
	
	public class RemovedGlobalScopeException extends Exception{
		private static final long serialVersionUID = -4226288235072920739L;
		public RemovedGlobalScopeException(){
			super("Gloal Scope was removed");
		}
	}

	public class FunctionAlreadyExistsException extends Exception{
		private static final long serialVersionUID = 4206688585433062666L;
		public FunctionAlreadyExistsException(Function tried, Function alreadyexists){
			super("Function "+alreadyexists+" cannot be overwritten by Function "+tried+". They have the same number of arguments.");
		}
		
	}
	
	public class FunctionDoesNotExistException extends Exception{
		private static final long serialVersionUID = 6667114577217294301L;
		public FunctionDoesNotExistException(String name, int numargs){
			super("Function "+name+"("+numargs+") doesn't exist yet. Have you declared it yet?");
		}
		
	}
}
