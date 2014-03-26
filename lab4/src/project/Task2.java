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
import org.w3c.dom.Node;
import org.w3c.dom.Attr;  
import org.w3c.dom.NodeList;

public class Task2 {
	
	private static void addElemetWithText(Document doc, Element root, String name, String value) {
		Element elm = doc.createElement(name);
		elm.appendChild(doc.createTextNode(value));
        root.appendChild(elm);
	}
	
	private static Node getNodeByTagName(Node root, String name) {
         return (Node) ((Element) root).getElementsByTagName(name).item(0).getChildNodes().item(0);
	}
	
	public static void build() {
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        dbFactory.setIgnoringComments(true);
        dbFactory.setValidating(false);
        DocumentBuilder dBuilder;
        
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            File f = new File("book.xml");
            Document doc = dBuilder.parse(f);
            
            // get root element
            NodeList booksList = doc.getElementsByTagName("book");

            // change elm0 price
            Node elm0 = getNodeByTagName(booksList.item(0), "price");
            System.out.println("Elm0 - old price : "  + elm0.getNodeValue());
            elm0.setNodeValue("50.00");
            System.out.println("Elm0 - new price : "  + elm0.getNodeValue());
            
            // delete last row
            int last_row = booksList.getLength()-1;
            doc.getFirstChild().removeChild(booksList.item(last_row));
            
            // add new book
            Element book = doc.createElement("book");
            book.setAttribute("id", "bk123");
            
            addElemetWithText(doc, book, "author", "Piotr Giedziun");
            addElemetWithText(doc, book, "title", "I like pizza - based on true story");
            addElemetWithText(doc, book, "genre", "Romance");
            addElemetWithText(doc, book, "price", "19.99");
            addElemetWithText(doc, book, "publish_date", "2014-03-26");
            addElemetWithText(doc, book, "description", "-");

            doc.getFirstChild().appendChild(book);
            
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
