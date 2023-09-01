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

#define SHARED_MEMORY_KEY 12345
#define SEMAPHORE_KEY 54321

#define SHARED_MEMORY_SIZE 4096
#define SEMAPHORE_COUNT 1

// Структура данных, которая будет храниться в shared memory
struct SharedData {
	int count;
	char msg[999];

	// Другие данные, необходимые для взаимодействия
};

using namespace std;
// Client side


void blyat() {
	// Получаем идентификатор shared memory
	int shmId = shmget(SHARED_MEMORY_KEY, SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
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
	int semId = semget(SEMAPHORE_KEY, SEMAPHORE_COUNT, IPC_CREAT | 0666);
	if (semId == -1) {
		perror("semget");
		exit(1);
	}

	while (sharedData->count < 10) {
		// Ждем, пока клиент будет готов
		struct sembuf semOps[1] = { 0, -1, 0 }; // Операция ожидания
		semop(semId, semOps, 1);

		// Увеличиваем count на 1
		sharedData->count++;

		// Оповещаем клиента
		semOps[0].sem_op = 1; // Операция увеличения
		semop(semId, semOps, 1);
	}

	// Отсоединяем shared memory
	shmdt(sharedData);

	// Удаляем shared memory
	shmctl(shmId, IPC_RMID, nullptr);

	// Удаляем семафор
	semctl(semId, 0, IPC_RMID);
}

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
			/*std::cout << "Command" << std::endl;
			sharedData->command = "Command";
			semOps[0].sem_op = -1;
			semop(semId, semOps, 1);*/
			while (true) {
				/*std::getline(std::cin, command);
				sharedData->command = command;
				semOps[0].sem_op = -1;
				semop(semId, semOps, 1);*/
				//cout << "Awaiting server response..." << endl;
				//memset(&msg, 0, sizeof(msg)); // clear the buffer
				//bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
				//if (!strcmp(msg, "exit"))
				//{
				//	cout << "Server has quit the session" << endl;
				//	break;
				//}
				//cout << "Server: " << msg << endl;
				/*if (command.starts_with("-1")) break;

				if (!chain.handle(command) && command != "")
				{
					std::cout << "[DATA BASE] command can't be executed" << std::endl
						<< std::endl;
				}*/

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
	int port = 12347;
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

					if (command == "Exit") {
						memset(&msg, 0, sizeof(msg)); // clear the buffer
						strcpy(msg, command.c_str());
						bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
						break;
					}

					memset(&msg, 0, sizeof(msg)); // clear the buffer
					strcpy(msg, command.c_str());
					bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
					//cout << "Awaiting server response..." << endl;
					//memset(&msg, 0, sizeof(msg)); // clear the buffer
					//bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
					//if (!strcmp(msg, "exit"))
					//{
					//	cout << "Server has quit the session" << endl;
					//	break;
					//}
					//cout << "Server: " << msg << endl;
					/*if (command.starts_with("-1")) break;

					if (!chain.handle(command) && command != "")
					{
						std::cout << "[DATA BASE] command can't be executed" << std::endl
							<< std::endl;
					}*/

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
	std::cout << "3. Exit" << std::endl;
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



	gettimeofday(&end1, NULL);
	close(clientSd);
	cout << "********Session********" << endl;
	cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
	cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
		<< " secs" << endl;
	cout << "Connection closed" << endl;


	return 0;
}