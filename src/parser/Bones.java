package parser;

import java.io.IOException;
import java.io.StringReader;

import beaver.Parser.Exception;

import util.Node;
import util.State;

public class Bones {
	public static void main(String[] args){
		State state = new State();
		StringReader script = new StringReader(args[0]);
		BonesScanner scanner = new BonesScanner(script);
		BonesParser parser = new BonesParser();
		try {
			Node n = (Node)parser.parse(scanner);
			n.visit(state);
		} catch (IOException e) {
			System.out.println("IO Error!");
			e.printStackTrace();
		} catch (Exception e) {
			System.out.println("Parsing Error!");
			e.printStackTrace();
		} catch (java.lang.Exception e) {
			System.out.println("Runtime Error!");
			e.printStackTrace();
		}
		System.out.println("End Program");
	}
}
