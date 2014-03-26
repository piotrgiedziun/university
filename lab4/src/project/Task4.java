package project;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Iterator;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class Task4 {
	
	private static String arrayToString(String[] input) {
		StringBuilder sb = new StringBuilder();
		for (String n : input) { 
		    if (sb.length() > 0) sb.append(',');
		    sb.append(n);
		}
		return sb.toString();
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
            File f = new File("task3.xml");
            Document doc = dBuilder.parse(f);
            
            // get elements
            NodeList employeesList = doc.getElementsByTagName("employee");
            
            ArrayList<String[]> lines = new ArrayList<String[]>();
            lines.add(new String[] {"name","dateOfBirth","dept","jobTitle"});
            for(int i=0; i<employeesList.getLength(); i++) {
            	String[] row = {
            			getNodeByTagName(employeesList.item(i), "name").getNodeValue(),
            			getNodeByTagName(employeesList.item(i), "dateOfBirth").getNodeValue(),
            			getNodeByTagName(employeesList.item(i), "dept").getNodeValue(),
            			getNodeByTagName(employeesList.item(i), "jobTitle").getNodeValue(),
            			};
            	lines.add(row);
            }

            // write to file
            try {
    			File of = new File("task4.txt");
                BufferedWriter bw = new BufferedWriter(new FileWriter(of, false));
                for (Iterator<String[]> it = lines.iterator(); it.hasNext(); ) {
                    String[] row = it.next();
                    bw.write(arrayToString(row));
                    if (it.hasNext()) {
                    	bw.newLine();
                    }
                }
                bw.close();
    	    } catch (Exception e) {
    	    	System.err.println("Unable to save task4.txt file.");
    	    }

        } catch (Exception e) {
            e.printStackTrace();
        }
	}
}
