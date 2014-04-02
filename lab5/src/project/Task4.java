package project;

import static com.googlecode.charts4j.Color.ALICEBLUE;
import static com.googlecode.charts4j.Color.BLACK;
import static com.googlecode.charts4j.Color.BLUEVIOLET;
import static com.googlecode.charts4j.Color.LAVENDER;
import static com.googlecode.charts4j.Color.LIMEGREEN;
import static com.googlecode.charts4j.Color.ORANGERED;
import static com.googlecode.charts4j.Color.WHITE;

import java.awt.BorderLayout;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.WindowConstants;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamReader;

import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.JDOMException;
import org.jdom2.input.SAXBuilder;
import org.xml.sax.Attributes;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;

import com.googlecode.charts4j.AxisLabels;
import com.googlecode.charts4j.AxisLabelsFactory;
import com.googlecode.charts4j.AxisStyle;
import com.googlecode.charts4j.AxisTextAlignment;
import com.googlecode.charts4j.BarChart;
import com.googlecode.charts4j.BarChartPlot;
import com.googlecode.charts4j.Data;
import com.googlecode.charts4j.Fills;
import com.googlecode.charts4j.GCharts;
import com.googlecode.charts4j.LinearGradientFill;
import com.googlecode.charts4j.Plots;
 
class Stats {
	private HashMap<String,Double> values ;
	
	Stats() {
		values = new HashMap<String,Double>();
		values.put("red", 0.0);
		values.put("green", 0.0);
		values.put("blue", 0.0);
	}
	
	public void increment(String key, Double value) {
		values.put(key, values.get(key)+value);
	}
	
	public Double getValue(String key) {
		return values.get(key);
	}
}

class Task4Handler extends DefaultHandler {
	private Stats stat;
	private String color;
	
	public Task4Handler(Stats stat) {
		this.stat = stat;
	}
	
	public void startElement(String uri, String localName, String qName,
			Attributes atts) {
		if("value".equals(localName)) {
			color = atts.getValue("color");
		}
	}

	public void characters(char[] ch, int start, int length) {
		String input = new String(ch, start, length).trim();
		if (!input.isEmpty()) {
			stat.increment(color, Double.valueOf(input));
		}
	}
}

public class Task4 {
	
	public static void main(String[] args) {
		run("task4_1000.xml", true);
		run("task4_100.xml", true);
		run("task4_10.xml", true);
		
		chart(new Long[][] { run("task4_10.xml", false), run("task4_100.xml", false), run("task4_1000.xml", false)});
	}
	
	public static void chart(Long[][] list) {
        BarChartPlot team1 = Plots.newBarChartPlot(Data.newData(list[0][2], list[1][2], list[2][2]), BLUEVIOLET, "STAX");
        BarChartPlot team2 = Plots.newBarChartPlot(Data.newData(list[0][1], list[1][1], list[2][1]), ORANGERED, "SAX");
        BarChartPlot team3 = Plots.newBarChartPlot(Data.newData(list[0][0], list[1][0], list[2][0]), LIMEGREEN, "DOM");

        // Instantiating chart.
        BarChart chart = GCharts.newBarChart(team1, team2, team3);

        // Defining axis info and styles
        AxisStyle axisStyle = AxisStyle.newAxisStyle(BLACK, 13, AxisTextAlignment.CENTER);
        AxisLabels score = AxisLabelsFactory.newAxisLabels("Time", 50.0);
        score.setAxisStyle(axisStyle);
        AxisLabels year = AxisLabelsFactory.newAxisLabels("Instance Size", 50.0);
        year.setAxisStyle(axisStyle);

        // Adding axis info to chart.
        chart.addXAxisLabels(AxisLabelsFactory.newAxisLabels("10", "100", "1000"));
        long maxValue = 0;
        for (int i = 0; i < list.length; i++) {
            for (int j = 0; j < list[i].length; j++) {
                if (list[i][j] > maxValue) {
                	maxValue = list[i][j];
                }
            }
        }
        chart.addYAxisLabels(AxisLabelsFactory.newNumericRangeAxisLabels(0, 100));
        chart.addYAxisLabels(score);
        chart.addXAxisLabels(year);

        chart.setSize(600, 450);
        chart.setBarWidth(100);
        chart.setSpaceWithinGroupsOfBars(20);
        chart.setDataStacked(true);
        chart.setTitle("Results", BLACK, 16);
        chart.setGrid(100, 10, 3, 2);
        chart.setBackgroundFill(Fills.newSolidFill(ALICEBLUE));
        LinearGradientFill fill = Fills.newLinearGradientFill(0, LAVENDER, 100);
        fill.addColorAndOffset(WHITE, 0);
        chart.setAreaFill(fill);
        String url = chart.toURLString();

        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setResizable( false );
        
        JLabel label = null;
		try {
			label = new JLabel(new ImageIcon(ImageIO.read(new URL(url))));
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        frame.getContentPane().add(label, BorderLayout.CENTER);
        frame.pack();
        frame.setVisible(true);
    }

	
	public static Long[] run(String file, Boolean debug) {
		Stats stats;
		long start, sax_time, dom_time, stax_time;
		
		// SAX Builder
		stats = new Stats();
		start = System.currentTimeMillis();
		SAXBuilder(stats, file);
		sax_time = System.currentTimeMillis() - start;
		
		// Display stats results
		if(debug)
			System.out.format("[SAX] red=%.2f, green=%.2f, blue=%.2f\n", 
				stats.getValue("red"), stats.getValue("green"), stats.getValue("blue"));
		
		// DOM Builder
		stats = new Stats();
		start = System.currentTimeMillis();
		DOMBuilder(stats, file);
		dom_time = System.currentTimeMillis() - start;
		
		// Display stats results
		if(debug)
			System.out.format("[DOM] red=%.2f, green=%.2f, blue=%.2f\n", 
				stats.getValue("red"), stats.getValue("green"), stats.getValue("blue"));
		
		// STAX Builder
		stats = new Stats();
		start = System.currentTimeMillis();
		STAXBuilder(stats, file);
		stax_time = System.currentTimeMillis() - start;
		
		// Display stats results
		if(debug)
			System.out.format("[STAX] red=%.2f, green=%.2f, blue=%.2f\n", 
				stats.getValue("red"), stats.getValue("green"), stats.getValue("blue"));
		
		// Display results
		if(debug) {
			System.out.format("[%s] DOM - %dms\n", file, dom_time);
			System.out.format("[%s] SAX - %dms\n", file, sax_time);
			System.out.format("[%s] STAX - %dms\n", file, stax_time);
		}
		return new Long[] {dom_time, sax_time, stax_time};
	}
	
	public static void SAXBuilder(Stats stats, String file) {
		try {
			Task4Handler handler = new Task4Handler(stats);
			XMLReader reader = XMLReaderFactory.createXMLReader();
			reader.setContentHandler(handler);
			reader.parse(file);
		} catch (Exception e) {
			System.err.println(e);
		}
	}

	public static void STAXBuilder(Stats stats, String file) {
		XMLInputFactory factory = XMLInputFactory.newInstance();
		XMLStreamReader reader;
		String color = null;
		
		try {
			reader = factory
					.createXMLStreamReader(new FileInputStream(new File(
							file)));

			while (reader.hasNext()) {
				int event = reader.next();
	
				switch (event) {
				case XMLStreamConstants.START_ELEMENT:
					if ("value".equals(reader.getLocalName())) {
						color = reader.getAttributeValue(0);
					}
					break;
	
				case XMLStreamConstants.CHARACTERS:
					if(!reader.getText().trim().isEmpty()) {
						stats.increment(color, Double.valueOf(reader.getText().trim()));
					}
					break;
	
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		} 
	}
	
	public static void DOMBuilder(Stats stats, String file) {
	  SAXBuilder builder = new SAXBuilder();
	  File xmlFile = new File(file);
 
	  try {
 
		Document document = (Document) builder.build(xmlFile);
		Element rootNode = document.getRootElement();
		List list = rootNode.getChildren("value");
 
		for (int i = 0; i < list.size(); i++) {
		   Element node = (Element) list.get(i);
		   stats.increment(node.getAttributeValue("color"), Double.valueOf(node.getValue()));
		}
 
	  } catch (IOException io) {
		System.out.println(io.getMessage());
	  } catch (JDOMException jdomex) {
		System.out.println(jdomex.getMessage());
	  }
	}
}