package nlg;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import twitter4j.Status;

public class TweetParser {
	
	private NGram ngram, rngram;
	
	public TweetParser() {
		ngram = new NGram();
		rngram = new NGram();
	}
	
	public void parseTweets(List<Status> tweets) {

		for(Status tweet : tweets) {
			String[] words = tweet.getText().toLowerCase().replaceAll("[^a-zA-Z\\s#@]+", "").split(" ");
			for(int i = 0; i < words.length - 2; i++) {
				if(words[i+2].isEmpty() || words[i+2].startsWith("#") || words[i+2].startsWith("@"))
					continue;
				
				ngram.get(words[i]).get(words[i+1]).put(words[i+2]);
			}
			for(int i = words.length - 1; i > 1; i--) {
				if(words[i-2].isEmpty() || words[i-2].startsWith("#") || words[i-2].startsWith("@"))
					continue;
				
				rngram.get(words[i]).get(words[i-1]).put(words[i-2]);
			}
		}
	}
	
	public void generateSentence(String first, String second) {
		int highestOccurrences = 0;
		String bestWord = "";
		String a = first, b = second;
		String sentence1 = a + " " + b;
		String sentence2 = a + " " + b;
		
		while(true) {
			bestWord = null;
			HashMap<String, NGram> suggestions = rngram.get(b).get(a).getWords();
			for(String s : suggestions.keySet()) {

				if(suggestions.get(s).getNrOfOccurrences() > highestOccurrences) {
					highestOccurrences = suggestions.get(s).getNrOfOccurrences();
					bestWord = s;
				}
			}
			
			if(bestWord == null || sentence1.contains(bestWord + " " + a + " " + b))
				break;
			
			sentence1 = bestWord + " " + sentence1;
			b = a;
			a = bestWord;
			highestOccurrences = 0;
		}
		
		a = first;
		b = second;
		highestOccurrences = 0;
		bestWord = "";
		while(true) {
			bestWord = null;
			HashMap<String, NGram> suggestions = ngram.get(a).get(b).getWords();
			for(String s : suggestions.keySet()) {

				if(suggestions.get(s).getNrOfOccurrences() > highestOccurrences) {
					highestOccurrences = suggestions.get(s).getNrOfOccurrences();
					bestWord = s;
				}
			}
			
			if(bestWord == null || sentence2.contains(a + " " + b + " " + bestWord))
				break;
			
			sentence2 += " " + bestWord;
			a = b;
			b = bestWord;
			highestOccurrences = 0;
		}
		System.out.println(sentence1);
		System.out.println(sentence2);
	}
	
//	public static void main(String[] args) {
//		TweetParser parser = new TweetParser();
//		
//		List<String> list = new ArrayList<String>();
//
//		list.add("Hello my name is Christoffer");
//		list.add("Do you know who I am");
//		list.add("Hello my name has many characters");
//		list.add("Good bye my name has one character");
//		
//		parser.parseTweets(list);
//		parser.generateSentence("do", "you");
//	}
}
