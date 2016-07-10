package Whiteboard;

import java.util.*;

public class ABoard implements Board {
    private static final long serialVersionUID = 123992103890218321L;

    String boardName;     // Nome desta lousa
    Vector<LineCoords> vLines;  // todas as linhas nesta lousa
    Vector<WbClient> vClients;  // todos os clientes desta lousa

    public ABoard(String bnm) {
    boardName = bnm;
    vLines = new Vector<LineCoords>();
    vClients = new Vector<WbClient>();
    }

    public String getName() { return boardName; }
    public int getNumLines() { return vLines.size(); }
    public Vector<WbClient> getConnClients() { return vClients; }
}
