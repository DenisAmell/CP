#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <unistd.h>
#include <cstring>

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

const char* shm_name = "/my_shared_memory";
const int shm_size = 4096;
#define SHARED_MEMORY_KEY 12345
#define SEMAPHORE_KEY 54321


#define SHARED_MEMORY_SIZE 4096
#define SEMAPHORE_COUNT 1

int main() {
	int shm_fd;
	void* shm_region;


	const char* file_path = "example.txt";
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

	/*shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
	if (shm_fd < 0) {
		std::cerr << "Error creating shared memory." << std::endl;
		return 1;
	}

	ftruncate(shm_fd, shm_size);

	shm_region = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_region == MAP_FAILED) {
		std::cerr << "Error mapping shared memory." << std::endl;
		return 1;
	}*/

	int semId = semget(SEMAPHORE_KEY, SEMAPHORE_COUNT, 0666);
	if (semId == -1) {
		perror("semget");
		exit(1);
	}

	// Now you can write data to shared memory
	std::string message;

	while (1) {
		struct sembuf semOps[1] = { 0, -1, 0 }; // Операция ожидания
		semop(semId, semOps, 1);

		std::cin >> message;
		sprintf(addr,  "%s", message.c_str());

		std::cout << "Data written to shared memory." << std::endl;

		semOps[0].sem_op = 1;
		semop(semId, semOps, 1);

	}


	// To unmap and close the shared memory when you are done
	//munmap(shm_region, shm_size);
	munmap(addr, file_size);
	//close(shm_fd);

	return 0;
}