package handlers;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import opennlp.tools.parser.Parse;
import opennlp.tools.parser.Parser;
import opennlp.tools.postag.POSTaggerME;
import utils.Logger;

public class StatementHandler extends Handler {
	private static ArrayList<String> statementDeclarers = new ArrayList<String>(Arrays.asList("S", "SINV"));
	
	private String statement;

	public StatementHandler(POSTaggerME posTagger, Parser parser) {
		super(posTagger, parser);
	}
	
	/**
	 * Check whether a Parse p is a statement
	 * 
	 * @param p
	 * @return boolean - statement or not
	 */
	public static boolean isStatement(Parse p) {
		if(statementDeclarers.contains(p.getType())) {
			Logger.logMessage("is statement");
			return true;
		}

		Logger.logMessage("not statement");
		
		return false;
	}

	@Override
	public List<String> analyze(Parse p, boolean completeSearch) {
		statement = p.getText();

//		Logger.logMessage("evaluating statement");
		evaluate(statement);

//		Logger.logMessage("finding statement subject");
		Parse subject = findSubject(p);
		if(subject != null) {
			System.out.println(subject.toString());
		}
		else
			Logger.logMessage("no subject found");
		
		Logger.logMessage("finding subject children");
		LinkedList<Parse> children = findSubjectChildren(p);
		for(Parse c : children) {
			System.out.println(c.toString());
		}
		
		/*
		 * quickfix
		 */
		ArrayList<String> subjects = new ArrayList<String>();
		subjects.add(subject.toString());
		for(Parse s : children) {
			subjects.add(s.toString());
		}
		
		return subjects;
	}
	
	/**
	 * Get the currently stored statement
	 * 
	 * @return
	 */
	public String getStatement() {
		return statement;
	}
	
	private Parse findSubject(Parse p) {
		Logger.logMessage("looking for PP");
		LinkedList<Parse> ps = search(p, new ArrayList<String>(Arrays.asList("PP")), null, true);
		if(!ps.isEmpty()) {
			Logger.logMessage("ps not empty");
			return search(ps.get(0), new ArrayList<String>(Arrays.asList("NN", "NNS")), null, true).get(0);
		}
		else {
			Logger.logMessage("no PP, look for nested VPs in " + p.toString());
			Parse vp = search(p, new ArrayList<String>(Arrays.asList("VP")), null, false).get(0);
			Logger.logMessage("looking for VP inside " + vp.toString());
			LinkedList<Parse> vp2 = search(vp, new ArrayList<String>(Arrays.asList("VP")), null, true);
			if(!vp2.isEmpty()) {
				Logger.logMessage("nested VPs, looking inside " + vp2.get(0).toString());
				return search(vp2.get(0), new ArrayList<String>(Arrays.asList("NN", "NNS")), null, true).get(0);
			}
			
			Logger.logMessage("no nested VPs");
			return search(p, new ArrayList<String>(Arrays.asList("NN", "NNS")), new ArrayList<String>(Arrays.asList("VP")), true).get(0);
		}
	}
	
	private LinkedList<Parse> findSubjectChildren(Parse p) {
		Logger.logMessage("looking for PP");
		LinkedList<Parse> ps = search(p, new ArrayList<String>(Arrays.asList("PP")), null, true);
		if(!ps.isEmpty()) {
			Logger.logMessage("PP exists, excluding PP");
			return search(p, new ArrayList<String>(Arrays.asList("NN", "NNS")), new ArrayList<String>(Arrays.asList("PP")), true);
		}
		else {
			Logger.logMessage("no PP, look for nested VPs");
			Parse vp = search(p, new ArrayList<String>(Arrays.asList("VP")), null, true).get(0);	
			LinkedList<Parse> vp2 = search(vp, new ArrayList<String>(Arrays.asList("VP")), null, true);
			if(!vp2.isEmpty()) {
				Logger.logMessage("nested VPs, excluding VP while looking inside " + vp.toString());
				return search(vp, new ArrayList<String>(Arrays.asList("NN", "NNS")), new ArrayList<String>(Arrays.asList("VP")), true);
			}

			Logger.logMessage("no nested VPs");
			return search(vp, new ArrayList<String>(Arrays.asList("NN", "NNS")), null, true);
		}
	}
}
