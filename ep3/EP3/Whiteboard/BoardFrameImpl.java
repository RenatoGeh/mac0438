// BoardFrameImpl.java
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
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.rmi.*;

public class BoardFrameImpl
    extends java.rmi.server.UnicastRemoteObject
    implements BoardFrame
{
    private static final long serialVersionUID = -5397351444331193874L;

    private int x0 = 0, y0 = 0, x1, y1;
    private static final int WIDTH = 400;
    private static final int HEIGHT = 400;
    private WbClient wbClient;
    private JFrame frame;
    private String myURL;
    private String clientURL;

    private void setClient() {
		try {
		    wbClient = (WbClient) Invoke.lookup(clientURL);
		    wbClient.recvDisplayObj(this);
		} catch (Exception x) {
		     x.printStackTrace();
		}
    }

    public BoardFrameImpl (String [] args) throws java.rmi.RemoteException {
		// args[] = 0:myId, 1:bnm, 2:clientMcnm, 3:clientId
        super();

        clientURL = Invoke.makeURL('C', args[4]);
		myURL = Invoke.makeURL('B', args[4]);

        // cria janela
        frame = new JFrame("BoardFrame " + args[1] +  "@" + clientURL + "@" + args[3]);

        frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		frame.setSize(BoardFrameImpl.WIDTH,BoardFrameImpl.HEIGHT);

		frame.addWindowListener(destroyWindow);
		frame.addWindowListener(raisedWindow);
		frame.addMouseListener(getCoords);

        frame.setVisible(true);

		try {
		    setClient();
		    Naming.rebind(myURL, this);
		    Invoke.myPrint("BoardFrameImpl", "executou Naming.rebind " + myURL);
		} catch (Exception x) {
		    x.printStackTrace();
		}
    }

    WindowListener destroyWindow = new WindowAdapter() {
	    public void windowClosing(WindowEvent e) { deleteAndExit(); }
	};

    WindowListener raisedWindow = new WindowAdapter() {
	    public void windowActivated(WindowEvent e) {
		try { wbClient.sendAllLines(); }
		catch (Exception x) {}
	    }
	};

    MouseListener getCoords = new MouseAdapter() {
	    public void mouseClicked(MouseEvent e) {
			if (e.getModifiers() == InputEvent.BUTTON3_MASK)
			    deleteAndExit();

			try {
			    // pegue coords, e mande linha para nosso cliente
			    LineCoords ln = new LineCoords();
			    ln.x2 = e.getX();
			    ln.y2 = e.getY();
			    ln.x1 = x0;
			    ln.y1 = y0;
			    x0 = ln.x2;	// guarde posicao atual
			    y0 = ln.y2;
			    wbClient.sendLine(ln);
			} catch (Exception x) {
			    x.printStackTrace();
			}
	    }
	};

    // invocado quando botao direito for pressionado ou
    // quando do fechamento da janela
    private void deleteAndExit() {
		try {
		    Naming.unbind(myURL);
		    wbClient.pleaseDie();
		} catch (Exception e) {}
	        System.out.println("Tchau!");
		System.exit(0);
    }

    // recebe coords de cliente e desenha linha
    public void recvOneLine(LineCoords ln) {
		frame.getGraphics().drawLine(ln.x1, ln.y1, ln.x2, ln.y2);
    }

    public static void main(String[] args) {

		Invoke.myPrint("BFI", "main");

		try {
		    BoardFrameImpl b = new BoardFrameImpl(args);
		} catch(Exception x) {}

    }
}


// eof
