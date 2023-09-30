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
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>


#include "../database_singleton.h"
// #include "abstract_handler.h"
// #include "commands/command.h"
#include "../commands/command_add_pool.h"
#include "../commands/command_add_scheme.h"
#include "../commands/command_add_collection.h"
#include "../commands/command_add_data.h"
#include "../commands/command_get_data.h"
#include "../commands/command_remove_pool.h"
#include "../commands/command_remove_scheme.h"
#include "../commands/command_remove_collection.h"
#include "../commands/command_remove_data.h"
#include "../commands/command_update_data.h"
#include "../commands/command_get_data_between.h"
#include <fstream>
#include "../request_handler_with_command_chain.h"
#include "../tree/tree_type.h"


#define SHARED_MEMORY_KEY 12345
#define SEMAPHORE_KEY 54321

#define SHARED_MEMORY_SIZE 4096
#define SEMAPHORE_COUNT 1

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660


using namespace std;

struct SharedData {
	int count;
	char msg[999];
	// Другие данные, необходимые для взаимодействия
};

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


void shered_memory_semaphore() {

	// Получаем идентификатор shared memory
	int shmId = shmget(SHARED_MEMORY_KEY, SHARED_MEMORY_SIZE, 0666);
	if (shmId == -1) {
		perror("shmget");
		exit(1);
	}

	// Присоединяем shared memory к адресному пространству процесса сервера
	SharedData* sharedData = (SharedData*)shmat(shmId, nullptr, 0);
	if (sharedData == (SharedData*)(-1)) {
		perror("shmat");
		exit(1);
	}

	// Получаем идентификатор семафора
	int semId = semget(SEMAPHORE_KEY, SEMAPHORE_COUNT, 0666);
	if (semId == -1) {
		perror("semget");
		exit(1);
	}

	database_singleton* db = new database_singleton();

	std::string command;
	char msg[1500];

	request_handler_with_command_chain<std::string> chain;
	chain.add_handler(new command_add_pool())
		.add_handler(new command_add_scheme())
		.add_handler(new command_add_collection())
		.add_handler(new command_add_data())
		.add_handler(new command_get_data())
		.add_handler(new command_remove_pool())
		.add_handler(new command_remove_scheme())
		.add_handler(new command_remove_collection())
		.add_handler(new command_remove_data())
		.add_handler(new command_update_data())
		.add_handler(new command_get_data_between());

	while (sharedData->count < 10) {
		struct sembuf semOps[1] = { 0, 1, 0 }; // Операция ожидания
		semop(semId, semOps, 1);

		// Увеличиваем count на 1
		//sharedData->count++;
		// Оповещаем клиента
		semOps[0].sem_op = -1; // Операция увеличения
		semop(semId, semOps, 1);

		std::string tmp = sharedData->msg;

		if (tmp == "Exit") break;

		if (tmp == "Command") {
			while (true) {
				semOps[0].sem_op = 1;
				semop(semId, semOps, 1);
				semOps[0].sem_op = -1;
				semop(semId, semOps, 1);

				command = sharedData->msg;

				if (command == "Exit") break;

				if (!chain.handle(command))
				{
					std::cout << "[DATA BASE] command can't be executed" << std::endl
						<< std::endl;
				}

			}
		}
		else if (tmp == "File") {


			semOps[0].sem_op = 1; // Операция увеличения
			semop(semId, semOps, 1);
			std::cout << "gg " << std::endl;
			semOps[0].sem_op = -1;
			semop(semId, semOps, 1);
			std::string file_name = sharedData->msg;
			std::string command;
			std::ifstream file(file_name);

			if (file.is_open())
			{
				while (std::getline(file, command))
				{
					if (!chain.handle(command))
					{
						std::cout << "[DATA BASE] command can't be executed" << std::endl
							<< std::endl;
					}
				}
			}
			else
			{
				std::cout << "File with name:" << sharedData->msg << " can't be opened" << std::endl;
				continue;
			}


		}
	}


	shmdt(sharedData);


}

void soket(int argc, char* argv[], int port_tmp) {
	//// for the server, we only need to specify a port number
	if (argc != 2)
	{
		cerr << "Usage: port" << endl;
		exit(0);
	}
	// grab the port number
	int port = 1234;
	// buffer to send and receive messages with
	char msg[1500];

	// setup a socket and connection tools
	sockaddr_in servAddr;
	bzero((char*)&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	// open stream oriented socket with internet address
	// also keep track of the socket descriptor
	int serverSd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSd < 0)
	{
		cerr << "Error establishing the server socket" << endl;
		exit(0);
	}
	// bind the socket to its local address
	int bindStatus = bind(serverSd, (struct sockaddr*)&servAddr,
		sizeof(servAddr));
	if (bindStatus < 0)
	{
		cerr << "Error binding socket to local address" << endl;
		exit(0);
	}
	cout << "Waiting for a client to connect..." << endl;
	// listen for up to 5 requests at a time
	listen(serverSd, 5);
	// receive a request from client using accept
	// we need a new address to connect with the client
	sockaddr_in newSockAddr;
	socklen_t newSockAddrSize = sizeof(newSockAddr);
	// accept, create a new socket descriptor to
	// handle the new connection with client
	int newSd = accept(serverSd, (sockaddr*)&newSockAddr, &newSockAddrSize);
	if (newSd < 0)
	{
		cerr << "Error accepting request from client!" << endl;
		exit(1);
	}
	cout << "Connected with client!" << endl;
	// lets keep track of the session time
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);
	// also keep track of the amount of data sent as well
	int bytesRead, bytesWritten = 0;

	database_singleton* db = new database_singleton();

	std::string command;

	request_handler_with_command_chain<std::string> chain;
	chain.add_handler(new command_add_pool())
		.add_handler(new command_add_scheme())
		.add_handler(new command_add_collection())
		.add_handler(new command_add_data())
		.add_handler(new command_get_data())
		.add_handler(new command_remove_pool())
		.add_handler(new command_remove_scheme())
		.add_handler(new command_remove_collection())
		.add_handler(new command_remove_data())
		.add_handler(new command_update_data())
		.add_handler(new command_get_data_between());

	while (1)
	{
		memset(&msg, 0, sizeof(msg)); // clear the buffer
		bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

		if (strcmp(msg, "Exit") == 0) break;

		if (strcmp(msg, "Command") == 0) {

			while (1) {
				memset(&msg, 0, sizeof(msg));
				bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

				if (!strcmp(msg, "Exit")) break;

				if (!chain.handle(msg))
				{
					std::cout << "[DATA BASE] command can't be executed" << std::endl
						<< std::endl;
				}
			}
		}
		else if (strcmp(msg, "File") == 0) {

			memset(&msg, 0, sizeof(msg));
			bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

			std::string command;
			std::ifstream file(msg);
			if (file.is_open())
			{
				while (std::getline(file, command))
				{
					if (!chain.handle(command))
					{
						std::cout << "[DATA BASE] command can't be executed" << std::endl
							<< std::endl;
					}
				}
			}
			else
			{
				std::cout << "File with name:" << msg << " can't be opened" << std::endl;
				continue;
			}

		}
	}
	// we need to close the socket descriptors after we're all done
	gettimeofday(&end1, NULL);
	close(newSd);
	close(serverSd);
	cout << "********Session********" << endl;
	cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
	cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
		<< " secs" << endl;
	cout << "Connection closed..." << endl;
}


void message_queues()
{
	key_t msg_queue_key;
	int qid;
	struct message message;

	if ((msg_queue_key = ftok(SERVER_KEY_PATHNAME, PROJECT_ID)) == -1)
	{
		perror("ftok");
		exit(1);
	}

	if ((qid = msgget(msg_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1)
	{
		perror("msgget");
		exit(1);
	}

	database_singleton* db = new database_singleton();

	std::string command;

	request_handler_with_command_chain<std::string> chain;
	chain.add_handler(new command_add_pool())
		.add_handler(new command_add_scheme())
		.add_handler(new command_add_collection())
		.add_handler(new command_add_data())
		.add_handler(new command_get_data())
		.add_handler(new command_remove_pool())
		.add_handler(new command_remove_scheme())
		.add_handler(new command_remove_collection())
		.add_handler(new command_remove_data())
		.add_handler(new command_update_data())
		.add_handler(new command_get_data_between());

	printf("Server: Hello, World!\n");

	while (1)
	{
		// read an incoming message
		if (msgrcv(qid, &message, sizeof(struct message_text), 0, 0) == -1)
		{
			perror("msgrcv");
			exit(1);
		}

		if (strcmp(message.message_text.buf, "Exit") == 0)
			break;

		if (strcmp(message.message_text.buf, "Command") == 0)
		{
			while (1)
			{
				std::cout << "gg" << std::endl;
				if (msgrcv(qid, &message, sizeof(struct message_text), 0, 0) == -1)
				{
					perror("msgrcv");
					exit(1);
				}

				if (strlen(message.message_text.buf) == 0)
					continue;
				std::cout << message.message_text.buf << std::endl;
				if (!strcmp(message.message_text.buf, "Exit"))
					break;

				if (!chain.handle(message.message_text.buf))
				{
					std::cout << "[DATA BASE] command can't be executed" << std::endl
						<< std::endl;
				}
			}
		}
		if (strcmp(message.message_text.buf, "File") == 0)
		{
			if (msgrcv(qid, &message, sizeof(struct message_text), 0, 0) == -1)
			{
				perror("msgrcv");
				exit(1);
			}

			std::cout << message.message_text.buf << std::endl;
			std::string command;
			std::ifstream file(message.message_text.buf);
			if (file.is_open())
			{
				while (std::getline(file, command))
				{
					if (!chain.handle(command))
					{
						std::cout << "[DATA BASE] command can't be executed" << std::endl
							<< std::endl;
					}
				}
			}
			else
			{
				std::cout << "File with name:" << message.message_text.buf << " can't be opened" << std::endl;
				continue;
			}
		}

		printf("Server: message received.\n");
	}
}

int file_mapping() {
	int shm_fd;
	void* shm_region;


	const char* file_path = "../example.txt";
	const int file_size = 100;
	int fd = open(file_path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("Ошибка при открытии файла");
		return 1;
	}

	// Установка размера файла
	lseek(fd, file_size - 1, SEEK_SET);
	write(fd, "", 1);

	// Отображаем файл в память
	char* addr = (char*)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("Ошибка при отображении файла в память");
		close(fd);
		return 1;
	}

	close(fd);


	int semId = semget(SEMAPHORE_KEY, SEMAPHORE_COUNT, 0666);
	if (semId == -1) {
		perror("semget");
		exit(1);
	}

	// Now you can write data to shared memory
	std::string message;


	database_singleton* db = new database_singleton();

	std::string command;
	char msg[1500];

	request_handler_with_command_chain<std::string> chain;
	chain.add_handler(new command_add_pool())
		.add_handler(new command_add_scheme())
		.add_handler(new command_add_collection())
		.add_handler(new command_add_data())
		.add_handler(new command_get_data())
		.add_handler(new command_remove_pool())
		.add_handler(new command_remove_scheme())
		.add_handler(new command_remove_collection())
		.add_handler(new command_remove_data())
		.add_handler(new command_update_data())
		.add_handler(new command_get_data_between());


	while (1) {
		struct sembuf semOps[1] = { 0, 1, 0 }; // Операция ожидания
		semop(semId, semOps, 1);
		// Оповещаем клиента
		semOps[0].sem_op = -1; // Операция увеличения
		semop(semId, semOps, 1);

		std::string tmp = addr;

		if (tmp == "Exit") break;

		if (tmp == "Command") {
			while (true) {
				semOps[0].sem_op = 1;
				semop(semId, semOps, 1);
				semOps[0].sem_op = -1;
				semop(semId, semOps, 1);

				command = addr;

				std::cout << command << std::endl;

				if (command == "Exit") break;

				if (!chain.handle(command))
				{
					std::cout << "[DATA BASE] command can't be executed" << std::endl
						<< std::endl;
				}

			}
		}
		else if (tmp == "File") {
			semOps[0].sem_op = 1; // Операция увеличения
			semop(semId, semOps, 1);
			std::cout << "gg " << std::endl;
			semOps[0].sem_op = -1;
			semop(semId, semOps, 1);
			std::string file_name = addr;
			std::string command;
			std::ifstream file(file_name);

			if (file.is_open())
			{
				while (std::getline(file, command))
				{
					if (!chain.handle(command))
					{
						std::cout << "[DATA BASE] command can't be executed" << std::endl
							<< std::endl;
					}
				}
			}
			else
			{
				std::cout << "File with name:" << file_name << " can't be opened" << std::endl;
				continue;
			}
		}

	}


	// To unmap and close the shared memory when you are done
	//munmap(shm_region, shm_size);
	munmap(addr, file_size);
	//close(shm_fd);
}

int main(int argc, char* argv[])
{


	if (argc != 2)
	{
		cerr << "Usage: port" << endl;
		exit(0);
	}
	// grab the port number
	int port = atoi(argv[1]);
	// buffer to send and receive messages with
	char msg[1500];

	// setup a socket and connection tools
	sockaddr_in servAddr;
	bzero((char*)&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	// open stream oriented socket with internet address
	// also keep track of the socket descriptor
	int serverSd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSd < 0)
	{
		cerr << "Error establishing the server socket" << endl;
		exit(0);
	}
	// bind the socket to its local address
	int bindStatus = bind(serverSd, (struct sockaddr*)&servAddr,
		sizeof(servAddr));
	if (bindStatus < 0)
	{
		cerr << "Error binding socket to local address" << endl;
		exit(0);
	}
	cout << "Waiting for a client to connect..." << endl;
	// listen for up to 5 requests at a time
	listen(serverSd, 5);
	// receive a request from client using accept
	// we need a new address to connect with the client
	sockaddr_in newSockAddr;
	socklen_t newSockAddrSize = sizeof(newSockAddr);
	// accept, create a new socket descriptor to
	// handle the new connection with client
	int newSd = accept(serverSd, (sockaddr*)&newSockAddr, &newSockAddrSize);
	if (newSd < 0)
	{
		cerr << "Error accepting request from client!" << endl;
		exit(1);
	}
	cout << "Connected with client!" << endl;
	// lets keep track of the session time
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);
	int bytesRead, bytesWritten = 0;



	//memset(&msg, 0, sizeof(msg)); // clear the buffer
	bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

	int mode_ipc = atoi(msg);

	std::cout << mode_ipc << std::endl;
	switch (mode_ipc) {
	case 1:
		shered_memory_semaphore();
		break;
	case 2:
		soket(argc, argv, port);
		break;
	case 3:
		message_queues();
		break;
	case 4:
		file_mapping();
		break;
	default:
		break;
	}



	// also keep track of the amount of data sent as wel
	// we need to close the socket descriptors after we're all done
	gettimeofday(&end1, NULL);
	close(newSd);
	close(serverSd);
	cout << "********Session********" << endl;
	cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
	cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
		<< " secs" << endl;
	cout << "Connection closed..." << endl;


	return 0;

}