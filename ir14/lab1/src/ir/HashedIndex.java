/*  
 *   This file is part of the computer assignment for the
 *   Information Retrieval course at KTH.
 * 
 *   First version:  Johan Boye, 2010
 *   Second version: Johan Boye, 2012
 *   Additions: Hedvig Kjellström, 2012-14
 */  


package ir;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;

import javax.swing.event.ListSelectionEvent;


/**
 *   Implements an inverted index as a Hashtable from words to PostingsLists.
 */
public class HashedIndex implements Index {

    /** The index as a hashtable. */
    private HashMap<String, PostingsList> index = new HashMap<String,PostingsList>();


    /**
     *  Inserts this token in the index.
     */
    public void insert(String token, int docID, int offset) {
		PostingsList list = getPostings(token);
		if(list == null) {
			list = new PostingsList();
			index.put(token, list);
		}

		list.add(docID, offset);
    }

    /**
     *  Returns all the words in the index.
     */
    public Iterator<String> getDictionary() {
		return index.keySet().iterator();
    }


    /**
     *  Returns the postings for a specific term, or null
     *  if the term is not in the index.
     */
    public PostingsList getPostings(String token) {
		return index.get(token);
    }


    /**
     *  Searches the index for postings matching the query.
     */
    public PostingsList search(Query query, int queryType, int rankingType, int structureType) {
    	PostingsList results = null;
    	
    	if(query.terms.size() < 2) {
    		if(query.terms.isEmpty()) {
        		return null;
    		}
    		
    		return getPostings((query.terms.getFirst()));
    	} else if(queryType == Index.INTERSECTION_QUERY) {
			PriorityQueue<PostingsList> queue = new PriorityQueue<PostingsList>(query.terms.size());
			
			for(String term : query.terms) {
				PostingsList list = getPostings(term);
				if(list == null) {
					list = new PostingsList();
				}
				
				queue.offer(list);
			}
			
			results = queue.poll();
			while(!queue.isEmpty()) {
				results = PostingsList.getIntersection(results, queue.poll());
			}
			
			return results;
			
		} else if(queryType == Index.PHRASE_QUERY) {
			results = getPostings(query.terms.pollFirst());
			
			for(String term : query.terms) {
				PostingsList curr = getPostings((term));
				
				if(curr == null) {
					return null;
				}
				
				results = PostingsList.getWithPhrase(results, curr);
			}
		}
    	
		return results;
    }


    /**
     *  No need for cleanup in a HashedIndex.
     */
    public void cleanup() {
    }
}
