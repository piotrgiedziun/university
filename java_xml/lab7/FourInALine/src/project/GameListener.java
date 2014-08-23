package project;

interface GameListener{
    void repaintGame();
    void logMessage(String text);
    void actionFinished(boolean game_over);
}