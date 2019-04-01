// A Java program for a Server
import java.net.*;
import java.io.*;

public class Room {
}

public class Player {
    private String name;
    byte[] flags = new byte[8];
    byte[] attack = new byte[16];
    byte[] defense = new byte[16];
    byte[] regen = new byte[16];
    byte[] health = new byte[16];
    byte[] gold = new byte[16];
    byte[] currentRoomNumber = new byte[16];
    byte[] descriptionLength = new byte[16];
    byte[] playerDescription = new byte[32];

    stream.read(name);
    stream.read(flags);
    stream.read(attack);
    stream.read(defense);
    stream.read(regen);
    stream.read(health);
    stream.read(gold);
    stream.read(currentRoomNumber);
    stream.read(descriptionLength);
    stream.read(playerDescription);


    public String getName() {
    return name;
    }
    public void setName(String name) {
    this.name = name;
    }
    public static void main(String[] args) {
    }
}

public class Server
{
    //initialize socket and input stream
    private Socket socket = null;
    private ServerSocket server = null;
    private DataOutputStream out = null;
    private DataInputStream in = null;

    // constructor with port
    public Server(int port)
    {
        // starts server and waits for a connection
        try
        {
            server = new ServerSocket(port);
            System.out.println("Server started");

            System.out.println("Waiting for a client ...");

            socket = server.accept();
            System.out.println("Client accepted");

            // takes input from the client socket
            in = new DataInputStream(
                new BufferedInputStream(socket.getInputStream()));

            String line = "";

            //send the output
            out = new DataOutputStream(socket.getOutputStream());

            // reads message from client until "Over" is sent
            while (!line.equals("exserver"))
            {
                try
                {
                    line = in.readUTF();
                    System.out.println(line);

                }
                catch(IOException i)
                {
                    System.out.println(i);
                }
            }
            System.out.println("Closing connection");

            // close connection
            socket.close();
            in.close();
        }
        catch(IOException i)
        {
            System.out.println(i);
        }
    }

    public static void main(String args[])
    {
        Server server = new Server(5000);
    }
}



final DataInputStream stream = new DataInputStream(socket.getInputStream)); //new input
//stream.readByte(); //reads the byte

//1 MESSAGE type,message ength(16), Recipient Name(32), Sender Name(32), Message(message length)

if(stream.readByte()==1){}
final int len = stream.readUnsignedShort(); //reads the message lenght
byte[] recipient = new byte[32]; //reads the recipient
byte[] sender = new byte[32]; //reads the sender

stream.read(recipient);//
stream.read(sender);

byte[] message_content = new byte[len];
stream.read(message_content);

final String message= new String(message_content, UTF_8);

//2 Change room
else if(stream.readByte()==2){
    byte[] room = new byte[8];
    stream.read(recipient);
}

//3 Fight
else if(stream.readByte()==3){}

//4 PVP
else if(stream.readByte()==4){}

//5 Loot
else if(stream.readByte()==5){}

//6 Start
else if(stream.readByte()==6){}

//7 Error
else if(stream.readByte()==7){}

//8 Accept
else if(stream.readByte()==8){}

//9 Room
else if(stream.readByte()==9){}

//10 Character
else if(stream.readByte()==10){}
//11 Game
else if(stream.readByte()==11){
}
//12 Leave
else if(stream.readByte()==12){
    socket.close(); // close connection
    in.close(); // close connection
}

//13 Connection
else if(stream.readByte()==13){

}


//Examples
final int len = stream.readUnsignedChar(); //8
final int len = stream.readUnsignedShort(); //16

byte[] example = new byte[8];
byte[] example = new byte[16];
byte[] example = new byte[32]; //32


// email cs
// ninas database
// mensaje mami por insurance y patente
// imprimir y mandar taxes
// chat app
// Mandar last 2 quizzes plus exam plus quizz 3
//5 Trabajar un poco en el server
// terminar los labs 4-5 250


//12 pm car insurance + dmv after
//retirar plata


// Raspberry pie Juegos
// Target lugares para vender websites

// Internal revenue service Stop 6579 A USC, 3651 F IH 35, Austin Texas 73301
// TPT letter, Licence, Social Security
