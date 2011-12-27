package parser;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import util.Node;
import util.State;
import beaver.Parser.Exception;

public class Bones {
	public static void main(String[] args) throws FileNotFoundException{
		State state = new State();
		FileReader script = new FileReader(args[0]);
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
