package handlers;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import aila.Subject;

import database.IDataHandler;
import database.XMLHandler;

import opennlp.tools.cmdline.parser.ParserTool;
import opennlp.tools.parser.Parse;
import opennlp.tools.parser.Parser;
import opennlp.tools.postag.POSTaggerME;
import utils.Logger;

public class QuestionHandler extends Handler {
	private static ArrayList<String> questionDeclarers = new ArrayList<String>(Arrays.asList("SBAR", "SBARQ", "SQ"));
	
	private String question;

	public QuestionHandler(POSTaggerME posTagger, Parser parser) {
		super(posTagger, parser);
	}
	
	public String getQuestion() {
		return question;
	}
	
	public static boolean isQuestion(Parse p) {
		if(questionDeclarers.contains(p.getType())) {
			Logger.logMessage("is question");
			return true;
		}

		Logger.logMessage("not question");
		
		return false;
	}
	
	public List<String> analyze(Parse p, boolean completeSearch) {
		question = p.getText();
		/*
		 * - typ av fråga
		 * - vad som frågas efter
		 * - vad som ska svaras med
		 */
		
		/*
		 * run POS-tagging
		 */
		System.out.println("POS-tags:");
		System.out.println(POSTag(question));
		
		/*
		 * create a tree structure of the sentence
		 */
		evaluate(question);
		
		/*
		 * interpret the question, find the parent (subject) and what to look for (associations)
		 */
		Parse parse = ParserTool.parseLine(question, parser, 1)[0].getChildren()[0];
		LinkedList<Parse> 	subjects = interpretSubject(parse),
				    		associations = interpretAssociations(parse);
		System.out.println("Subjects interpreted: " + subjects);
		System.out.println("Associations interpreted: " + associations);
		
		Subject s = new Subject(subjects.get(0).toString());
		IDataHandler dh = new XMLHandler();
		dh.retrieveSubjectData(s);
		s.getChildSubject(associations.get(0).toString());
		
		return null;
	}
	
	private LinkedList<Parse> interpretSubject(Parse p) {		
		LinkedList<Parse> subjectHolder = new LinkedList<Parse>();
		ArrayList<String> 	subjectTags = new ArrayList<String>(),
							exclude = new ArrayList<String>();
		LinkedList<Parse> result = new LinkedList<Parse>();
		if(p.getType().equals("SBAR")) {
			ArrayList<String> tags = new ArrayList<String>();
			tags.add("VP");
			subjectTags.add("NN");
			subjectTags.add("NNS");
			
			subjectHolder = search(p, tags, exclude, true);
			for(Parse vp : subjectHolder) {
				result.addAll(search(vp, subjectTags, exclude, true));
			}
		}
		else if(p.getType().equals("SQ")) {
			exclude.add("VP");
			subjectTags.add("NN");
			subjectTags.add("NNS");
			
			result.addAll(search(p, subjectTags, exclude, true));
		}
		
		return result;
	}
	
	private LinkedList<Parse> interpretAssociations(Parse p) {
		if(p.getType().equals("SBAR")) {
			ArrayList<String> tags = new ArrayList<String>(),
					exclude = new ArrayList<String>();
			tags.add("NN");
			tags.add("NNS");
			exclude.add("VP");
			
			return search(p, tags, exclude, true);
		}
		else if(p.getType().equals("SQ")) {
			LinkedList<Parse> subjectHolder = new LinkedList<Parse>();
			LinkedList<Parse> result = new LinkedList<Parse>();
			ArrayList<String> tags = new ArrayList<String>(),
								subjectTags = new ArrayList<String>(),
								exclude = new ArrayList<String>();
			tags.add("VP");
			subjectTags.add("NN");
			subjectTags.add("NNS");
			
			subjectHolder = search(p, tags, exclude, true);
			for(Parse vp : subjectHolder) {
				result.addAll(search(vp, subjectTags, exclude, true));
			}
			
			return result;
		}
		
		return null;
	}
}
