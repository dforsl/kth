package ir;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;

public class DiskIndex extends HashedIndex {
	private String tokensFilePath;
	private String occurrencesFilePath;
	
	public DiskIndex(String tokensFilePath, String occurrencesFilePath) {
		this.tokensFilePath = tokensFilePath;
		this.occurrencesFilePath = occurrencesFilePath;
	}
	
	public PostingsList getPostings(String token) {
		PostingsList list = null;
		try {
			BufferedReader tokensReader = new BufferedReader(new FileReader(new File(tokensFilePath)));
			RandomAccessFile occurrencesRAF = new RandomAccessFile(new File(occurrencesFilePath), "rw");

			String[] line = null;
			while(line == null) {
				String l = tokensReader.readLine();
				
				if(l == null) {
					return null;
				}
				
				line = l.startsWith(token + " ") ? l.split(" ") : null;
			}
			
			list = new PostingsList();
			for(int i = 1; i < line.length; i += 2) {
				int docID = Integer.parseInt(line[i]);
				long occurrencesAt = Long.parseLong(line[i+1]);
				
				occurrencesRAF.seek(occurrencesAt);
				String[] occurrencesLine = occurrencesRAF.readUTF().split(" ");
				for(String occStr :  occurrencesLine) {
					list.add(docID, Integer.parseInt(occStr));
				}
			}
			
			tokensReader.close();
			occurrencesRAF.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
		
		return list;
    }
}
