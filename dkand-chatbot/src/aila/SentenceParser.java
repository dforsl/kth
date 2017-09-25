package aila;

import java.io.IOException;

import database.IDataHandler;
import database.XMLHandler;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.List;

import opennlp.tools.cmdline.PerformanceMonitor;
import opennlp.tools.cmdline.parser.ParserTool;
import opennlp.tools.cmdline.postag.POSModelLoader;
import opennlp.tools.parser.Parse;
import opennlp.tools.parser.Parser;
import opennlp.tools.parser.ParserFactory;
import opennlp.tools.parser.ParserModel;
import opennlp.tools.postag.POSModel;
import opennlp.tools.postag.POSSample;
import opennlp.tools.postag.POSTaggerME;
import opennlp.tools.sentdetect.SentenceDetectorME;
import opennlp.tools.sentdetect.SentenceModel;
import opennlp.tools.tokenize.WhitespaceTokenizer;
import opennlp.tools.util.InvalidFormatException;


public class SentenceParser {

	private BufferedReader reader;
	
	/* 
	 * openNLP helpers
	 */
	POSModel model;
	private PerformanceMonitor perfMon;
	private POSTaggerME posTagger;
	
	public SentenceParser() {
		init();
	}
	
	public void init() {
		try {
			reader = new BufferedReader(new InputStreamReader(System.in, "UTF-8"));
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
			System.exit(0);
		}
		model = new POSModelLoader()
		.load(new File("openNLP_models/en-pos-maxent.bin"));
		
		perfMon = new PerformanceMonitor(System.err, "sent");
		
		posTagger = new POSTaggerME(model);
		
		perfMon.start();
	}
	
	
	
	/*
	 * Retrieve information from sentence
	 */
	private void RetrieveInformation(String sentence) {
		
//		if(isQuestion(sentence)) {
//			HandleQuestion(sentence);
//		}
//			
			//if(tmp[1].equals("NN") || tmp[1].equals("NNS") || tmp[1].equals("PRP"))
			//	System.out.println(s);
//			if(i < (taggedStrings.length - 1)) {
//				if(tmp[1].equals("MD") && taggedStrings[i+1].split("_")[1].equals("PRP"))
//					System.out.println("Yes I " + tmp[0]);
//			}
	}
	
//	public void interact() {
//		String input = "";
//		while(!input.equals("q")) {
//			
//			try {
//				input = reader.readLine();
//			} catch (IOException e) {
//				e.printStackTrace();
//				continue;
//			}
//			
//			
//			System.out.println("Sentence detection");
////			for(String s : SentenceDetection(input)) {
//////				s = s.replaceAll("[,]", "");
////				RetrieveInformation(s);
////			}
//			
//			
//		}
//		finish();
//	}
}
