/*  
 *   This file is part of the computer assignment for the
 *   Information Retrieval course at KTH.
 * 
 *   First version:  Johan Boye, 2010
 *   Second version: Johan Boye, 2012
 */  

package ir;

import java.util.LinkedList;
import java.util.Set;
import java.io.Serializable;

/**
 *   A list of postings for a given word.
 */
public class PostingsList implements Comparable<PostingsList>, Serializable {
    
    /** The postings list as a linked list. */
    private LinkedList<PostingsEntry> list = new LinkedList<PostingsEntry>();

    public PostingsList() {
    	
    }

    /**  Number of postings in this list  */
    public int size() {
    	return list.size();
    }

    /**  Returns the ith posting */
    public PostingsEntry get(int i) {
    	return list.get(i);
    }

    /**
     * Adds an occurrence at {@code offset} in {@code docID} to the corresponding {@code PostingsEntry}.
     * 
     * If no matching {@code PostingsEntry} exists, a new one is created.
     * 
     * @param docID - id of the document in which the occurrence is
     * @param offset - offset of the occurrence from start
     */
    public void add(int docID, int offset) {
    	PostingsEntry entry = null;
    	int index = 0;
    	
    	if(!list.isEmpty() && list.getLast().docID <= docID) {
    		if(list.getLast().docID == docID) {
    			entry = list.getLast();
    		} else {
    			entry = new PostingsEntry(docID, 0);
    			list.addLast(entry);
    		}
    	} else {
	    	for(PostingsEntry e : list) {
	    		if(e.docID >= docID) {
	    			if(e.docID == docID) {
	    				entry = e;
	    			}
	    			
	    			break;
	    		} else {
	    			index++;
	    		}
	    	}
    	}
    	
    	if(entry == null) {
    		entry = new PostingsEntry(docID, 0);
    		list.add(index, entry);
    	}
    	
    	entry.addOccurrence(offset);
    }
    
    /**
     * Get the intersecting {@code PostingsEntries} of two {@code PostingsLists}
     * 
     * @param a - the first {@code PostingsList}
     * @param b - the other {@code PostingsList}
     * @return a {@code PostingsList} with the intersection {@code PostingsEntries}
     */
    public static PostingsList getIntersection(PostingsList a, PostingsList b) {
    	PostingsList intersection = new PostingsList();
    	int aSize = a.size(), 
    		bSize = b.size(),
    		i = 0,
    		j = 0;
    	
    	while(i < aSize && j < bSize) {
    		int aDocID = a.get(i).docID,
    			bDocID = b.get(j).docID;
    		
    		if(aDocID == bDocID) {
    			intersection.add(aDocID, 0);
    			i++;
    			j++;
    		} else if(aDocID < bDocID) {
    			i++;
    		} else {
    			j++;
    		}
    	}
    	
    	return intersection;
    }
    
    /**
     * Get the {@code PostingsEntries} with the phrase made of two {@code PostingsLists}
     * 
     * @param a - the first {@code PostingsList}
     * @param b - the other {@code PostingsList}
     * @return a {@code PostingsList} where the tokens make the phrase from {@code a} and {@code b}
     */
    public static PostingsList getWithPhrase(PostingsList a, PostingsList b) {
    	PostingsList result = new PostingsList();
    	int aSize = a.size(),
    		bSize = b.size(),
    		i = 0,
    		j = 0;
        	
    	while(i < aSize && j < bSize) {
    		PostingsEntry aEntry = a.get(i),
    					  bEntry = b.get(j);
    		
    		if(aEntry.docID == bEntry.docID) {
    			Set<Integer> occurrencesA = aEntry.getOccurrences();
    			for(Integer occurrence : occurrencesA) {
    				if(bEntry.occurresAt(occurrence + 1)) {
    					result.add(aEntry.docID, (occurrence + 1));
    				}
    			}
    			
    			i++;
    			j++;
    		} else if(aEntry.docID < bEntry.docID) {
    			i++;
    		} else {
    			j++;
    		}
    	}
    	
    	return result;
    }

	public int compareTo(PostingsList o) {
		return size() - o.size();
	}
}
