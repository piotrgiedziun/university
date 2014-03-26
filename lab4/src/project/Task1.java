package project;

import java.io.File;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class Task1 {
	
	public static void build() {
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            
            Document doc = dBuilder.newDocument();
            Element rootElement = doc.createElement("ComputerEngineering");
            doc.appendChild(rootElement);
 
            Element course = doc.createElement("Cource");  
            rootElement.appendChild(course);  
           
            // add attributes to school  
            course.setAttribute("Name", "Application programming - Java and XML technologies");  
            course.setAttribute("Author","Piotr Giedziun"); 
            
            Element topic = doc.createElement("Topic");  
            course.appendChild(topic);
            
            Element person = doc.createElement("Person");  
            person.setAttribute("Name","Piotr Giedziun"); 
            person.setAttribute("Age","23"); 
            course.appendChild(person);
 
            //write to file
            StreamResult file = new StreamResult(new File("task1.xml"));
 
            //write data
            TransformerFactory transformerFactory = TransformerFactory.newInstance();  
            Transformer transformer = transformerFactory.newTransformer();
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "3");
            DOMSource source = new DOMSource(doc); 
            transformer.transform(source, file);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
 

}
