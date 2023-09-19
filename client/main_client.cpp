#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/msg.h>

#define SHARED_MEMORY_KEY 12345
#define SEMAPHORE_KEY 54321

#define SHARED_MEMORY_SIZE 4096
#define SEMAPHORE_COUNT 1

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'

struct message_text
{
	int qid;
	char buf[200];
};

struct message
{
	long message_type;
	struct message_text message_text;
};

// Структура данных, которая будет храниться в shared memory
struct SharedData {
	int count;
	char msg[999];

	// Другие данные, необходимые для взаимодействия
};

using namespace std;
// Client side

void client_shered_memory() {

	char msg[1500];
	std::string command;
	// Получаем идентификатор shared memory
	int shmId = shmget(SHARED_MEMORY_KEY, SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
	std::cout << shmId << std::endl;
	if (shmId == -1) {
		perror("shmget");
		exit(1);
	}

	// Присоединяем shared memory к адресному пространству процесса клиента
	SharedData* sharedData = (SharedData*)shmat(shmId, nullptr, 0);
	if (sharedData == (SharedData*)(-1)) {
		perror("shmat");
		exit(1);
	}

	// Получаем идентификатор семафора
	int semId = semget(SEMAPHORE_KEY, SEMAPHORE_COUNT, IPC_CREAT | 0666);
	if (semId == -1) {
		perror("semget");
		exit(1);
	}

	while (sharedData->count < 10) {
		struct sembuf semOps[1] = { 0, -1, 0 }; // Операция ожидания
		semop(semId, semOps, 1);
		memset(&(sharedData->msg), 0, sizeof(sharedData->msg));
		size_t number_menu = 0;
		std::cout << "\tMENU" << std::endl;
		std::cout << "=================================" << std::endl;
		std::cout << "1. From read to console" << std::endl;
		std::cout << "2. From read to file" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "Enter: ";
		std::cin >> number_menu;
		if (number_menu == 1) {
			//send(shmId, "Command", strlen("Command"), 0);
			std::cout << "Command" << std::endl;
			memset(&(sharedData->msg), 0, sizeof(sharedData->msg)); // clear the buffer
			strcpy(sharedData->msg, "Command");
			semOps[0].sem_op = 1;
			semop(semId, semOps, 1);


			while (true) {

				semOps[0].sem_op = -1;
				semop(semId, semOps, 1);

				std::getline(std::cin, command);
				memset(&(sharedData->msg), 0, sizeof(sharedData->msg)); // clear the buffer
				strcpy(sharedData->msg, command.c_str());
				if (command == "Exit") break;
				semOps[0].sem_op = 1;
				semop(semId, semOps, 1);


			}
		}
		else if (number_menu == 2) {
			//send(shmId, "File", strlen("File"), 0);
			memset(&(sharedData->msg), 0, sizeof(sharedData->msg)); // clear the buffer
			strcpy(sharedData->msg, "File");
			semOps[0].sem_op = 1;
			semop(semId, semOps, 1);

			semOps[0].sem_op = -1;
			semop(semId, semOps, 1);
			std::string file_name;
			std::cout << "Enter name file ";
			std::cin >> file_name;


			memset(&(sharedData->msg), 0, sizeof(sharedData->msg)); // clear the buffer
			strcpy(sharedData->msg, file_name.c_str());


		}
		else if (number_menu == 3) {
			memset(&(sharedData->msg), 0, sizeof(msg)); // clear the buffer
			strcpy(sharedData->msg, "Exit");
			//send(semId, (char*)&msg, strlen(msg), 0);
			//sharedData->command = "Exit";
			std::cout << "Count: " << sharedData->count << std::endl;

			semOps[0].sem_op = 1; // Операция увеличения
			semop(semId, semOps, 1);
			break;
		}

		sharedData->count++;

		std::cout << "Count: " << sharedData->count << std::endl;

		semOps[0].sem_op = 1; // Операция увеличения
		semop(semId, semOps, 1);
	}
	// Отсоединяем shared memory

	// Отсоединяем shared memory
	shmdt(sharedData);

	// Удаляем shared memory
	shmctl(shmId, IPC_RMID, nullptr);

	// Удаляем семафор
	semctl(semId, 0, IPC_RMID);
}


int soket(int argc, char* argv[], int port_tmp) {
	// we need 2 things: ip address and port number, in that order
	if (argc != 3)
	{
		cerr << "Usage: ip_address port" << endl;
		exit(0);
	} // grab the IP address and port number
	char* serverIp = argv[1];
	int port = 1234;
	std::cout << port << std::endl;
	// create a message buffer
	char msg[1500];
	// setup a socket and connection tools
	struct hostent* host = gethostbyname(serverIp);
	sockaddr_in sendSockAddr;
	bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
	sendSockAddr.sin_family = AF_INET;
	sendSockAddr.sin_addr.s_addr =
		inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	sendSockAddr.sin_port = htons(port);
	int clientSd = socket(AF_INET, SOCK_STREAM, 0);
	// try to connect...
	int status = connect(clientSd,
		(sockaddr*)&sendSockAddr, sizeof(sendSockAddr));
	if (status < 0)
	{
		cout << "Error connecting to socket!" << endl;
		return -1;
	}
	cout << "Connected to the server!" << endl;
	int bytesRead, bytesWritten = 0;
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);

	std::string command;


	try {

		while (true) {
			size_t number_menu = 0;
			std::cout << "\tMENU" << std::endl;
			std::cout << "=================================" << std::endl;
			std::cout << "1. From read to console" << std::endl;
			std::cout << "2. From read to file" << std::endl;
			std::cout << "3. Exit" << std::endl;
			std::cout << "Enter: ";
			std::cin >> number_menu;


			if (number_menu == 1) {
				bytesWritten += send(clientSd, "Command", strlen("Command"), 0);
				while (true) {

					std::getline(std::cin, command);

					//if (command.length() == 0) continue;

					if (command == "Exit") {
						memset(&msg, 0, sizeof(msg)); // clear the buffer
						strcpy(msg, command.c_str());
						bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
						break;
					}

					memset(&msg, 0, sizeof(msg)); // clear the buffer
					strcpy(msg, command.c_str());
					bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);

				}
			}
			else if (number_menu == 2) {
				bytesWritten += send(clientSd, "File", strlen("File"), 0);
				std::string file_name;
				std::cout << "Enter name file ";
				std::cin >> file_name;
				memset(&msg, 0, sizeof(msg)); // clear the buffer
				strcpy(msg, file_name.c_str());
				bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
			}
			else if (number_menu == 3) {
				memset(&msg, 0, sizeof(msg)); // clear the buffer
				strcpy(msg, "Exit");
				bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
				break;
			}
			else
				throw std::logic_error("Error input!");

		}
	}
	catch (std::logic_error const& ex) {
		std::cout << ex.what() << std::endl;
	}

	gettimeofday(&end1, NULL);
	close(clientSd);
	cout << "********Session********" << endl;
	cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
	cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
		<< " secs" << endl;
	cout << "Connection closed" << endl;

	return 0;
}

void message_queues()
{
	key_t server_queue_key;
	int server_qid, myqid;
	struct message my_message, return_message;

	// create my client queue for receiving messages from server
	if ((myqid = msgget(IPC_PRIVATE, 0660)) == -1)
	{
		perror("msgget: myqid");
		exit(1);
	}

	if ((server_queue_key = ftok(SERVER_KEY_PATHNAME, PROJECT_ID)) == -1)
	{
		perror("ftok");
		exit(1);
	}

	if ((server_qid = msgget(server_queue_key, 0)) == -1)
	{
		perror("msgget: server_qid");
		exit(1);
	}

	my_message.message_type = 1;
	my_message.message_text.qid = myqid;

	printf("Please type a message: ");

	std::string command;

	while (1)
	{
		size_t number_menu = 0;
		std::cout << "\tMENU" << std::endl;
		std::cout << "=================================" << std::endl;
		std::cout << "1. From read to console" << std::endl;
		std::cout << "2. From read to file" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "Enter: ";
		std::cin >> number_menu;

		if (number_menu == 1)
		{
			strcpy(my_message.message_text.buf, "Command");
			if (msgsnd(server_qid, &my_message, sizeof(struct message_text), 0) == -1)
			{
				perror("client: msgsnd");
				exit(1);
			}
			while (1)
			{

				std::getline(std::cin, command);

				if (command == "Exit")
				{
					strcpy(my_message.message_text.buf, "Exit");
					if (msgsnd(server_qid, &my_message, sizeof(struct message_text), 0) == -1)
					{
						perror("client: msgsnd");
						exit(1);
					}
					break;
				}

				strcpy(my_message.message_text.buf, command.c_str());
				if (msgsnd(server_qid, &my_message, sizeof(struct message_text), 0) == -1)
				{
					perror("client: msgsnd");
					exit(1);
				}
			}
		}
		if (number_menu == 2)
		{
			std::string file_name;
			strcpy(my_message.message_text.buf, "File");
			std::cout << my_message.message_text.buf << std::endl;
			if (msgsnd(server_qid, &my_message, sizeof(struct message_text), 0) == -1)
			{
				perror("client: msgsnd");
				exit(1);
			}
			std::cout << "Enter name file ";
			std::cin >> file_name;

			strcpy(my_message.message_text.buf, file_name.c_str());

			if (msgsnd(server_qid, &my_message, sizeof(struct message_text), 0) == -1)
			{
				perror("client: msgsnd");
				exit(1);
			}
		}
		if (number_menu == 3) {
			strcpy(my_message.message_text.buf, "Exit");
			if (msgsnd(server_qid, &my_message, sizeof(struct message_text), 0) == -1)
			{
				perror("client: msgsnd");
				exit(1);
			}
			break;
		}

	}
	// remove message queue
	if (msgctl(myqid, IPC_RMID, NULL) == -1)
	{
		perror("client: msgctl");
		exit(1);
	}

	printf("Client: bye\n");
}

int main(int argc, char* argv[]) {

	if (argc != 3)
	{
		cerr << "Usage: ip_address port" << endl;
		exit(0);
	} // grab the IP address and port number
	char* serverIp = argv[1];
	int port = atoi(argv[2]);
	// create a message buffer
	char msg[1500];
	// setup a socket and connection tools
	struct hostent* host = gethostbyname(serverIp);
	sockaddr_in sendSockAddr;
	bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
	sendSockAddr.sin_family = AF_INET;
	sendSockAddr.sin_addr.s_addr =
		inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	sendSockAddr.sin_port = htons(port);
	int clientSd = socket(AF_INET, SOCK_STREAM, 0);
	// try to connect...
	int status = connect(clientSd,
		(sockaddr*)&sendSockAddr, sizeof(sendSockAddr));
	if (status < 0)
	{
		cout << "Error connecting to socket!" << endl;
		return -1;
	}
	cout << "Connected to the server!" << endl;
	int bytesRead, bytesWritten = 0;
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);


	std::string number_menu;
	std::cout << "\tMENU IPC" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << "1. Shared memory" << std::endl;
	std::cout << "2. Soket" << std::endl;
	std::cout << "3. Message queues" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << "Enter: ";
	std::cin >> number_menu;


	std::cout << number_menu << std::endl;
	if (number_menu == "1") {

		bytesWritten += send(clientSd, (number_menu.substr(0, number_menu.find("\r"))).c_str(), strlen(number_menu.c_str()), 0);
		client_shered_memory();

	}
	if (number_menu == "2") {

		bytesWritten += send(clientSd, (number_menu.substr(0, number_menu.find("\r"))).c_str(), strlen(number_menu.c_str()), 0);
		soket(argc, argv, port);
	}
	if (number_menu == "3") {
		bytesWritten += send(clientSd, (number_menu.substr(0, number_menu.find("\r"))).c_str(), strlen(number_menu.c_str()), 0);
		message_queues();
	}



	gettimeofday(&end1, NULL);
	close(clientSd);
	cout << "********Session********" << endl;
	cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
	cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
		<< " secs" << endl;
	cout << "Connection closed" << endl;


	return 0;
}