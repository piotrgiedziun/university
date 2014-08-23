package project;

import java.io.File;
import java.text.DecimalFormat;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class Task4CreateXML {
	
	static int COUNT = 1000;
	static float UPPER = 0;
	static float LOWER = 255;
	static DecimalFormat df = new DecimalFormat("##.##");
	static String[] colors = new String[]{"red", "green", "blue"};
	
	public static void main(String[] args) {
		DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder dBuilder;
		try {
			dBuilder = dbFactory.newDocumentBuilder();

			Document doc = dBuilder.newDocument();
			Element rootElement = doc.createElement("values");
			doc.appendChild(rootElement);
			
			for(int i=0; i<COUNT; i++) {
				String color = colors[(int) (Math.random() * colors.length)];
				Double value = Math.random() * (UPPER - LOWER) + LOWER;
				Element course = doc.createElement("value");
				course.appendChild(doc.createTextNode(df.format(value)));
				course.setAttribute("color", color);
				rootElement.appendChild(course);
			}

			// write to file
			StreamResult file = new StreamResult(new File("task4_"+COUNT+".xml"));

			// write data
			TransformerFactory transformerFactory = TransformerFactory
					.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			transformer.setOutputProperty(
					"{http://xml.apache.org/xslt}indent-amount", "3");
			DOMSource source = new DOMSource(doc);
			transformer.transform(source, file);
			System.out.println("Done.");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
