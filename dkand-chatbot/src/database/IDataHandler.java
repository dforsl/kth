package database;

import aila.Subject;

public interface IDataHandler {
	
	/**
	 * lets the provided Subject s consume all knowledge of it
	 * 
	 * @param s - Subject
	 */
	public void retrieveSubjectData(Subject s);
	
	/**
	 * store all knowledge of the Subject s
	 * 
	 * @param s - Subject
	 */
	public void storeSubjectData(Subject s);
	
	
	/**
	 * let the handler finish of its use
	 * 
	 * @return
	 */
	public boolean finish();
	
}
