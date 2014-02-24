/*  
 *   This file is part of the computer assignment for the
 *   Information Retrieval course at KTH.
 * 
 *   First version:  Johan Boye, 2010
 *   Second version: Johan Boye, 2012
 */  

package ir;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class PostingsEntry implements Comparable<PostingsEntry>, Serializable {
    
    public int docID;
    public double score;
    public Set<Integer> occurrences;
    
    public PostingsEntry(int docID, int score) {
    	this.docID = docID;
    	this.score = score;
    	this.occurrences = new HashSet<Integer>();
    }
    
    /**
     *  PostingsEntries are compared by their score (only relevant 
     *  in ranked retrieval).
     *
     *  The comparison is defined so that entries will be put in 
     *  descending order.
     */
    public int compareTo( PostingsEntry other ) {
    	return Double.compare(other.score, score);
    }

    /**
     * Get all occurrences of the token in the document
     * 
     * @return all occurrences
     */
    public Set<Integer> getOccurrences() {
    	return occurrences;
    }
    
    /**
     * Adds an occurrence of the token in the document
     * 
     * @param occurrence - where the word occurs
     */
    public void addOccurrence(int occurrence) {
    	occurrences.add(occurrence);
    }
    
    /**
     * Check if there is an occurrence of the word in the document at {@code occurrence}
     * 
     * @param occurrence - offset where the occurrence should be in the document
     * @return true if there is an occurrence at {@code occurrence}
     */
    public boolean occurresAt(int occurrence) {
    	return occurrences.contains(occurrence);
    }
}

    
