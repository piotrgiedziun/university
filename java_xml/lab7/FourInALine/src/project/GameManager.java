package project;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;

public class GameManager {
	
	private static String file_name = "game_state.xml";
	
	public static void autoSave(Game game) {
		save(game, file_name);
	}
	
	public static void save(Game game, String file_name) {
		GameManager.file_name = file_name;
		try {

			File file = new File(file_name);
			JAXBContext jaxbContext = JAXBContext.newInstance(Game.class);
			Marshaller jaxbMarshaller = jaxbContext.createMarshaller();

			jaxbMarshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);

			jaxbMarshaller.marshal(game, file);

		} catch (JAXBException e) {
			e.printStackTrace();
		}

	}
	
	public static Game load(String file_name) {
		GameManager.file_name = file_name;
		try {
			JAXBContext context = JAXBContext.newInstance(Game.class);
		    Marshaller m = context.createMarshaller();
			Unmarshaller um = context.createUnmarshaller();
			Game game = (Game) um.unmarshal(new FileReader(file_name));
			
			return game;
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (JAXBException e) {
			e.printStackTrace();
		}
		return null;
	}
}
