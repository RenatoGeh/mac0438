// WbClientImpl.java
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

public class WbClientImpl
    extends java.rmi.server.UnicastRemoteObject
    implements WbClient {

    private static final long serialVersionUID = 7863979949800221008L;

    private String myURL;
    private String thisMcnm;
    private String boardNm;
    private String myServerURL;
    private BoardFrame lf;
    private WbServer wbServer;
    private int clientID;

    public int getID() { return clientID; }

    // ache o nosso quadro; faca algumas tentativas
    private void makeBoard(String [] args) throws Exception {
      Invoke.javaVM
          ('B', args[1]  + " " + args[2] + " " + thisMcnm + " " + args[0]);
    }

    public WbClientImpl(String [] args) throws Exception {
      // args[] = 0:clientId, 1:brdNm, 2:displayMcnm, 3:wbserverURL
      super();
      thisMcnm = java.net.InetAddress.getLocalHost().getHostName();
      boardNm = args[1];
      clientID = Integer.parseInt(args[0]);

      myURL = Invoke.makeURL('C',  args[0]);
      Naming.rebind(myURL, this);
      Invoke.myPrint("WbClientImpl", "did Naming.rebind " +  myURL);

      makeBoard(args);
      myServerURL = args[3];
      wbServer = (WbServer) Invoke.lookup(myServerURL);

      // addClient() acontece em recvDisplayObj()
    }

    // esta chamada vem de wbServer
    public void updateBoard(LineCoords ln) throws Exception {
     lf.recvOneLine(ln);
    }

    public void sendAllLines()  throws Exception {
     wbServer.sendAllLines(this, boardNm);
    }

    public void sendLine(LineCoords ln) throws Exception {
     wbServer.addLine(ln, boardNm);
    }

    public void recvDisplayObj(BoardFrame ab) throws Exception {
     lf = ab;
     wbServer.addClient(this, boardNm);
    }

    public void pleaseDie() throws Exception {
      Naming.unbind(myURL);
      try { wbServer.delClient(this, boardNm);}
      catch (Exception x) {}
      System.exit(0);
    }

    public static void main(String args[]) throws Exception {
     WbClientImpl me = new WbClientImpl(args);
    }
}

// -eof-
