package project;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class Task4 {
	
	private static void addElemetWithText(Document doc, Element root, String name, String value) {
		Element elm = doc.createElement(name);
		elm.appendChild(doc.createTextNode(value));
        root.appendChild(elm);
	}
	
	private static Node getNodeByTagName(Node root, String name) {
         return (Node) ((Element) root).getElementsByTagName(name).item(0).getChildNodes().item(0);
	}
	
	private static ArrayList<String[]> filetoLines(File fin) throws IOException {
		FileInputStream fis = new FileInputStream(fin);
		ArrayList<String[]> list = new ArrayList<String[]>();
	 
		BufferedReader br = new BufferedReader(new InputStreamReader(fis));
	 
		String line = null;
		
		// omit first line
		br.readLine();
		
		while ((line = br.readLine()) != null) {
			list.add(line.split(","));
		}
	 
		br.close();
		return list;
	}
	
	public static void build() {
		ArrayList<String[]> lines = new ArrayList<String[]>();
		try {
			lines = filetoLines(new File("task3.txt"));
		} catch (IOException e) {
			System.err.println("File not found.");
		}
		
		
		DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        dbFactory.setIgnoringComments(true);
        dbFactory.setValidating(false);
        DocumentBuilder dBuilder;
        
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.newDocument();
            
            Element rootElement = doc.createElement("employees");
            doc.appendChild(rootElement);
            
    		// loop through lines
    		for(String[] row : lines) {
                Element employee = doc.createElement("employee");
                addElemetWithText(doc, employee, "name", row[0]);
                addElemetWithText(doc, employee, "dateOfBirth", row[1]);
                addElemetWithText(doc, employee, "dept", row[2]);
                addElemetWithText(doc, employee, "jobTitle", row[3]);

                doc.getFirstChild().appendChild(employee);
    		}
            
            //write to console or file
            StreamResult console = new StreamResult(System.out);
 
            //write data
            TransformerFactory transformerFactory = TransformerFactory.newInstance();  
            Transformer transformer = transformerFactory.newTransformer();
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            DOMSource source = new DOMSource(doc); 
            transformer.transform(source, console);
        } catch (Exception e) {
            e.printStackTrace();
        }
	}
}
