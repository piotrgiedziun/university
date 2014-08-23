package project;

import org.xml.sax.Attributes;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;

class Task2Handler extends DefaultHandler {
	
	public void startElement(String uri, String localName, String qName,
			Attributes atts) {
		System.out.format("Start tag: %s\n", qName);
	}

	public void endElement(String uri, String localName, String qName) {
		System.out.format("End tag: %s\n", qName);
	}

	public void characters(char[] ch, int start, int length) {
		String input = new String(ch, start, length).trim().split(" ")[0];
		if (!input.isEmpty()) {
			System.out.format("%s\n", input);
		}
	}
}

public class Task2 {
	public static void main(String[] args) {
		try {
			Task2Handler handler = new Task2Handler();
			XMLReader reader = XMLReaderFactory.createXMLReader();
			reader.setContentHandler(handler);
			reader.parse("task2.xml");
		} catch (Exception e) {
			System.err.println(e);
		}
	}
}
