package project;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.Timer;

public class GamePanel extends JPanel implements GameListener {

	private Game game;
	private JLabel logLabel;
	private JButton newGame;
	private BufferedImage image;

	public GamePanel() {

		game = new Game();
		game.addListener(this);
		game.addTimer(new Timer(130, game));

		addKeyListener(new TGameKeyAdapter(game));
		setFocusable(true);
		setBackground(Color.white);
		setLayout(null);

		newGame = new JButton("New Game");
		newGame.setBounds(5, (game.COLS + 1) * 60 + 20, 100, 30);
		newGame.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				logLabel.setText("");
				game.restart();
				requestFocusInWindow();
			}
		});

		JButton saveGame = new JButton("Save");
		saveGame.setBounds(100, (game.COLS + 1) * 60 + 20, 100, 30);
		saveGame.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				GameManager.save(game);
				requestFocusInWindow();
			}
		});

		JButton loadGame = new JButton("Load");
		loadGame.setBounds(195, (game.COLS + 1) * 60 + 20, 100, 30);
		loadGame.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				logLabel.setText("");
				game = GameManager.load();
				game.addListener(GamePanel.this);
				game.addTimer(new Timer(130, game));
				addKeyListener(new TGameKeyAdapter(game));
				repaint();
				requestFocusInWindow();
			}
		});

		logLabel = new JLabel();
		logLabel.setBounds(295, (game.COLS + 1) * 60 + 20, 100, 30);

		add(newGame);
		add(saveGame);
		add(loadGame);
		add(logLabel);

		try {
			image = ImageIO.read(new File("cc.jpg"));
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

	public void paint(Graphics g) {
		super.paint(g);
		g.drawImage(image, -10, 50, null);
		
		Graphics2D g2d = (Graphics2D) g;

		// draw main coin
		Coin main = game.getMainCoin();
		if (main != null)
			g2d.drawImage(main.getImage(), main.getX(), main.getY(), this);

		// draw others coins
		for (Coin c : game.getCoins()) {
			g2d.drawImage(c.getImage(), c.getX(), c.getY(), this);
		}

		// draw grid
		for (int i = 0; i <= game.COLS; i++)
			g2d.drawLine(10 + i * 60, 70, 10 + i * 60,
					(game.ROWS + 2) * 60 + 10);

		for (int i = 1; i <= game.ROWS + 2; i++)
			g2d.drawLine(10, 10 + i * 60, 10 + game.COLS * 60, 10 + i * 60);

		Toolkit.getDefaultToolkit().sync();
		g.dispose();
	}

	@Override
	public void repaintGame() {
		repaint();
	}

	@Override
	public void logMessage(String text) {
		newGame.requestFocusInWindow();
		logLabel.setText(text);
	}

}
