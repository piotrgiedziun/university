package project;

import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.SchemaFactory;

import org.w3c.dom.Document;
import org.xml.sax.ErrorHandler;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

class SimpleErrorHandler implements ErrorHandler {
    public void warning(SAXParseException e) throws SAXException {
        System.out.println(e.getMessage());
    }

    public void error(SAXParseException e) throws SAXException {
        System.out.println(e.getMessage());
    }

    public void fatalError(SAXParseException e) throws SAXException {
        System.out.println(e.getMessage());
    }
}

public class Task5 {
	
	public static void build() {
		SchemaFactory schemaFactory = 
			    SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		factory.setValidating(true);
		factory.setNamespaceAware(true);
		try {
			factory.setSchema(schemaFactory.newSchema(
				    new Source[] {new StreamSource("lab1_task3.xsd")}));
		} catch (SAXException e1) {}

		DocumentBuilder builder;
		try {
			builder = factory.newDocumentBuilder();
			builder.setErrorHandler(new SimpleErrorHandler());

			try {
				Document document = builder.parse(new InputSource("lab1_task3.xml"));
			} catch (SAXException | IOException e) {
				e.printStackTrace();
			}
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		}

	}
}
