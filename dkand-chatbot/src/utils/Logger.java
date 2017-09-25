package utils;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
	private static Status status;
	
	private static BufferedWriter writer;
	
	public enum Status	 {
		PRINT_AND_LOG, PRINT, LOG, DISABLED
	}
	
	public static boolean initLog(String filePath) {
		File f = new File("filePath");
		try {
			writer = new BufferedWriter(new PrintWriter(f));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return false;
		}
		
		switch(status) {
			case PRINT:	status = Status.PRINT_AND_LOG;
					   	break;	
		}
		
		System.out.println("Logger status is now " + status.toString());
		System.out.println("Logging in " + filePath);
		return true;
	}
	
	public static void logMessage(String message) {
		if(status == Status.LOG || status == Status.PRINT_AND_LOG) {
			writeToLog(message);
		}
		
		if(status == Status.PRINT || status == Status.PRINT_AND_LOG) {
			print(message);
		}
	}
	
	public static void logError(String message, Exception e) {
		if(status == Status.LOG || status == Status.PRINT_AND_LOG) {
			writeToLog(message, e);
		}
		
		if(status == Status.PRINT || status == Status.PRINT_AND_LOG) {
			print(message, e);
		}
	}
	
	private static void print(String message) {
		System.out.println("Message: " + message);
	}
	
	private static void print(String error, Exception e) {
		System.out.println("Error: " + error);
		System.out.println("Error Message: " + e.getMessage());
		System.out.println("Stack Trace: " + e.getStackTrace());
	}
	
	private static boolean writeToLog(String message) {
		try {
			writer.write("Message: " + message);
		} catch (IOException e) {
			print("Error whilst trying to log \"" + message + "\". ", e);
			return false;
		} catch (NullPointerException e) {
			print("Error whilst trying to log \"" + message + "\". ", e);
			return false;
		}
		
		return true;
	}
	
	private static boolean writeToLog(String error, Exception ex) {
		try {
			writer.write("Error: " + error);
			writer.write("Error Message: " + ex.getMessage());
			writer.write("Stack Trace: " + ex.getStackTrace());
		} catch (IOException e) {
			print("Error whilst trying to log \"" + error + "\". ", e);
			return false;
		} catch (NullPointerException e) {
			print("Error whilst trying to log \"" + error + "\". ", e);
			return false;
		}
		
		return true;
	}
	
	public static Status getStatus() {
		return status;
	}
	
	public static void setStatus(Status s) {
		switch(s) {
			case PRINT_AND_LOG: 	System.out.println("Initialize before logging. Printing messages.");
									break;
									
			case PRINT:				System.out.println("Logging disabled, printing messages.");
									break;
									
			case LOG:				System.out.println("Initialize before logging. Printing disabled.");
		}
		
		status = s;
	}	
}
