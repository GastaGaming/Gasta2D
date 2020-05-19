#include <string>
#include <locale> //‰‰‰‰‰ ˆˆˆˆ varten
#include <clocale> //‰‰‰‰‰ ˆˆˆˆ varten
#include <fstream> // Tiedostojen lukua varten
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "DataBaseHandler.h"
#include <Windows.h>
#include "sha256.h"
#include <cstring>
#include <sstream>
#include "SDL.h"
#include "SDL_net.h"
//#include "../Network.h"
#undef main
//Tarkista et sqlite3.c k‰ytt‰‰ c compilerii koska t‰‰ mun solutioni on kakkaa.
using namespace std;
namespace DebugLog
{
	static void WarningMSG(const char* message)
	{
		printf("%c[%dm", 0x1B, 33);//Yellow
		std::cout << message << std::endl;
	}
	static void ErrorMSG(const char* message)
	{
		printf("%c[%dm", 0x1B, 31);//Red
		std::cout << message << std::endl;
	}
	static void LogMSG(const char* message)
	{
		printf("%c[%dm", 0x1B, 39);//White
		std::cout << message << std::endl;
	}
	static void SuccessMSG(const char* message)
	{
		printf("%c[%dm", 0x1B, 32);//Green
		std::cout << message << std::endl;
	}
}
using namespace DebugLog;
class MainHelper {
public:
	DatabaseHandler dbh;
	bool inputOk = false;
	void CreateTables()
	{
		dbh.Init();
		string line;
		string filecontent;
		ifstream Tables("TableInit.txt");

		if (Tables.is_open())
		{
			while (getline(Tables, line))
			{
				printf("%c[%dm", 0x1B, 33);//Yellow
				cout << line << '\n';
				filecontent.append(line);
			}
			Tables.close();
		}
		Tables.close();
		const char* c = filecontent.c_str();
		dbh.RunQuery(c);
	};
	void FillTables()
	{
		dbh.Init();
		string line;
		string filecontent;
		ifstream Tables("TableFill.txt");

		if (Tables.is_open())
		{
			while (getline(Tables, line))
			{
				printf("%c[%dm", 0x1B, 33);//Yellow
				cout << line << '\n';
				filecontent.append(line);
			}
			Tables.close();
		}
		Tables.close();
		const char* c = filecontent.c_str();
		dbh.RunQuery(c);
	}
};
inline bool file_exists(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	std::setlocale(LC_ALL, " ");
	std::locale::global(std::locale(""));
	std::cout.imbue(std::locale());
	string input;
	bool reset = false;
	bool quit = false;
	MainHelper mh;
	if (file_exists("GameServer.db"))
	{
		printf("%c[%dm", 0x1B, 33);//Yellow
		while (mh.inputOk != true)
		{
			cout << "Do you wanna DELETE OLD DataBase? Y | N to continue\n";
			cin >> input;
			if (input == "Y" || input == "y")
			{
				reset = true;
				if (remove("GameServer.db") != 0)
				{
					printf("%c[%dm", 0x1B, 31);//Red
					perror("Error deleting file");
				}
				else
				{
					printf("%c[%dm", 0x1B, 32);//Green
					puts("File successfully deleted");
				}
				printf("%c[%dm", 0x1B, 39);//White
				mh.inputOk = true;
			}
			else if (input == "N" || input == "n")
			{
				reset = false;
				mh.inputOk = true;
			}
			else
			{
				printf("%c[%dm", 0x1B, 31);//Red
				cout << "Input not valid\n";
			}
		}
	}
	else
	{
		reset = true;
	}
	mh.inputOk = false;
	if (reset == true)
	{
		while (mh.inputOk != true)
		{
			cout << "Do you wanna inatilaze Debug database? Y | N to continue\n";
			cin >> input;
			if (input == "Y" || input == "y")
			{
				printf("%c[%dm\n__________________\n", 0x1B, 32);//Green
				cout << "Walid input Y";
				//Initialize database tables and fill debug info
				mh.inputOk = true;
				mh.CreateTables();
				mh.FillTables();

			}
			else if (input == "N" || input == "n")
			{
				printf("%c[%dm", 0x1B, 32);//Green
				cout << "Walid input N\n";
				mh.inputOk = true;
				//Initialize database tables, but leave data empty.
				mh.CreateTables();
			}
			else
			{
				printf("%c[%dm", 0x1B, 31);//Red
				cout << "Input not valid\n";
			}
			mh.inputOk = true;
		}
	}
	//Natiivi kokeilu 1

	int PORT = 1023;
	LogMSG("Starting server........\n");
	if (SDL_Init(0) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
	SuccessMSG("SDL_INIT SUCCESSSSSSS!\n");
	UDPsocket udpsockServer, udpsockClient;
	IPaddress ipaddress;
	UDPpacket* recv_packet;
	SDLNet_SocketSet socketset = NULL;
	int numused;
	static const int MAX_PACKET_SIZE = 1024;
	SDLNet_ResolveHost(&ipaddress, NULL, PORT);
	if (SDLNet_ResolveHost(&ipaddress, NULL, PORT) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}
	udpsockServer = SDLNet_UDP_Open(PORT);
	if (!udpsockServer) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	else
	{
		//string Message = "Listening : " + &ipaddress.host + ' : ' + (int)ipaddress.port;
		//WarningMSG(Message.c_str());
		WarningMSG("listening on 0.0.0.0:1024\n");
	}
	socketset = SDLNet_AllocSocketSet(10);
	if (socketset == NULL) {
		fprintf(stderr, "Couldn't create socket set: %s\n", SDLNet_GetError());
		exit(2);
	}
	numused = SDLNet_UDP_AddSocket(socketset, udpsockServer);
	if (numused == -1) {
		printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());
		exit(2);
	}
	SuccessMSG("UDP SCOKET SUCCESS\n");
	SuccessMSG("STARTING SERVER LOOP\n");
	bool done = false;
	UDPpacket* packet = SDLNet_AllocPacket(1024);
	if (!packet) {
		printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(4);
	}

	while (!done)
	{
		int numrecv;
		numrecv = SDLNet_UDP_Recv(udpsockServer, packet);
		if (numrecv != NULL) {
			// do something with packet
			cout << "we got a message" << endl;
			string logIn = "logIn";
			string sData = "";
			for (int i = 0; i < packet->len; i++)//Collect the data
			{
				//std::cout << (char)packet->data[i];
				sData += (char)packet->data[i];
				//cout << sData << endl;
			}
			if (logIn.find(sData) != std::string::npos)//When complete we can compare it
			{
				std::cout << "found!" << '\n';
			}
			std::cout << std::endl;
			packet->data[packet->len] = '\0';
		}
	}
	SDLNet_UDP_Close(udpsockServer);
	udpsockServer = NULL; //this helps us know that this UDPsocket is not valid anymore
	// number is now in your hosts byte order, ready to use.

	//Natiivi kokeilu 2
	//udpConnection->InitServer(remotePort, localPort);

	//UDPpacket* packet;
	//char c[10][80000];
	//int cCount = 0;
	//int cLength[10];

	//bool running = true;

	//while (running)
	//{
	//	//clear();  //Clears garbage form SDL.
	//	packet = udpConnection->recievedData();
	//	#define PACKET_LEN packet->len
	//	//#define PACKET_DATA packet->data
	//	cout << "GGGG\m" << endl;
	//	if (packet != NULL) {
	//		cout << "we got a message" << endl;
	//		packet->data[PACKET_LEN] = 0;
	//		for (int i = 0; i < packet->len; i++)
	//		{
	//			std::cout << (char)packet->data[i];
	//		}
	//		std::cout << std::endl;
	//		for (int i = 0; i <= PACKET_LEN; i++) {
	//			c[cCount][i] = packet->data[i];
	//		}
	//		//*c[cCount] = udpConnection->packet->data;
	//		cLength[cCount] = PACKET_LEN;
	//		if (cCount == 9) {
	//			cCount = 0;
	//		}
	//		else {
	//			cCount++;
	//		}
	//	}
	//	/*for (int i = 0; i < packet->len; i++)
	//	{
	//		std::cout << (char)packet->data[i];
	//	}
	//	std::cout << std::endl;
	//	packet->data[packet->len] = '\0';*/
	//	/*for (int i = 0; i < cCount; i++) {
	//		text(c[i], 20, i * 16, cLength[i] * 16, 16, 0, 0, 0);
	//	}*/
	//}


	SDLNet_Quit();//Clean up

	//while (quit != true)
	//{
	//	cout << "Choose action or Q to quit.\n 1 | Create new user\n 2 | Login \n 3 | Test out sha256\n 4 | List tables\n" \
	//		" 5 | Select all from table\n 6 | Run Query\n";
	//	std::getline(std::cin >> std::ws, input);
	//	if (input == "1")
	//	{
	//		//Cre
	//		string userName;
	//		string email;
	//		string pw1, pw2;
	//		cout << "Write Username\n";
	//		cin >> userName;
	//		cout << "Write Your Email\n";
	//		cin >> email;
	//	back:
	//		cout << "Write Your PASSWORD\n";
	//		cin >> pw1;
	//		cout << "Plz write you PASSWORD AGAIN TO CONFIRM\n";
	//		cin >> pw2;

	//		if (pw1.compare(pw2) == 0)
	//		{
	//			pw1 = sha256(pw1);
	//			mh.dbh.CreateUser(userName, email, pw1);
	//			pw1 = "asd";
	//			pw2 = "fuug";
	//		}
	//		else
	//		{
	//			cout << "PASSWORD DOES NOT MATCH!!!!\n";
	//			goto back;
	//		}
	//	}
	//	if (input == "2")
	//	{
	//		string name;
	//		string pw;
	//		cout << "Write Username\n";
	//		cin >> name;
	//		cout << "Write Your PASSWORD\n";
	//		cin >> pw;
	//		pw = sha256(pw);
	//		mh.dbh.Login(name, pw);
	//	}
	//	if (input == "3")
	//	{
	//		string uinput;
	//		cout << "Type something to get hashet\n";
	//		cin >> uinput;
	//		string output = sha256(uinput);
	//		cout << "sha256('" << uinput << "') : " << output << endl;
	//	}
	//	if (input == "4")
	//	{
	//		mh.dbh.ListTables();
	//	}
	//	if (input == "5")
	//	{
	//		string uinput;
	//		cout << "Type table name\n";
	//		cin >> uinput;
	//		mh.dbh.SelectAllFromTable(uinput);
	//	}
	//	if (input == "6")
	//	{
	//		string uinput;
	//		cout << "Type query here example |SELECT * FROM User;|\n";
	//		std::getline(std::cin >> std::ws, uinput);
	//		//uinput = "SELECT * FROM User;";
	//		mh.dbh.RunQueryString(uinput);
	//	}
	//	if (GetKeyState(0x51) || input == "q")
	//	{
	//		quit = true;
	//	}
	//	else
	//	{
	//		input = "0";
	//		cout << "PLZ use valid input;|\n";
	//	}
	//	Sleep(5);
	//}

}