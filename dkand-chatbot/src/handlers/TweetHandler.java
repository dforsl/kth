package handlers;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import opennlp.tools.parser.Parse;
import opennlp.tools.parser.Parser;
import opennlp.tools.postag.POSTaggerME;
import utils.Logger;

public class TweetHandler extends Handler {
	private String statement;	
	
	public TweetHandler(POSTaggerME posTagger, Parser parser) {
		super(posTagger, parser);
	}

	@Override
	public List<String> analyze(Parse p, boolean completeSearch) {
		statement = p.getText();

//		Logger.logMessage("Evaluating statement");
		evaluate(statement);

//		Logger.logMessage("Finding statement subjects");
		LinkedList<Parse> subjectParses;
		if(completeSearch)
			subjectParses = simpleSubjectSearch(p);
		else {
			subjectParses = findSubject(p);
			if(subjectParses.isEmpty())
				subjectParses = simpleSubjectSearch(p);
		}
		
		/*
		 * create the list to return
		 */
		ArrayList<String> subjects = new ArrayList<String>();
		for(Parse sp : subjectParses) {
			subjects.add(sp.toString().toLowerCase().replaceAll("[^a-zA-Z0-9]+", ""));
		}
		
		return subjects;
	}
	
	private LinkedList<Parse> simpleSubjectSearch(Parse p) {
		return search(p, new ArrayList<String>(Arrays.asList("NN", "NNS", "NNP", "NNPS")), null, true);		
	}
	
	private LinkedList<Parse> findSubject(Parse p) {
		Logger.logMessage("looking for PP");
		
		LinkedList<Parse> ps = search(p, new ArrayList<String>(Arrays.asList("PP")), null, true);
		if(!ps.isEmpty()) {
			Logger.logMessage("ps not empty");
			return search(ps.get(0), new ArrayList<String>(Arrays.asList("NN", "NNS")), null, true);
		}
		else {
			Logger.logMessage("no PP, look for nested VPs in " + p.toString());
			LinkedList<Parse> res = search(p, new ArrayList<String>(Arrays.asList("VP")), null, false);
			if(res.isEmpty())
				return new LinkedList<Parse>();

			Parse vp = res.get(0);
			
			Logger.logMessage("looking for VP inside " + vp.toString());
			LinkedList<Parse> vp2 = search(vp, new ArrayList<String>(Arrays.asList("VP")), null, true);
			if(!vp2.isEmpty()) {
				Logger.logMessage("nested VPs, looking inside " + vp2.get(0).toString());
				return search(vp2.get(0), new ArrayList<String>(Arrays.asList("NN", "NNS")), null, true);
			}
			
			Logger.logMessage("no nested VPs");
			return search(p, new ArrayList<String>(Arrays.asList("NN", "NNS")), new ArrayList<String>(Arrays.asList("VP")), true);
		}
	}
}
