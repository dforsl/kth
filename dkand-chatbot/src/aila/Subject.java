package aila;

import java.util.ArrayList;


import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import database.XMLHandler;

public class Subject {
	private String subject;
	
	//subjects owned by the subject
	private ArrayList<Subject> subjects;
	
	//associations with the subject
	private ArrayList<String> associations;
	
	public Subject(Element e) {
		subjects = new ArrayList<Subject>();
		associations = new ArrayList<String>();
		
		subject = e.getFirstChild().getNextSibling().getFirstChild().getNodeValue();
		consumeData(e);
	}
	
	public Subject(String s) {
		subject = s;
		subjects = new ArrayList<Subject>();
		associations = new ArrayList<String>();
	}
	
	public String getSubject() {
		return subject;
	}
	
	public ArrayList<Subject> getSubjects() {
		return subjects;
	}
	
	public ArrayList<String> getAssociations() {
		return associations;
	}
	
	public void addSubject(Subject s) {
		subjects.add(s);
	}
	
	public void getChildSubject(String child) {
		for(Subject s : subjects) {
			if(s.getSubject().equals(child)) {
				for(Subject c : s.getSubjects()) {
					System.out.println(c.getSubject());
				}
			}
		}
	}
	
	public void consumeData(Element e) {
		NodeList sList = XMLHandler.getNodeList(e, "subjects/subject");
//		System.out.println("Number of subjects: " + sList.getLength());
		for(int i = 0; i < sList.getLength(); i++) {
			Element sElement = (Element) sList.item(i);
			Subject s = new Subject(sElement);
			subjects.add(s);
		}

		NodeList associations = XMLHandler.getNodeList(e, "associations/association");
//		System.out.println("Number of associations: " + associations.getLength());
		for(int i = 0; i < associations.getLength(); i++) {
			String l = associations.item(i).getFirstChild().getTextContent();
			this.associations.add(l);
		}
	}
	
	public void print() {
//		System.out.println("Subject: " + subject);
//		System.out.println("Associations: " + associations.toString());
//		System.out.println("Children: { ");
		for(Subject s : subjects) {
			s.print();
			System.out.println(" }");
		}
	}
}
