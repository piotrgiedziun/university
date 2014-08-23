package project;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class TGameKeyAdapter extends KeyAdapter {
	
	Game game;
	
	TGameKeyAdapter(Game g) {
		game = g;
	}
	
	@Override
	public void keyPressed(KeyEvent e) {
		int key = e.getKeyCode();
		
		if(key == KeyEvent.VK_RIGHT) {
			game.moveRight();
		}
		
		if(key == KeyEvent.VK_LEFT) {
			game.moveLeft();
		}
		
		if(key == KeyEvent.VK_DOWN) {
			game.accept();
		}
		
		super.keyPressed(e);
	}

}
