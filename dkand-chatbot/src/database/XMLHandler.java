package database;

import java.io.File;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import aila.Subject;

public class XMLHandler implements IDataHandler {
	private final String dbFilePath = "src/database/subjects.xml";
	
	private Document db;	
	
	public XMLHandler() {
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder;
		
		try {
			builder = dbf.newDocumentBuilder();
			db = builder.parse(new File(dbFilePath));
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void retrieveSubjectData(Subject s) {
		/*
		 * normalize the document element
		 */
		db.getDocumentElement().normalize();
		
		/*
		 * get all subjects
		 */
		NodeList subjects = getNodeList(db, "/subjects/subject");
		
		/*
		 * loop through all subjects, find the one searched for
		 * 
		 * should be replaced by XPATH?
		 */
//		System.out.println("Number of subjects: " + subjects.getLength());
		for(int i = 0; i < subjects.getLength(); i++) {
			Element subject = (Element) subjects.item(i);
			
			Node n = getNode(subject, "name").getFirstChild();			
			if(n.getNodeValue().equals(s.getSubject())) {
				/*
				 * when found, consume the data and return
				 */
				s.consumeData(subject);
				return;
			}
		}	
	}

	@Override
	public void storeSubjectData(Subject s) {
		
		/* 
		 * add the new subject to the subjects root
		 */
		Node newSubject = subjectToNode(s);
		db.getFirstChild().appendChild(newSubject);
		
		/*
		 * write to the XML file
		 */
		if(!writeXML())
			System.out.println("Failed to write XML.");
	}
	
	private Node subjectToNode(Subject s) {
		/*
		 * create our new subject
		 */
		Element subject = db.createElement("subject"),
				name = db.createElement("name"),
				subjects = db.createElement("subjects"),
				associations = db.createElement("associations");
		
		/*
		 * set the name and append all children
		 */
		name.setTextContent(s.getSubject());
		subject.appendChild(name);
		subject.appendChild(subjects);
		subject.appendChild(associations);
		
		/*
		 * add the belonging subjects
		 */
		for(Subject c : s.getSubjects()) {
			Node child = subjectToNode(c);
			subject.appendChild(child);
		}
		
		/*
		 * add the known associations
		 */
		for(String a : s.getAssociations()) {
			Element association = db.createElement("association");
			association.setTextContent(a);
			
			associations.appendChild(association);
		}
		
		return subject;
	}
	
	/**
	 * write the db to our XML file
	 * 
	 * @return successful
	 */
	private boolean writeXML() {
		/*
		 * get the transformer factory
		 */
		TransformerFactory tf = TransformerFactory.newInstance();
		
		try {
			Transformer transformer = tf.newTransformer();
			
			/*
			 * retrieve the source from the db object and write
			 */
			DOMSource source = new DOMSource(db);
			StreamResult result = new StreamResult(new File(dbFilePath));
			transformer.transform(source, result);
		} catch (TransformerConfigurationException e) {
			e.printStackTrace();
			
			return false;
		} catch (TransformerException e) {
			e.printStackTrace();
			
			return false;
		}
		
		return true;
	}

	@Override
	public boolean finish() {
		
		return true;
	}
	
	public static NodeList getNodeList(Node source, String strExp) {
		XPathFactory xpf = XPathFactory.newInstance();
		XPath xp = xpf.newXPath();
		NodeList nl = null;
		try {
			XPathExpression expr = xp.compile(strExp);
			nl = (NodeList) expr.evaluate(source, XPathConstants.NODESET);
		} catch (XPathExpressionException e1) {
			e1.printStackTrace();
		}
		
		return nl;
	}
	
	public static Node getNode(Node source, String strExp) {
		XPathFactory xpf = XPathFactory.newInstance();
		XPath xp = xpf.newXPath();
		Node node = null;
		try {
			XPathExpression expr = xp.compile(strExp);
			node = (Node) expr.evaluate(source, XPathConstants.NODE);
		} catch (XPathExpressionException e1) {
			e1.printStackTrace();
		}
		
		return node;
	}
}
