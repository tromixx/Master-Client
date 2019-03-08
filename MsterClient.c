#include<ncurses.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
//#include "functions.h"
//unsigned int type;

#define CHARACTER 10

struct Character CH;
struct Room RM;
struct Message M;
struct Charray CHA;

//struct Chroom CR;


struct Character
{
		char Name[32];
		uint8_t Flags;
		uint16_t Attack;
		uint16_t Defense;
		uint16_t Regen;
		uint16_t Health;
		uint16_t Gold;
		uint16_t Current_Room_Number;
		uint16_t description_length;
		char Player_description[5000];

};

struct Room
{
		uint16_t Room_num;
		char Room_name[32];
		uint16_t Room_description_length;
		char Room_description[5000];
};




struct Message
{
		uint16_t Message_lenght;
		char Recipient_Name[32];
		char Sender_name[32];
		char Message[5000];
};

struct Charray
{
	char arrays[] =  {"Name", "Player_description"};
	printf(top, "%s %d %d %d %d %d %s", arr[0], arr[1]);
	int arrayd[] =  { 3, 3, 3, 3, 3};
	printf(top, "%d %d %d %d %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
};
/*

struct Chroom
{
		uint16_t Room_desc;
};
*/

void windw()
{
 char mesg[]="Enter start to beggin this fenomenal game experience: ";		/* message to be appeared on the screen */
 char str[80];
 int row,col;				/* to store the number of rows and *
					 * the number of colums of the screen */
 initscr();				/* start the curses mode */
 getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg); /* print the message at the center of the screen */
 getstr(str);
 mvprintw(LINES - 2, 0, "You where going to start ether way :)");
 getch();
 endwin();

}

struct receive_info {
	int skt;
	WINDOW* top;
	WINDOW* bottom;
	WINDOW* stats;
};

void exit_graceful(int signal){
	endwin();
	exit(0);
}

void* receive_print(void* arg){

	struct receive_info* prfi = (struct receive_info*)arg;
	char buff[1024];

	ssize_t readsize;

	//char stat[49];
	//char p=0;
	//unsigned short type;
	uint8_t type;

	for(;;){

		//wprintw(prfi->top, "Comands: X X X X X X X X X X X X X X X X X X X X X X X X X X X ");

		readsize = read(prfi->skt, &type, 1);
		//wprintw(prfi->bottom, "%d", type);

		if (type==1)
		{
			wprintw(prfi->top, "Type 1 MESSAGE: \n"); 

			//memset(M.Recipient_Name, 0, 32);
			//memset(M.Sender_name, 0, 32);	
			//memset(M.Message, 0, 5000);	

			read(prfi->skt, &M.Message_lenght, 2);
			wprintw(prfi->top,"Message: %d \n", M.Message_lenght);

			read(prfi->skt, M.Recipient_Name, 32);
			wprintw(prfi->top,"Recipient_Name: %s \n", M.Recipient_Name);

			read(prfi->skt, M.Sender_name, 32);
			wprintw(prfi->top,"Sender_name: %s \n", M.Sender_name);

			read(prfi->skt, M.Message, M.Message_lenght);
			wprintw(prfi->top,"Message: %s \n", M.Message);
			M.Message[M.Message_lenght] = 0;

			
			M.Message_lenght=0;
			memset(M.Recipient_Name, 0, 32);
			memset(M.Sender_name, 0, 32);
			memset( M.Message, 0, 1024);

			wrefresh(prfi->top);
			wrefresh(prfi->bottom);			

		}

		else if (type==2)
		{

			//read(prfi->skt, &RM.Room_num, 2);
			//wprintw(prfi->top, "Changing to room", RM.Room_num);
			//CHARACTER();
			//empty
			//wprintw(prfi->top, "CHANGE ROOM: 	\n"); 
			//uint16_t Room_num;

		}

		else if (type==3)
		{
			//wprintw(prfi->top, "3"); 

		}

		else if (type==4)
		{
			char Name_of_target_player[32];
			read(prfi->skt, Name_of_target_player, 32);

			wprintw(prfi->top,"Name_of_target_player: %s \n", Name_of_target_player);
			//wprintw(prfi->top, "4"); 

			wrefresh(prfi->top);
			wrefresh(prfi->bottom);
		}

		else if (type==5)
		{
			char Name_of_target_player[32];
			read(prfi->skt, Name_of_target_player, 32);

			wprintw(prfi->top,"Name_of_target_player: %s \n", Name_of_target_player);

			wrefresh(prfi->top);
			wrefresh(prfi->bottom);
			//wprintw(prfi->top, "LOOT COMMING! \n", readsize); 
			//char loot[32];

			//read(prfi->skt, &loot, 32);

			//wprintw(prfi->top, "Thats a lot of gold:  \n", loot); 

		}

		else if (type==6)
		{
			//wprintw(prfi->top, "STARTING GAME!: \n", readsize);

			//write(prfi->skt, &input, 1);


			//windw();

			//write(skt->sockfd, &Start, 32);


		}

		else if (type==7)
		{
			wprintw(prfi->top, "Error: \n");

			uint8_t Error_code;
			uint16_t Error_message_length;
			char error_message[1024];

			memset(error_message, 0, 1024);

			read(prfi->skt, &Error_code, 1);
			wprintw(prfi->top, "Type: %d", Error_code);

			read(prfi->skt, &Error_message_length, 2);
			//wprintw(prfi->top, "Type: %d", Error_message_length);

			read(prfi->skt, error_message, Error_message_length);
			wprintw(prfi->top, "Type: %s", error_message);

			wrefresh(prfi->top);
			wrefresh(prfi->bottom);


		}

		else if (type==8)
		{
			wprintw(prfi->top, "Message: \n");
			
			uint8_t Atype8;
			read(prfi->skt, &Atype8, 1);
			wprintw(prfi->top, "Type: %d", Atype8); 
			wrefresh(prfi->top);
			wrefresh(prfi->bottom);

		}

		else if (type==9)
		{
			wprintw(prfi->top, "9");

			read(prfi->skt, &RM.Room_num, 2);
			wprintw(prfi->top, "Room_num: %d \n", RM.Room_num);

			read(prfi->skt, RM.Room_name, 32);
			wprintw(prfi->top, "Room_name: %s \n", RM.Room_name);

			read(prfi->skt, &RM.Room_description_length, 2);
			wprintw(prfi->top, "Room_description_length: %d \n", RM.Room_description_length);

			read(prfi->skt, RM.Room_description, RM.Room_description_length);
			wprintw(prfi->top, "Room_description: %s \n", RM.Room_description);

			wrefresh(prfi->top);
			wrefresh(prfi->bottom);

			
		}

		else if (type==10)
		{

			wprintw(prfi->top, "CREATING CHARACTER:	\n"); 

			memset(CH.Name, 0, 32);
			memset(CH.Player_description, 0, 1024);

			read(prfi->skt, CH.Name, 32);
			wprintw(prfi->top, "Namee: %s \n", CH.Name);

			read(prfi->skt, &CH.Flags, 1);
			wprintw(prfi->top, "Flags: %d \n", CH.Flags);

			read(prfi->skt, &CH.Attack, 2);
			wprintw(prfi->top, "Attack: %d\n", CH.Attack);

			read(prfi->skt, &CH.Defense, 2);
			wprintw(prfi->top, "Defense: %d\n", CH.Defense);

			read(prfi->skt, &CH.Regen, 2);
			wprintw(prfi->top, "Regen: %d\n", CH.Regen);

			read(prfi->skt, &CH.Health, 2);
			wprintw(prfi->top, "Health: %d\n", CH.Health);

			read(prfi->skt, &CH.Gold, 2);
			wprintw(prfi->top, "Gold: %d\n", CH.Gold);

			read(prfi->skt, &CH.Current_Room_Number, 2);
			wprintw(prfi->top, "Current_Room_Number: %d\n", CH.Current_Room_Number);

			read(prfi->skt, &CH.description_length, 2);
			wprintw(prfi->top, "description_length: %d\n", CH.description_length);

			read(prfi->skt, CH.Player_description, CH.description_length);
			wprintw(prfi->top, "Player_description: %s\n", CH.Player_description);

			wrefresh(prfi->top);
			wrefresh(prfi->bottom);
/*
			desc = malloc(desc_len + 1);
			desc[desc_len] = 0;
			read(prfi->skt, desc, desc_len);

			wprintw(prfi->top, desc);
*/
		}

		else if (type==11)
		{
			//readsize = read(prfi->skt, buff, 33);

			wprintw(prfi->top, "GAME\n"); 
			//uint16_t init_points;
			unsigned short init_points;
			//uint16_t init_limit;
			unsigned short init_limit;
			//uint16_t desc_len;	
			unsigned short desc_len;
			char * desc= NULL;	

			read(prfi->skt, &init_points, 2);
			read(prfi->skt, &init_limit, 2);
			read(prfi->skt, &desc_len, 2);

			desc = malloc(desc_len + 1);
			desc[desc_len] = 0;
			read(prfi->skt, desc, desc_len);
			
			wprintw(prfi->top, "Initial points: %d \n", init_points);
			wprintw(prfi->top, "Stats Limit: %d \n", init_limit);
			wprintw(prfi->top, "Description Length %d \n", desc_len);
			wprintw(prfi->top, desc);
			wrefresh(prfi->top);
			wrefresh(prfi->bottom);


		}

		else if (type==12)
		{
			//wprintw(prfi->top, "12", readsize); 

		}

		else if (type==13)
		{
			wprintw(prfi->top, "13", readsize); 
			//memset(Room_name, 0, 32);
			//memset(Room_description, 0, 5000);

			read(prfi->skt, &RM.Room_num, 2);
			wprintw(prfi->top, "Room_num: %d \n", RM.Room_num);

			read(prfi->skt, RM.Room_name, 32);
			wprintw(prfi->top, "Room_name: %s \n", RM.Room_name);

			read(prfi->skt, &RM.Room_description_length, 2);
			wprintw(prfi->top, "Room_description_length: %d \n", RM.Room_description_length);

			read(prfi->skt, RM.Room_description, RM.Room_description_length);
			wprintw(prfi->top, "Room_description: %s \n", RM.Room_description);

			wrefresh(prfi->top);
			wrefresh(prfi->bottom);

		}
		type = -1;


		wprintw(prfi->top, "\n");
		wmove(prfi->bottom, LINES/4 - 2, 0);
		wrefresh(prfi->top);
		wrefresh(prfi->bottom);


		//reset te read
		memset(buff, 0, sizeof(buff));
	}
	return 0; 
}

int main(int argc, char ** argv){

	char buff[1024*1024];


	// Usage Information
	if(argc < 3){
		printf("Usage:  %s hostname port\n", argv[0]);
		return 1;
	}

	// Handle Signals
	struct sigaction sa;
	sa.sa_handler = exit_graceful;
	sigaction(SIGINT, &sa, 0);

	// Prepare the network connection, but don't call connect yet
	int skt = socket(AF_INET, SOCK_STREAM, 0);
	if(skt == -1)
		goto err;
	short port = atoi(argv[2]);
	struct sockaddr_in connect_addr;
	connect_addr.sin_port = htons(port);
	connect_addr.sin_family = AF_INET;
	struct hostent* entry = gethostbyname(argv[1]);
	if(!entry)
		goto err;
	struct in_addr **addr_list = (struct in_addr**)entry->h_addr_list;
	struct in_addr* c_addr = addr_list[0];
	char* ip_string = inet_ntoa(*c_addr);
	connect_addr.sin_addr = *c_addr;
	
	// Set up curses.  This is probably easier in Python.
	initscr();
	start_color();
	use_default_colors();
	init_pair(1, COLOR_GREEN, -1);
	init_pair(2, COLOR_RED, -1);
	refresh();
	WINDOW* top = newwin(LINES*3/4, COLS, 0, 0);
	WINDOW* bottom = newwin(LINES/4 - 1, COLS, LINES*3/4 + 1, 0);

	//WINDOW *stats     = newwin(10, 120/2+1, 0, 120/2);




	//STATS
	double max_x=7;
	double max_y=5;
	getmaxyx(stdscr, max_y, max_x);
	WINDOW *stats     = newwin(10, max_x/4, 10, max_x/4);
	wborder(stats,'|','|','-','-','+','+','+','+');
	mvwprintw(stats, 1, 1 , "COMMANDS:");
	mvwprintw(stats, 3,3,"2. start 'Starts the game'");
	mvwprintw(stats,4,4, "3. chroom 'Change the room'");
	mvwprintw(stats,5,5, "4. fight 'Fights the monster'");
	mvwprintw(stats,6,6, "5. Comming soon: pvpfight");
	mvwprintw(stats,7,5, "6. stats 'Show your stats'");
	mvwprintw(stats,8,4, "7. message 'Send Message'");
	mvwprintw(stats,8,4, "8. leave 'Send Message'");
	mvwprintw(stats, 2,2,"1. make 'Creates a Character'");
	//scrollok(side, 1);





	refresh();
	wmove(stdscr, LINES*3/4, 0);
	whline(stdscr, ACS_HLINE , COLS);
	wmove(bottom, LINES/4 - 2, 0);
	scrollok(bottom, 1);
	scrollok(top, 1);
	wrefresh(top);

	wrefresh(stats);

	wrefresh(bottom);
	refresh();

	// The UI is up, let's reassure the user that whatever name they typed resolved to something
	wattron(top, COLOR_PAIR(1));
	wprintw(top, "Connecting to host %s (%s)\n", entry->h_name, ip_string);
	wrefresh(top);
	
	// Actually connect.  It might connect top away, or sit here and hang - depends on how the
	// host is feeling today
	if(connect(skt, (struct sockaddr*)&connect_addr, sizeof(struct sockaddr_in)))
		goto err;
	
	// Let the user know we're connected, so they can start doing whatever they do.
	wprintw(top, "Connected\n");
	wrefresh(top);
	wattroff(top, COLOR_PAIR(1));

	// Start the receive thread
	struct receive_info rfi;
	rfi.skt = skt;
	rfi.top = top;
	rfi.bottom = bottom;
	pthread_t t;
	pthread_create(&t, 0, receive_print, &rfi);

	// Get user input.  Ctrl + C is the way out now.
	char input[48];
	wmove(bottom, LINES/4 - 2, 0);
	wgetnstr(bottom, input, 48); 
	size_t length=32;

	//uint8_t restart = 9;
/*
	char Name[32];
	uint8_t Flags;
	uint16_t Attack;
	uint16_t Defense;
	uint16_t Regen;
	uint16_t Health;
	uint16_t Gold;
	uint16_t Current_Room_Number;
	uint16_t desc_len;
	uint16_t Player_description;
	char * desc= NULL;	
*/

	for(;;)
	{
		//char input[48];
		wscrl(bottom, 0);
		wrefresh(bottom);
		wgetnstr(bottom, input, 1024*1024); //-1

		//if(!strcmp(input, "info"))
		//{
			//mvwprintw(stats, "start\t");
			//mvwprintw(stats, "chroom\t");
			//mvwprintw(stats, "fight\t");
			//mvwprintw(stats, "pvpfight\t");
			//mvwprintw(stats, "make !creates a character\t");
			//mvwprintw(stats, 1, 1 , "Well done");
		//}


		if(!strcmp(input, "message"))
		{
			//uint8_t input = 1;
			write(skt, &input, 1);
			wprintw(top, "\n");

			wprintw(top,"Message_lenght: %d \n", M.Message_lenght);
			wscanw(bottom, "%d", &M.Message_lenght);
			write(skt, &M.Message_lenght, 2);

			wprintw(top,"Recipient_Name: %s \n", M.Recipient_Name);
			wscanw(bottom, "%s", M.Recipient_Name);
			write(skt, M.Recipient_Name, 32);

			wprintw(top,"Sender_name: %s \n", M.Sender_name);
			wscanw(bottom, "%s", M.Sender_name);
			write(skt, M.Recipient_Name, 32);

			wprintw(top,"Message: %s \n", M.Message);
			wscanw(bottom, "%s", M.Message);
			write(skt, M.Message, M.Message_lenght);

			wrefresh(top);
			wrefresh(bottom);
		}


		if(!strcmp(input, "start"))
		{
			uint8_t input = 6;
			write(skt, &input, 1);
			wprintw(top, "\n");

			wrefresh(top);
			wrefresh(bottom);
		}


		if(!strcmp(input, "chroom"))
		{
			uint8_t input = 2;
			write(skt, &input, 1);

			//wprintw(top, "\n");

			wprintw(top, "Changing_room: ");
			wscanw(top, "%d", &RM.Room_num);
			write(skt, &RM.Room_num, 2);

			wrefresh(top);
			wrefresh(bottom);

		}

		if(!strcmp(input, "fight"))
		{
			uint8_t input = 3;
			write(skt, &input, 1);

			wrefresh(top);
			wrefresh(bottom);
		}

		if(!strcmp(input, "stats"))
		{
			wprintw(top, "Hi");
			//uint8_t input;

			wprintw(top, "Name: %s \n", CHA.arrays[0]);
			wprintw(top, "Attack: %d\n", CHA.arrayd[0]);
			wprintw(top, "Defense: %d\n", CHA.arrayd[1]);
			wprintw(top, "Regen: %d\n", CHA.arrayd[2]);
			wprintw(top, "Health: %d\n", CHA.arrayd[3]);
			wprintw(top, "Gold: %d\n", CHA.arrayd[4]);
			wprintw(top, "Player_description: %s\n", CHA.arrays[1]);
		}

		if(!strcmp(input, "leave"))
		{
			uint8_t input = 12;
			write(skt, &input, 1);

			wrefresh(top);
			wrefresh(bottom);
		}


		if(!strcmp(input, "pvpfight"))
		{
			uint8_t input = 4;
			write(skt, &input, 1);

			wrefresh(top);
			wrefresh(bottom);
		}

		if(!strcmp(input, "loot"))
		{
			uint8_t input = 6;
			write(skt, &input, 1);

			wrefresh(top);
			wrefresh(bottom);
		}




		if(!strcmp(input, "make"))
		{
			wprintw(top, "Creating a CHARACTER: \n");

			memset(CH.Player_description, 0, 32);
			
			memset(input, 0, 48);
			
			uint8_t input = 10;

			write(skt, &input, 1);

			//write(skt, CHARACTER, sizeof(uint8_t));

			uint16_t whatever = 1;
			wprintw(bottom, "Name: ");
			wscanw(bottom, "%s", CH.Name);
			write(skt, CH.Name, 32);

			//wprintw(bottom, "Flags: ");
			//wscanw(bottom, "%d", &CH.Flags);
			write(skt, &whatever, 1);

			wprintw(bottom, "Attack: ");
			wscanw(bottom, "%d", &CH.Attack);
			write(skt, &CH.Attack , sizeof(uint16_t));

			wprintw(bottom, "Defense: ");
			wscanw(bottom, "%d", &CH.Defense);
			write(skt, &CH.Defense , sizeof(uint16_t));

			wprintw(bottom, "Regen: ");
			wscanw(bottom, "%d", &CH.Regen);
			write(skt, &CH.Regen , sizeof(uint16_t));

			//wprintw(bottom, "Health: ");
			//wscanw(bottom, "%d", &CH.Health);
			write(skt, &whatever , sizeof(uint16_t));

			//wprintw(bottom, "Gold: ");
			//wscanw(bottom, "%d", &CH.Gold);
			write(skt, &whatever , sizeof(uint16_t));

			//wprintw(bottom, "Current_Room_Number: ");
			//wscanw(bottom, "%d", &CH.Current_Room_Number);
			write(skt, &whatever, sizeof(uint16_t));


			wprintw(bottom, "Player_description: ");
			wscanw(bottom, "%s", CH.Player_description);
			CH.description_length=(uint16_t)strlen(CH.Player_description);
			//wprintw(bottom, "Len: %d", strlen(CH.Player_description));
			//int description_length= 4;
			//wprintw(bottom, "description_length: ");
			//wscanw(bottom, "%d", &CH.description_length);
			write(skt, &CH.description_length , sizeof(uint16_t));
			write(skt, CH.Player_description , CH.description_length);

			//memset(input, 0, 48);

			wrefresh(top);
			wrefresh(bottom);

		}


	}

err:
	endwin();
	perror(argv[0]);
	return 1;
}

/*
WRITE:
		//length = strlen(input);
		//input[length] = '\n';
		//input[length+1] = 0;
		//scan and send to the server
		//wscanw("%c", &input);
		//write(skt, input, length+1);


/*
			wprintw(top,"Name: %s", CH.Name);
			wprintw(top,"State: %d", CH.Flags);
			wprintw(top,"Attack: %d", CH.Attack);
			wprintw(top,"Defense: %d", CH.Defense);
			wprintw(top,"Regen: %d", CH.Regen);
			wprintw(top,"Health: %d", CH.Health);
			wprintw(top,"Gold: %d", CH.Gold);
			wprintw(top,"Current_Room_Number: %d", CH.Current_Room_Number);
			wprintw(top,"desc_len: %d", CH.desc_len);
			wprintw(top,"Player_description: %s", CH.Player_description);




			char Name[32];
			uint8_t Flags;
			uint16_t Attack;
			uint16_t Defense;
			uint16_t Regen;
			uint16_t Health;
			uint16_t Gold;
			uint16_t Current_Room_Number;
			uint16_t desc_len;
			char Player_description[1024];	
*/

		//readsize = read(prfi->skt, buff, 1);


		//if (readsize=2)

		//if ()
/*
		readsize = read(prfi->skt, buff, 2);
		readsize = read(prfi->skt, buff, 3);
		readsize = read(prfi->skt, buff, 1);

		readsize = read(prfi->skt, buff, 1);
		readsize = read(prfi->skt, buff, 1);
		readsize = read(prfi->skt, buff, 1);
*/



//MESSAGE:
/*
		if readsize==1
			wprintw(prfi->top, buff);

		if readsize==2
			wprintw(prfi->top, "Message Length: \n", buff);

		if readsize==32
			wprintw(prfi->top, "Reciper Name: \n", buff);

		if readsize==32
			wprintw(prfi->top, "Sender Name:  \n", buff);

		if readsize<32
			wprintw(prfi->top, "Connection Terminated\n");




//CHARACTER
//ROOM
//ACCEPT
//ERRORS
//START
//LOOT
//PVPFIGHT
//FIGHT
//CHANGEROOM
//PROTOCOL MESSAGES
//GAME
//LEAVE
//CONNECTION
//MONSTERS

For each protocol 1 if

char name[1024*1024];
char attack[1024*1024];
char defense[1024*1024];
char regen[1024*1024];
char health[1024*1024];
char gold[1024*1024];
char room[1024*1024];

length = strlen(input)
length = strlen(input)
length = strlen(input)
length = strlen(input)
length = strlen(input)
length = strlen(input)
length = strlen(input)
length = strlen(input)

size_t length;

if (readsize = read(prfi->skt, buff, );)

write(skt, input, length+1);

0	Type, 10
1-32	Name of the player
33	Flags: Starting from the highest bit, Alive, Join Battle, Monster, Started, Ready. The lowest three are reserved for future use.
34-35	Attack
36-37	Defense
38-39	Regen
40-41	Health (signed)
42-43	Gold
44-45	Current room number (may be unknown to the player)
46-47	buff length
48+	Player buff

I been doing it wrong I think, I tohugh the server gave me number but it seems that my client retrieve bits.
So should I create one specific var for option? like attack, defence, name..
For example you read all the time and if it is 36-37 bits then you know is Defense or if it is 34-35 bits you know is atack.

//mvwprintw()

newwin(3)
