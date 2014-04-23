package project;

import javax.swing.JFrame;

public class GameFrame extends JFrame {

    public GameFrame() {
        add(new GamePanel());
        setTitle("C.C. is hungry. Hurry!");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(440, 560);
        setLocationRelativeTo(null);
        setVisible(true);
        setResizable(false);
    }
    public static void main(String[] args) {
        new GameFrame();
    }
}