package project;

import java.awt.Image;

import javax.swing.ImageIcon;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@XmlRootElement(name = "coin")
@XmlType(propOrder = { "x", "y", "player_id" })
public class Coin {

	private Image image;
	@XmlElement(name = "x")
	private int x;
	@XmlElement(name = "y")
	private int y;
	@XmlElement(name = "player_id")
	private Integer player_id;
	
	public Coin() {}
	
	public Coin(int start_col, int start_row) {
		x = start_col;
		y = start_row;
		player_id = null;
	}


	public Coin(int start_col, int start_row, int player_id) {
		setPlayer(player_id);
		x = start_col;
		y = start_row;
	}

	public Image getImage() {
		if(image == null) {
			String fileName;
			if(player_id == 0)
				fileName = "pizza_0.png";
			else
				fileName = "pizza_1.png";
			
			ImageIcon ii = new ImageIcon(this.getClass().getResource(fileName));
			image = ii.getImage();
		}
		return image;
	}
	
	public void move(int x, int y) {
		this.x += x;
		this.y += y;
	}
	
	public int getX() {
		return x*60+10;
	}
	
	public int getY() {
		return y*60+10;
	}
	
	public int getRow() {
		return y;
	}
	
	public int getCol() {
		return x;
	}
	
	private Integer getPlayer() {
		return player_id;
	}
	
	public void setPlayer(int pid) {
		player_id = pid;
		String fileName;
		if(player_id == 0)
			fileName = "pizza_0.png";
		else
			fileName = "pizza_1.png";
		
		ImageIcon ii = new ImageIcon(this.getClass().getResource(fileName));
		image = ii.getImage();
	}
	
	@Override
	public boolean equals(Object obj) {
		if(!(obj instanceof Coin))
			return false;
		
		Coin coin = (Coin) obj;
		if(player_id != null)
			return coin.getRow() == getRow() && coin.getCol() == getCol() && coin.getPlayer() == getPlayer();
		return coin.getRow() == getRow() && coin.getCol() == getCol();
	}
	
}
