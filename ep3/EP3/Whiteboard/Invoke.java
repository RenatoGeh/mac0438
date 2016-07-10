// Invoke.java
//
// MAC-438 Programacao Concorrente
// USP - Instituto de Matematica e Estatistica
//
// Prof. Marcel P. Jackowski
// mjack@ime.usp.br
//

package Whiteboard;

import java.io.*;
import java.rmi.*;

public class Invoke {
    public static int verbosity = 1; // controls myPrint()
    private static BufferedReader stdIn; // stdinput, buffered

    private static int pid = 0; // pseudo process-id
    private static int svrCount = 0;
    private static final String rmiRegistryPfx = "rmi://localhost/";

    // Isolates path related issues.
    private static String javaCmd = "/usr/bin/java";
    //    "/usr/java/jdk1.2.2/bin/java";
    //    "e:\\jdk1.2.2\\bin\\java";
    private static final String serverClass = "Whiteboard.WbServerImpl";
    private static final String clientClass = "Whiteboard.WbClientImpl";
    private static final String linesClass = "Whiteboard.BoardFrameImpl";
    private static final String classNames[]
  = {serverClass, clientClass,linesClass};

    public static void setJavaCmdPath(String s) {
    javaCmd = s;
    }

    public static int getNumProcs() { return pid; }
    public static int getSvrCount() { return svrCount; }

    // for use during development only
    public static void myPrint(String who, String what) {
    if (verbosity > 0)
        System.out.println(who + ": " + what);
    }

    // post: return the users input; make sure it is non-empty
    public static String promptAndGet(String msg) {
    if (stdIn == null)
        stdIn = new BufferedReader(new InputStreamReader(System.in));

    String s = null;

    try {
        System.out.print(msg + ": ");
        System.out.flush();
        s = stdIn.readLine();
    } catch (Exception e) {}

    if (s == null || s == "") s = "vazio";
    return s;
    }

    // Invoke java on the given class in a separate process.  Also,
    // take care of any exceptions.
    public static void javaVM(char c, String args) {
    myPrint("Invoke", "javaVM");

    String classNm = classNames[c == 'S'? 0 : c == 'C' ? 1 : 2];
    String cmd = javaCmd + " " +  classNm + " " + (c=='S'?svrCount:pid) + " " +  args;
    if (c == 'S')
      ++svrCount;
    else
      ++pid;

    try {
        Runtime r = Runtime.getRuntime();
        myPrint("Run", ""  + r + cmd);
        try {
      Process p = r.exec(cmd);
      myPrint("\nInvoke",
        "process " + p + " criado para:\n" + cmd + "\n");
        } catch(Exception e) {
      System.out.println("Process Error ao executar [" + cmd + "]");
        }
    }
    catch(Exception e) {
        System.out.println("Runtime Error ao executar [" + cmd + "]");
    }
    }

    public static String makeURL(char c, String id) {
    return rmiRegistryPfx + c + id;
    }

    public static Remote lookup(String url) throws Exception {
      Remote r;
      for (int j = 0; j < 10; j++)
          try {
            r = Naming.lookup(url);
            System.out.println("Server encontrado!");
            return r;
          } catch (Exception e) {
            myPrint
                ("Invoke", url + " ainda nao encontrado; tentando ...");
            r = null;
            Thread.sleep(1000);
          }
      System.out.println("Nao foi possivel encontrar o server " + url + ". :(");
      return null;
    }

    public static void main(String[] args) {
    Invoke.javaVM('S', "");
    }
}

// -eof-
