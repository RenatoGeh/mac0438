// WbServerImpl.java
//
// MAC-438 Programacao Concorrente
// USP - Instituto de Matematica e Estatistica
//
// Prof. Marcel P. Jackowski
// mjack@ime.usp.br
//

package Whiteboard;

import java.io.*;
import java.util.*;
import java.rmi.*;
import java.rmi.server.*;

public class WbServerImpl
    extends UnicastRemoteObject
    implements WbServer
{
  private static final long serialVersionUID = 1458229962978494252L;

    private Vector<ABoard> vBoards;
    private String myURL;

    public WbServerImpl(String [] args) throws Exception {
    // args[] = serverID, serverMcnm
    vBoards = new Vector<ABoard>();
    myURL = Invoke.makeURL('S', args[0]);
    Naming.rebind(myURL, this);
    }

    public Vector<ABoard> getBoards() throws Exception { return vBoards; }
    public String getURL() throws Exception { return myURL; }

    private void pleaseDie() throws Exception {
    Naming.unbind(myURL);
    System.exit(0);
    }

    private ABoard findAboard(String bnm) {
    for (Enumeration<ABoard> e = vBoards.elements(); e.hasMoreElements();) {
        ABoard b = e.nextElement();
        if (bnm.equals(b.boardName))
          return b;
    }
    return null;
    }

    public void addBoard(ABoard b) throws Exception {
      vBoards.addElement(b);
    }

    public void deleteBoard(String name) throws Exception {
      int index = -1;
      for (int i=0;i<vBoards.size();++i)
        if (vBoards.elementAt(i).getName().equals(name))
          index = i;
      if (index < 0)
        System.out.println("No such board.");
      vBoards.removeElementAt(index);
    }

    public void sendAllLines(WbClient wc, String bnm) throws Exception {
    ABoard ab = findAboard(bnm);
    sendAllLines(wc, ab);
    }

    private void sendAllLines(WbClient wc, ABoard ab) throws Exception {
    for (Enumeration<LineCoords> e = ab.vLines.elements(); e.hasMoreElements(); ) {
        wc.updateBoard(e.nextElement());
    }
    }

    public void addClient(WbClient wc, String brnm) throws Exception {
    ABoard ab = findAboard(brnm);
    if (ab == null) {
        ab = new ABoard(brnm);
        vBoards.addElement(ab);
    } else {
        sendAllLines(wc, ab); // novo cliente em uma lousa antiga
    }
    ab.vClients.addElement(wc);
    }

    public void delClient(WbClient wc, String brnm) throws Exception {
    ABoard ab = findAboard(brnm);
    if (ab == null) return;

    ab.vClients.removeElement(wc);

    // Caso ultimo cliente desta lousa, apague lousa
    if (ab.vClients.size() == 0) vBoards.removeElement(ab);

    // Caso ultima lousa, termine servidor
    if (vBoards.size() == 0) pleaseDie();
    }

    public void addLine(LineCoords ln, String bnm) throws Exception {
    ABoard ab = findAboard(bnm);
    if (ab == null) return;

    ab.vLines.addElement(ln);

    // Broadcast para todos os clientes desta lousa
    for (Enumeration<WbClient> e = ab.vClients.elements(); e.hasMoreElements();) {
        WbClient wc = e.nextElement();
        wc.updateBoard(ln);
    }
    }

    public static void main(String args[])  throws Exception {
    WbServerImpl wsi = new WbServerImpl(args);
    }
}

// -eof-
