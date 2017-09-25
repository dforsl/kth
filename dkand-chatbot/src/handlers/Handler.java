package handlers;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import opennlp.tools.cmdline.parser.ParserTool;
import opennlp.tools.parser.Parse;
import opennlp.tools.parser.Parser;
import opennlp.tools.postag.POSSample;
import opennlp.tools.postag.POSTaggerME;
import opennlp.tools.sentdetect.SentenceDetectorME;
import opennlp.tools.sentdetect.SentenceModel;
import opennlp.tools.tokenize.WhitespaceTokenizer;
import opennlp.tools.util.InvalidFormatException;

public abstract class Handler {
	protected POSTaggerME posTagger;
	protected Parser parser;
	
	protected Handler(POSTaggerME posTagger, Parser parser) {
		this.posTagger = posTagger;
		this.parser = parser;
	}
	
	protected abstract List<String> analyze(Parse p, boolean completeSearch);
	
	/**
	 * create POS-tags for a sentence
	 * 
	 * @param text - String - sentence to tag
	 * @return the tagged sentence
	 */
	protected String POSTag(String text) {
		
		String whitespaceTokenizerLine[] = WhitespaceTokenizer.INSTANCE
				.tokenize(text);
		String[] tags = posTagger.tag(whitespaceTokenizerLine);

		POSSample sample = new POSSample(whitespaceTokenizerLine, tags);

//		perfMon.incrementCounter();
		
		return sample.toString();
	}	
	
	/**
	 * detects sentences in given input
	 * 
	 * @param input - the input string
	 * @return a String array of the sentences
	 */
	protected String[] sentenceDetection(String input) {
		InputStream modelIn = null;
		try {
			modelIn = new FileInputStream("openNLP_models/en-sent.bin");
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}
		
        SentenceModel model = null;
        try {
           model = new SentenceModel(modelIn);  
        }
        catch (IOException e) {
          e.printStackTrace();
        }
        finally {
          if (modelIn != null) {
            try {
              modelIn.close();
            }
            catch (IOException e) {
            }
          }
        }
        
        SentenceDetectorME sentenceDetector = new SentenceDetectorME(model);
        String sentences[] = sentenceDetector.sentDetect(input);
          
        return sentences;
    }	
	
	/**
	 * get nouns and associations?
	 * 
	 * @param sentence
	 */
	protected void getNouns(String sentence) {
		String tagged = POSTag(sentence);
		System.out.println(tagged);
		String[] taggedStrings = tagged.split("[ ]");
		System.out.println("Important parts?");
		for(int i = 0; i < taggedStrings.length; i++) {
			String[] tmp = taggedStrings[i].split("_");
			
			if(tmp[1].equals("NN") || tmp[1].equals("NNP") || tmp[1].equals("NNS")) {
				System.out.println("there is somethin' about " + tmp[0]);
				
				int j = i-1;
				while(j >= 0) {
					String[] tmp2 = taggedStrings[j].split("_");
					if(!(tmp2[1].equals("JJ") || tmp2[1].equals("CC"))) 
						break;
					if(tmp2[1].equals("JJ"))
						System.out.println("it is " + taggedStrings[j].split("_")[0]);
					j--;
				}
				
				j = i+1;
				while(j < taggedStrings.length) {
					String[] tmp2 = taggedStrings[j].split("_");
					if(!(tmp2[1].equals("JJ") || tmp2[1].equals("CC") || tmp2[1].equals("WDT") || tmp2[1].equals("VBZ"))) 
						break;
					if(tmp2[1].equals("JJ"))
						System.out.println("it is " + taggedStrings[j].split("_")[0]);
					j++;
				}
			}
		}	
	}
	
	/**
	 * creates a relational tree of the words in a given sentence
	 * 
	 * @param text
	 * @throws InvalidFormatException
	 * @throws IOException
	 */
	public void evaluate(String text) {
		Parse topParses[] = ParserTool.parseLine(text, parser, 1);
 
		for (Parse p : topParses) {
			System.out.println(p.getChildCount() + " children");
			p.show();				
//			p.showCodeTree();
		}
	}
	
	/**
	 * find parses by certain tags within a parse, with the possibility of excluding
	 * 
	 * @param p
	 * @param tags
	 * @param exclude
	 * @return
	 */
	protected LinkedList<Parse> search(Parse p, ArrayList<String> tags, ArrayList<String> exclude, boolean fulhack) {
		LinkedList<Parse> result = new LinkedList<Parse>();
		
		if(tags.contains(p.getType()) && !fulhack) {
			result.add(p);
			return result;
		}
		
		for(Parse c : p.getChildren()) {
			if(exclude != null && exclude.contains(c.getType()))
				continue;
			
			LinkedList<Parse> partialRes = search(c, tags, exclude, false);
			result.addAll(partialRes);
		}
		
		return result;
	}
}
