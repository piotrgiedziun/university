package project;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.Timer;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@XmlRootElement(name = "game")
@XmlType(propOrder = { "coins", "current_player_id", "mainCoin" })
public class Game implements ActionListener {
	
	private ArrayList<Player> players;
	
	@XmlElementWrapper(name = "coins")
	@XmlElement(name = "coin")
	private ArrayList<Coin> coins;
	private GameListener gameListener;
	@XmlElement
	private int current_player_id;
	@XmlElement
	private Coin mainCoin;
	private Coin fallingCoin;
	private Timer timer;
	
	public final static int ROWS = 6;
	public final static int COLS = 7;
	
	public Game() {
		// init gameListener
		gameListener = null;
		fallingCoin = null;
		
		// add two players
		players = new ArrayList<Player>();
		players.add(new Player("Player #1"));
		players.add(new Player("Player #2"));
		
		// create main coin
		current_player_id = 0;
		mainCoin = new Coin(0, 0, current_player_id);
		
		// create coins array
		coins = new ArrayList<Coin>();
	}
	
	public Player currentPlayer() {
		return players.get(current_player_id);
	}
	
	public ArrayList<Coin> getCoins() {
		return coins;
	}
	
	public void moveLeft() {
		move(-1);
	}
	
	public void moveRight() {
		move(1);
	}
	
	private void changePlayer() {
		current_player_id = (current_player_id == 0) ? 1 : 0;
		mainCoin.setPlayer(current_player_id);
	}
	
	public void accept() {
		// block accept while coin is falling and when stack is full
		if(fallingCoin != null || !nextIsAvailable(mainCoin, 0, 1)) {
			return;
		}
		// add new coin & block main coin
		coins.add(new Coin(mainCoin.getCol(), 1, current_player_id));
		
		fallingCoin = coins.get(coins.size()-1);
		
		// start falling animation
		interfaceChnaged();
		timer.start();
	}
	
	public void addListener(GameListener gl) {
		gameListener = gl;
	}

	public Coin getMainCoin() {	
		if(fallingCoin != null)
			return null;
		
		return mainCoin;
	}
	
	public void addTimer(Timer t) {
		timer = t;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {		
		
		if(fallingCoin.getRow() <= ROWS && nextIsAvailable(fallingCoin, 0, 1)) {
			fallingCoin.move(0, 1);
		}else{
			timer.stop();
			
			// check if gg
			boolean gg=false;
			int i=0, j=0;
			
			do {
				i++;
			} while(nextIsMine(fallingCoin, i, 0));
			do {
				j++;
			} while(nextIsMine(fallingCoin, -j, 0));
			
			if(i+j-1 >= 4) {
				gg=true;
			}
			
			i=0; j=0;
			do {
				i++;
			} while(nextIsMine(fallingCoin, 0, i));
			do {
				j++;
			} while(nextIsMine(fallingCoin, 0, -j));
			
			if(i+j-1 >= 4) {
				gg=true;
			}
			
			i=0; j=0;
			do {
				i++;
			} while(nextIsMine(fallingCoin, i, i));
			do {
				j++;
			} while(nextIsMine(fallingCoin, -j, -j));
			
			if(i+j-1 >= 4) {
				gg=true;
			}
			
			i=0; j=0;
			do {
				i++;
			} while(nextIsMine(fallingCoin, -i, i));
			do {
				j++;
			} while(nextIsMine(fallingCoin, j, -j));
			
			if(i+j-1 >= 4) {
				gg=true;
			}
			
			if(!gg) {
				fallingCoin = null;
				changePlayer();
			}else if( gameListener != null ) {
				gameListener.logMessage(current_player_id == 0 ? "Player #1 WON!" : "Player #2 WON!");
			}
		}
		interfaceChnaged();
	}
	
	private boolean nextIsMine(Coin coin, int x, int y){
		Coin nextCoin = new Coin(coin.getCol()+x, coin.getRow()+y, current_player_id);
		return coins.contains(nextCoin);
	}
	
	private boolean nextIsAvailable(Coin coin, int x, int y) {
		Coin nextCoin = new Coin(coin.getCol()+x, coin.getRow()+y);
		return !coins.contains(nextCoin);
	}

	private void move(int x) {
		if(fallingCoin != null)
			return;

		if(mainCoin.getCol()+x >= 0 && mainCoin.getCol()+x < COLS) {
			mainCoin.move(x, 0);
			interfaceChnaged();
		}
	}
	
	private void interfaceChnaged() {
		if( gameListener != null ) {
			gameListener.repaintGame();
		}
	}

	public void restart() {
		coins.clear();
		current_player_id = 0;
		fallingCoin = null;
		mainCoin = new Coin(0, 0, current_player_id);
		interfaceChnaged();
	}
	
}
