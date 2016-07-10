// WbAdmin.java
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

public class WbAdmin
{
    private Vector<WbServer> vServers;

    private static final String menu =
  "\nWbAdmin: cria [s]ervidor, [a]diciona cliente, " +
  "emite [r]elatorio, [t]ransfere lousa, para sair pressione [x]";

    public WbAdmin(String url) {
      vServers = new Vector<>();

      if (url == null) url = "localhost";

      System.out.println("Procurando por servidores pre-existentes...");

      for (int i=0;;++i) {
        WbServer svr = null;

        try {
          svr = (WbServer) Invoke.lookup("rmi://"+url+"/S"+i);
        } catch (Exception exc) {}

        if (svr == null) break;
        vServers.add(svr);
      }

      System.out.println("Não foram encontrados servidores pre-existentes.");
    }

    private void serverCreate() {
      String args = Invoke.promptAndGet("NomeMaquinaServidor");
      Invoke.javaVM('S',  args); // S for Server

      WbServer svr = null;
      int svrCount=0;

      try {
        // Procura por servidor.
        svr = (WbServer) Invoke.lookup("rmi://"+args+"/S"+(svrCount = Invoke.getSvrCount()-1));
      } catch (Exception exc) {
        exc.printStackTrace();
      }

      // Se achou, adiciona na lista de servidores.
      if (svr != null) {
        vServers.add(svr);
        System.out.println("Servidor criado com nome: S" + svrCount);
      }
    }

    private void addClientReq() {
    String args = Invoke.promptAndGet("NomeBoard Display ServidorURL");
    Invoke.javaVM('C', args); // C for Client
    }

    private void transferReq() {
      String input = Invoke.promptAndGet("NomeBoard OrigemURL DestinoURL");
      String[] args = input.split(" ");

      WbServer origin = null, dest = null;

      System.out.println("Procurando por servidores...");
      try {
        System.out.println("... Servidor origem.");
        origin = (WbServer) Invoke.lookup(args[1]);
        System.out.println("... Servidor destino.");
        dest = (WbServer) Invoke.lookup(args[2]);
      } catch (Exception exc) {
        exc.printStackTrace();
      }

      if (origin == null || dest == null) {
        System.out.println("Falha ao tentar encontrar um dos servidores.");
        return;
      }

      // Find board with name args[0].
      try {
        Vector<ABoard> boards = origin.getBoards();
        ABoard cb = null;
        for (ABoard b : boards) {
          if (b.getName().equals(args[0])) {
            cb = b;
            break;
          }
        }
        if (cb == null) {
          System.out.println("Board " + args[0] + " nao encontrada.");
          return;
        }
        Vector<WbClient> clients = cb.getConnClients();

        dest.addBoard(cb);
        origin.deleteBoard(args[0]);

        for (WbClient c : clients) {
          dest.sendAllLines(c, args[0]);
        }

        System.out.println("Board " + args[0] + " transferido de " + args[1] + " para " + args[2]);
      } catch (Exception exc) {
        exc.printStackTrace();
      }
    }

    private void queryReq() {
      try {
        for (WbServer svr : vServers) {
          System.out.println("Server \"" + svr.getURL() + "\n------------------------");
          Vector<? extends Board> boards = svr.getBoards();
          System.out.println(svr.getURL() + " contem " + boards.size() + " boards:");
          for (Board b : boards) {
            Vector<WbClient> clients = b.getConnClients();
            System.out.println("Board " + b.getName() + " contem " + b.getNumLines() + " linhas com "
                + clients.size() + " clientes:");
            for (WbClient client : clients)
              System.out.println("Client ID: " + client.getID());
          }
          System.out.println("------------||------------");
        }
      } catch(Exception exc) {
        exc.printStackTrace();
      }
      System.out.println("Final da lista de servidores.");
      System.out.println("------------------------");
    }

    private void userInteract() {
    while (true) {
        String choice = Invoke.promptAndGet(menu);
        switch (choice.charAt(0)) {
        case 's': serverCreate(); break;
        case 'a': addClientReq(); break;
        case 'r': queryReq(); break;
        case 't': transferReq(); break;
        case 'x': System.exit(0); break;
        }
    }
    }

    // Se args[1] for nao vazio, entao considera-se que args[1] e' o endereco URL. Senao, o
    // endereco considerado e' localhost.
    public static void main(String[] args) {
      WbAdmin wa = new WbAdmin(args.length<2?"localhost":args[1]);
      wa.userInteract();
    }
}

// -eof-
