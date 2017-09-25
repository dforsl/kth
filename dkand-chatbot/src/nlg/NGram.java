package nlg;

import java.util.HashMap;

public class NGram {
	private HashMap<String, NGram> words;	
	private int nrOfOccurrences;
	
	public NGram() {
		nrOfOccurrences = 0;
		words = new HashMap<String, NGram>();
	}
	
	public int getNrOfOccurrences() {
		return nrOfOccurrences;
	}
	
	public void increaseNrOccurrences() {
		this.nrOfOccurrences++;
	}
	
	/**
	 * Get the NGram, create if not already exists
	 * @param word
	 */
	public NGram get(String word) {
		if(!words.containsKey(word)) {
			words.put(word, new NGram());
		}
		return words.get(word);
	}
	
	/**
	 * put a new word and increase occurrence
	 * @param word
	 */
	public void put(String word) {
		if(!words.containsKey(word)) {
			words.put(word, new NGram());
		}
		words.get(word).increaseNrOccurrences();
	}
	
	public HashMap<String, NGram> getWords() {
		return words;
	}
}
