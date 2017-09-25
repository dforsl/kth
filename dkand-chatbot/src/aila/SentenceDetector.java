package aila;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import opennlp.tools.sentdetect.SentenceDetectorME;
import opennlp.tools.sentdetect.SentenceModel;

public class SentenceDetector {
	
	private static SentenceDetectorME sentenceDetector;
    
    public static void init() {
    	
        SentenceModel model = null;
        try {
        	InputStream modelIn = new FileInputStream("openNLP_models/en-sent.bin");
        	model = new SentenceModel(modelIn);  
        }
        catch (IOException e) {
          e.printStackTrace();
        }
        
        sentenceDetector = new SentenceDetectorME(model);
    }
    
    public static String[] detect(String input) {
    	return sentenceDetector != null ? sentenceDetector.sentDetect(input) : null;
    }
}