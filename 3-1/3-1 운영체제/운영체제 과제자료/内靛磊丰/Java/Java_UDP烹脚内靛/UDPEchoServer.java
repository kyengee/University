import java.io.*;
import java.net.*;

public class UDPEchoServer extends UDPServer {
    public final static int DEFAULT_PORT = 7;

    public UDPEchoServer() throws SocketException{
            super(DEFAULT_PORT);
    }

    @Override
    public void respond(DatagramPacket packet){
        try{
        DatagramPacket outgoing = new DatagramPacket(packet.getData(), 
        packet.getLength(), packet.getAddress(), packet.getPort());
        ds.send(outgoing);
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }

    public static void main(String[] args){
        
        System.out.println("** Server **");
        try{
            UDPServer server = new UDPEchoServer();
            Thread t = new Thread(server);
            t.start();
        }
        catch(SocketException e){
            e.printStackTrace();
        }
    }
}