package project;

import java.io.File;
import java.io.FileInputStream;
import java.util.HashMap;
import java.util.Map.Entry;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamReader;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

class Item {
	Double value;
	Integer count;

	public Item() {
		value = 0.0;
		count = 0;
	}

	public Double getAverage() {
		return value / count;
	}
}

class AnswerCounter {
	Integer correct;
	Integer incorrect;

	public AnswerCounter() {
		correct = 0;
		incorrect = 0;
	}

	public Double getCorrectPercentage() {
		return 100.0;
	}
}

public class Task1 {

	public static void stax() {
		HashMap<String, Item> servicecomponent_names = new HashMap<String, Item>();
		HashMap<String, Item> activitynames = new HashMap<String, Item>();
		HashMap<String, AnswerCounter> activitynamesAnswerCounter = new HashMap<String, AnswerCounter>();

		XMLInputFactory factory = XMLInputFactory.newInstance();
		XMLStreamReader reader;
		try {
			reader = factory.createXMLStreamReader(new FileInputStream(
					new File("simres59444.xml")));

			Item item = null;
			AnswerCounter ac = null;

			while (reader.hasNext()) {
				int event = reader.next();

				if (event == XMLStreamConstants.START_ELEMENT
						&& reader.getLocalName().equals("measurement")) {
					if (reader.getAttributeValue("", "status").equals("ok")) {
						Double responseperiod = Double.parseDouble(reader
								.getAttributeValue("", "responseperiod"));

						// add to servicecomponent_names
						String servicecomponent_name = reader
								.getAttributeValue("", "servicecomponent_name");

						if (servicecomponent_name != null) {
							item = servicecomponent_names
									.containsKey(servicecomponent_name) ? servicecomponent_names
									.get(servicecomponent_name) : new Item();
							item.count += 1;
							item.value += responseperiod;
							servicecomponent_names.put(servicecomponent_name,
									item);
						}

						// add to activitynames
						String activityname = reader.getAttributeValue("",
								"activityname");

						if (activityname != null) {
							// average
							item = activitynames.containsKey(activityname) ? activitynames
									.get(activityname) : new Item();
							item.count += 1;
							item.value += responseperiod;
							activitynames.put(activityname, item);

							// correct
							ac = activitynamesAnswerCounter
									.containsKey(activityname) ? activitynamesAnswerCounter
									.get(activityname) : new AnswerCounter();
							ac.correct++;
							activitynamesAnswerCounter.put(activityname, ac);
						}
					} else if (reader.getAttributeValue("", "status").equals(
							"false")
							&& reader.getAttributeValue("", "activityname") != null) {
						// incorrect
						String activityname = reader.getAttributeValue("",
								"activityname");

						ac = activitynamesAnswerCounter
								.containsKey(activityname) ? activitynamesAnswerCounter
								.get(activityname) : new AnswerCounter();
						ac.incorrect++;
						activitynamesAnswerCounter.put(activityname, ac);
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		// display results
		System.out
				.println("average responseperiod for each servicecomponent_name with status 'ok'");

		for (Entry<String, Item> entry : servicecomponent_names.entrySet()) {

			System.out.format("\tfor %s -> %.2f\n", entry.getKey(), entry
					.getValue().getAverage());
		}

		System.out
				.println("\n\naverage responseperiod for each activity with status 'ok'");

		for (Entry<String, Item> entry : activitynames.entrySet()) {

			System.out.format("\tfor %s -> %.2f\n", entry.getKey(), entry
					.getValue().getAverage());
		}

		System.out
				.println("\n\npercentage answered not-correctly by activityname");

		for (Entry<String, AnswerCounter> entry : activitynamesAnswerCounter
				.entrySet()) {

			System.out.format("\tfor %s -> %d | %d\n", entry.getKey(),
					entry.getValue().correct, entry.getValue().incorrect);
		}

	}

	public static void sax() {
		final HashMap<String, Item> servicecomponent_names = new HashMap<String, Item>();
		final HashMap<String, Item> activitynames = new HashMap<String, Item>();
		final HashMap<String, AnswerCounter> activitynamesAnswerCounter = new HashMap<String, AnswerCounter>();

		try {

			SAXParserFactory factory = SAXParserFactory.newInstance();
			SAXParser saxParser = factory.newSAXParser();

			DefaultHandler handler = new DefaultHandler() {

				Item item = null;
				AnswerCounter ac = null;

				public void startElement(String uri, String localName,
						String qName, Attributes attributes)
						throws SAXException {
					if (qName.equals("measurement")) {
						if (attributes.getValue("status").equals("ok")) {
							Double responseperiod = Double
									.parseDouble(attributes
											.getValue("responseperiod"));

							// add to servicecomponent_names
							String servicecomponent_name = attributes
									.getValue("servicecomponent_name");

							if (servicecomponent_name != null) {
								item = servicecomponent_names
										.containsKey(servicecomponent_name) ? servicecomponent_names
										.get(servicecomponent_name)
										: new Item();
								item.count += 1;
								item.value += responseperiod;
								servicecomponent_names.put(
										servicecomponent_name, item);
							}
							
							String activityname = attributes.getValue("activityname");
							
							if( activityname != null ) {
								// average
								item = activitynames
										.containsKey(activityname) ? activitynames
										.get(activityname) : new Item();
								item.count += 1;
								item.value += responseperiod;
								activitynames.put(activityname, item);
								
								// correct
								ac = activitynamesAnswerCounter
										.containsKey(activityname) ? activitynamesAnswerCounter
										.get(activityname) : new AnswerCounter();
								ac.correct++;
								activitynamesAnswerCounter.put(activityname, ac);
							}

						} else if (attributes.getValue("status").equals("false")
								&& attributes.getValue("activityname") != null) {
							// incorrect
							String activityname = attributes.getValue("activityname");

							ac = activitynamesAnswerCounter
									.containsKey(activityname) ? activitynamesAnswerCounter
									.get(activityname) : new AnswerCounter();
							ac.incorrect++;
							activitynamesAnswerCounter.put(activityname, ac);
						}
					}

				}

			};

			saxParser.parse("simres59444.xml", handler);

		} catch (Exception e) {
			e.printStackTrace();
		}

		// display results
		System.out
				.println("average responseperiod for each servicecomponent_name with status 'ok'");

		for (Entry<String, Item> entry : servicecomponent_names.entrySet()) {

			System.out.format("\tfor %s -> %.2f\n", entry.getKey(), entry
					.getValue().getAverage());
		}

		System.out
				.println("\n\naverage responseperiod for each activity with status 'ok'");

		for (Entry<String, Item> entry : activitynames.entrySet()) {

			System.out.format("\tfor %s -> %.2f\n", entry.getKey(), entry
					.getValue().getAverage());
		}

		System.out
				.println("\n\npercentage answered not-correctly by activityname");

		for (Entry<String, AnswerCounter> entry : activitynamesAnswerCounter
				.entrySet()) {

			System.out.format("\tfor %s -> %d | %d\n", entry.getKey(),
					entry.getValue().correct, entry.getValue().incorrect);
		}
	}

	public static void main(String[] args) {
		long startTime, stopTime;
		// SAX
		startTime = System.currentTimeMillis();
		sax();
		stopTime = System.currentTimeMillis();
		System.out.format("== SAX took %d ==\n", stopTime - startTime);
		
		// STAX
		startTime = System.currentTimeMillis();
		stax();
		stopTime = System.currentTimeMillis();
		System.out.format("== STAX took %d ==\n", stopTime - startTime);
	}

}