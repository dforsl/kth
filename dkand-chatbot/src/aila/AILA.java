package aila;

import handlers.QuestionHandler;
import handlers.StatementHandler;
import handlers.TweetHandler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;

import nlg.TweetParser;

import database.TwitterClient;

import opennlp.tools.cmdline.PerformanceMonitor;
import opennlp.tools.cmdline.parser.ParserTool;
import opennlp.tools.cmdline.postag.POSModelLoader;
import opennlp.tools.parser.Parse;
import opennlp.tools.parser.Parser;
import opennlp.tools.parser.ParserFactory;
import opennlp.tools.parser.ParserModel;
import opennlp.tools.postag.POSModel;
import opennlp.tools.postag.POSTaggerME;
import simplenlg.framework.NLGFactory;
import simplenlg.lexicon.Lexicon;
import simplenlg.phrasespec.SPhraseSpec;
import simplenlg.realiser.english.Realiser;
import twitter4j.QueryResult;
import twitter4j.Status;
import utils.Logger;
import utils.Utils;

/**
 * 
 * 	This is the base for the Artificial Intelligent Learning Agent A.I.L.A
 * 
 * @author daniel forslund, christoffer gunning
 *
 */

public class AILA {
	private BufferedReader reader;
	
	private QuestionHandler questionHandler;
	private StatementHandler statementHandler;
	private TweetHandler tweetHandler;
	
	private TwitterClient twitterClient;
	
	/* 
	 * openNLP helpers
	 */
	private POSModel model;
	private PerformanceMonitor perfMon;
	private POSTaggerME posTagger;
	private Parser parser;
	
	public AILA() {
		try {
			reader = new BufferedReader(new InputStreamReader(System.in, "UTF-8"));
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
			System.exit(0);
		}
	}
	
	public void init() {
		/*
		 * init the logger
		 */
		Logger.setStatus(Logger.Status.PRINT);
		
		model = new POSModelLoader()
		.load(new File("openNLP_models/en-pos-maxent.bin"));
		
		perfMon = new PerformanceMonitor(System.err, "sent");
		
		posTagger = new POSTaggerME(model);
		
		perfMon.start();
		
		/*
		 * load the sentence parser
		 */
		try {
			InputStream is = new FileInputStream("openNLP_models/en-parser-chunking.bin");
			 
			ParserModel model = new ParserModel(is);
	 
			parser = ParserFactory.create(model);

			is.close();
		} catch (Exception e) {
			Logger.logError("Error whilst initializing openNLP", e);
			System.exit(0);
		}
		
		/* create a QuestionHandler */
		questionHandler = new QuestionHandler(posTagger, parser);
		
		/* create a StatementHandler */
		statementHandler = new StatementHandler(posTagger, parser);
		
		/* create a tweet handler */
		tweetHandler = new TweetHandler(posTagger, parser);
		
		/* create a twitter client */
		twitterClient = new TwitterClient();
		
		/* init the sentence detector */
		SentenceDetector.init();
		
		Logger.logMessage("Init complete!");
	}
	
	public void interact() {
		String input;
		//run forever
		while(true) {
			//get user input
			try {
				input = reader.readLine();
			} catch (IOException e) {
				Logger.logError("Error whilst reading user input.", e);
				continue;
			}
			
			//detect sentences
			String[] sentences = SentenceDetector.detect(input);
			
			//parse the sentences using openNLP
			Parse[] parses = new Parse[sentences.length];
			for(int i = 0; i < sentences.length; i++) {
				parses[i] = ParserTool.parseLine(sentences[i], parser, 1)[0].getChildren()[0];
			}
			
			
			
			//analyze the user's input
			ArrayList<String> subjects = new ArrayList<String>();
			ArrayList<String> theSubjects = new ArrayList<String>();
			for(Parse p : parses) {
				subjects.addAll(tweetHandler.analyze(p, true));
				theSubjects.addAll(tweetHandler.analyze(p, false));
			}
			
			System.out.println(subjects.toString());
			
			//HashMap for regularly occurring subjects
			HashMap<String, Integer> subjectResults = new HashMap<String, Integer>();
			HashMap<String, Integer> beforeSubject = new HashMap<String, Integer>();
			HashMap<String, Integer> afterSubject = new HashMap<String, Integer>();
			
			//search for the tweets matching the found subjects
			ArrayList<Status> tweets = new ArrayList<Status>();
			for(String subject : subjects) {
				ArrayList<String> s = new ArrayList<String>(Arrays.asList(subject));
				tweets.addAll(twitterOccurancesSearch(s, subjectResults));
			}
			
			findSearchWord(theSubjects.get(0), tweets, beforeSubject, afterSubject);
			
			tweets.addAll(twitterOccurancesSearch(subjects, subjectResults));
			
			System.out.println("Occurences result");
		    LinkedHashMap<String, Integer> sortedResults = Utils.sortHashMapByValues(subjectResults);
		    LinkedHashMap<String, Integer> sortedBefore = Utils.sortHashMapByValues(beforeSubject);
		    LinkedHashMap<String, Integer> sortedAfter = Utils.sortHashMapByValues(afterSubject);
		    for(String s : sortedResults.keySet()) {
		    	System.out.println(s + " : " + sortedResults.get(s));
		    }
		    
			TweetParser parser = new TweetParser();
			
			String bestBeforeWord = "", bestAfterWord = "";
			int bestBeforeOccurrence = 0, bestAfterOccurrence = 0;
			
		    for(String s : sortedBefore.keySet()) {
		    	bestBeforeWord = s;
		    	bestBeforeOccurrence = sortedBefore.get(s);
		    }
		    
		    for(String s : sortedAfter.keySet()) {
		    	bestAfterWord = s;
		    	bestAfterOccurrence = sortedAfter.get(s);
		    }

			parser.parseTweets(tweets);
		    
		    
		    if(bestBeforeOccurrence > bestAfterOccurrence) {
		    	System.out.println("Searching for: " + bestBeforeWord + " " + theSubjects.get(0));
				parser.generateSentence(bestBeforeWord, theSubjects.get(0));
		    } else {
		    	System.out.println("Searching for: " + theSubjects.get(0) + " " + bestAfterWord);
				parser.generateSentence(theSubjects.get(0), bestAfterWord);
		    }
		}
	}
	
	private void findSearchWord(String subject, ArrayList<Status> tweets, HashMap<String, Integer> beforeSubject, HashMap<String, Integer> afterSubject) {
		System.out.println("Finding word for: " + subject);
		for(Status tweet : tweets) {
			String[] words = tweet.getText().toLowerCase().replaceAll("[^a-zA-Z\\s#@]+", "").split(" ");
			for(int i = 0; i < words.length; i++) {
				if(words[i].equals(subject)) {
					String before, after;
					if(i != 0) {
						before = words[i - 1];
						if(!beforeSubject.containsKey(before)) {
							beforeSubject.put(before, 0);
						} else {
							int value = beforeSubject.get(before) + 1;
							beforeSubject.put(before, value);
						}
					}
					
					if(i != words.length - 1) {
						after = words[i + 1];
						if(!afterSubject.containsKey(after)) {
							afterSubject.put(after, 0);
						} else {
							int value = afterSubject.get(after) + 1;
							afterSubject.put(after, value);
						}
					}
				}
			}
		}
		
	}

	private List<Status> twitterOccurancesSearch(ArrayList<String> subjects, HashMap<String, Integer> result) {
		QueryResult qResult = twitterClient.search(subjects);
		System.out.println(qResult.getTweets().size() + " tweets found");
	    for (Status status : qResult.getTweets()) {
//	    	System.out.println();
//	    	System.out.println("Tweet by @" + status.getUser().getScreenName());
//	        System.out.println(status.getText());
//	        System.out.println("NLP gives:");
	        Parse p = ParserTool.parseLine(status.getText(), parser, 1)[0].getChildren()[0];
	        List<String> ss = tweetHandler.analyze(p, true);
//	        System.out.println(ss.toString());
//	        System.out.println();
	        
	        for(String s : ss) {
	        	if(result.containsKey(s)) {
	        		result.put(s, (result.get(s) + 1));
	        	} else {
	        		result.put(s, 1);
	        	}
	        }
	    }
	    
	    return qResult.getTweets();
	}
	
	public void finish() {
		perfMon.stopAndPrintFinalResult();
	}
	
	public static void main(String[] args) {
		AILA aila = new AILA();
		aila.init();
		aila.interact();
		aila.finish();
		
//		SentenceParser p = new SentenceParser();
//		p.interact();
	}
}
