#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/sem.h>

const char* shm_name = "/my_shared_memory";
const int shm_size = 4096;
#define SHARED_MEMORY_KEY 12345
#define SEMAPHORE_KEY 54321


#define SHARED_MEMORY_SIZE 4096
#define SEMAPHORE_COUNT 1

int main() {
	int shm_fd;
	void* shm_region;

	const char* file_path = "../server/example.txt";
	const int file_size = 100;  // Размер файла для отображения

	int fd = open(file_path, O_RDWR);
	if (fd == -1) {
		perror("Ошибка при открытии файла");
		return 1;
	}

	// Отображаем файл в память
	char* addr = (char*)mmap(NULL, file_size, O_CREAT | O_RDWR, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("Ошибка при отображении файла в память");
		close(fd);
		return 1;
	}

	close(fd);  // Файл больше не нужен

  // Файл больше не нужен

	/*shm_fd = shm_open(shm_name, O_RDONLY, 0600);
	if (shm_fd < 0) {
		std::cerr << "Error opening shared memory." << std::endl;
		return 1;
	}

	shm_region = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_region == MAP_FAILED) {
		std::cerr << "Error mapping shared memory." << std::endl;
		return 1;
	}*/
	int semId = semget(SEMAPHORE_KEY, SEMAPHORE_COUNT, IPC_CREAT | 0666);
	if (semId == -1) {
		perror("semget");
		exit(1);
	}

	while (1)
	{
		struct sembuf semOps[1] = { 0, 1, 0 }; // Операция ожидания
		semop(semId, semOps, 1);

		semOps[0].sem_op = -1;
		semop(semId, semOps, 1);
		// Now you can read data from shared memory
		std::cout << "Data read from shared memory: " << addr << std::endl;
	}


	// To unmap and close the shared memory when you are done
	/*munmap(shm_region, shm_size);*/
	munmap(addr, file_size);

	//close(shm_fd);

	return 0;
}