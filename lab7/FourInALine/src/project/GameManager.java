package project;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;

public class GameManager {
	
	private static final String GAME_STATE_FILE = "game_state.xml";
	
	public static void save(Game game) {
		try {

			File file = new File(GAME_STATE_FILE);
			JAXBContext jaxbContext = JAXBContext.newInstance(Game.class);
			Marshaller jaxbMarshaller = jaxbContext.createMarshaller();

			jaxbMarshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);

			jaxbMarshaller.marshal(game, file);

		} catch (JAXBException e) {
			e.printStackTrace();
		}

	}
	
	public static Game load() {
		try {
			JAXBContext context = JAXBContext.newInstance(Game.class);
		    Marshaller m = context.createMarshaller();
			Unmarshaller um = context.createUnmarshaller();
			Game game = (Game) um.unmarshal(new FileReader(GAME_STATE_FILE));
			
			return game;
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (JAXBException e) {
			e.printStackTrace();
		}
		return null;
	}
}
