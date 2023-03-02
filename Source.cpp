/*
the single machine version of the pizza calculator. later I will make the multi machine server and the multi machine client

Pizza calculated by etienne chamberlain
*/
/* the plan for the pizza calculator

what needs calculating
pizza diameter in inches raw input the program assumes you are making a circular pizza
pizza radius is half the pizza diameter
pi is 3.14159 in this application so dont order a pizza too big or accuracy will be lost
pizza radius squared times pi equals pizza area in square inches

next is the pizza price in dollars and cents
pizza price is a dollars and cents value input as raw input
warning the price of the pizza can include micropennies if you accidentally put three or more digits in cents
pizza deal is the pizza area divided by the pizza price


the next step:
error handling is done. sometime after that socket code
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <ws2tcpip.h>
#define PORT 8080




#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc, char* argv[])
{
	WSADATA wsa;
	SOCKET s;
	SOCKET new_socket;
	struct sockaddr_in server;
	int c;
	struct sockaddr_in client;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}

	puts("Bind done");

	//Listen
	listen(s, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s, (struct sockaddr*)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
	}

	puts("Connection accepted");


	closesocket(s);
	WSACleanup();

	return 0;
}

int hostnameLookup(int argc, char* argv[])
{
	WSADATA wsa;
//	const char* hostname = "www.google.com";
	const char* hostname = "192.168.1.7";
	char ip[100];
	struct hostent* he;
	struct in_addr** addr_list;
	int i;
	struct addrinfo hints;

	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	DWORD dwRetval;



	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");


	if ((he = gethostbyname(hostname)) == NULL)
	{
		//gethostbyname failed
		printf("gethostbyname failed : %d", WSAGetLastError());
		return 1;
	}

	//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	addr_list = (struct in_addr**)he->h_addr_list;

	for (i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}
	printf("%s resolved to : %s\n", hostname, ip);
}



int client(int argc, char* argv[])
{
	WSADATA wsa;
	SOCKET s;
	char server_reply[2000];
	int recv_size;

	struct sockaddr_in server;
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.");
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");
//	struct sockaddr_in server;
	inet_pton(AF_INET, "192.168.1.7", &server.sin_addr.s_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");
	const char* message = "GET / HTTP/1.1\r\n\r\n";
	if (send(s, message, strlen(message), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	//Receive a reply from the server
	if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}

	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	puts(server_reply);
	closesocket(s);
	WSACleanup();

	return 0;

	return 0;
}
float pizza_calculation(float pizza_diameter)
{
	float pizza_radius = (pizza_diameter / 2);
	float pi = 3.14159;
	float pizza_area = (pizza_radius * pizza_radius) * pi;
	return pizza_area;
}

float price_per_square_inch(float dollar_and_cents_price, float area_sq_inch)
{
	float per_square_inch_exact = dollar_and_cents_price / area_sq_inch;
	return per_square_inch_exact;
}

int pizzacalc(void)
{
	float pizza_diameter = 0;

//pasted code that we will try to work with
	char input[100];



/*	int i;

	printf("Enter input: ");
	fgets(input, sizeof(input), stdin);

	for (i = 0; input[i] != '\0'; i++) {
		if (isalpha(input[i])) {
			printf("Invalid input: Contains letters\n");
			return 1;
		}
*/
	while (pizza_diameter <= 0)
	{


		printf("input the diameter of your pizza in inches: ");

		scanf_s("%s", input, (unsigned)_countof(input));
		sscanf_s(input, "%f", &pizza_diameter);
	
	}

	float Calculated_pizza_area = pizza_calculation(pizza_diameter);
	printf("your pizza is %f square inches \n", Calculated_pizza_area);


	float pizza_price = -1;
	
	
	while (pizza_price < 0)
	{

		printf_s("please input the price: ");
		scanf_s("%s", input, (unsigned)_countof(input));
		sscanf_s(input, "%f", &pizza_price);
	}
	
	float spending_per_square_inch = price_per_square_inch(pizza_price, Calculated_pizza_area);
	printf("the amount of money you are paying per square inch of pizza is $%f \n", spending_per_square_inch);

	int no_input_no_close = 0;
	scanf_s("%d", &no_input_no_close);

	return(0);

}
