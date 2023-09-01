#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

// Структура данных, которая будет храниться в общей памяти
struct SharedData {
	int counter;
};

// Функция для получения идентификатора для объекта общей памяти
int getSharedMemoryId() {
	key_t key = ftok("shared_memory_key", 1234);
	if (key == -1) {
		perror("ftok failed");
		exit(1);
	}

	return shmget(key, sizeof(SharedData), IPC_CREAT | 0666);
}

// Функция для получения идентификатора для семафора
int getSemaphoreId() {
	key_t key = ftok("semaphore_key", 5678);
	if (key == -1) {
		perror("ftok failed");
		exit(1);
	}

	return semget(key, 1, IPC_CREAT | 0666);
}

// Функция для инициализации общей памяти и семафора
void initialize() {
	int sharedMemoryId = getSharedMemoryId();
	int semaphoreId = getSemaphoreId();

	// Присоединяемся к общей памяти
	SharedData* sharedData = (SharedData*)shmat(sharedMemoryId, nullptr, 0);
	if (sharedData == (void*)-1) {
		perror("shmat failed");
		exit(1);
	}

	// Инициализируем значение счетчика
	sharedData->counter = 0;

	// Инициализируем семафор
	semctl(semaphoreId, 0, SETVAL, 1);

	// Отсоединяемся от общей памяти
	if (shmdt(sharedData) == -1) {
		perror("shmdt failed");
		exit(1);
	}
}

// Функция для выполнения операций в общей памяти
void operateInSharedMemory() {
	int sharedMemoryId = getSharedMemoryId();
	int semaphoreId = getSemaphoreId();

	// Присоединяемся к общей памяти
	SharedData* sharedData = (SharedData*)shmat(sharedMemoryId, nullptr, 0);
	if (sharedData == (void*)-1) {
		perror("shmat failed");
		exit(1);
	}

	// Захватываем семафор
	struct sembuf semaphoreOperation;
	semaphoreOperation.sem_num = 0;
	semaphoreOperation.sem_op = -1; // Значение -1 означает захват семафора
	semaphoreOperation.sem_flg = 0;
	if (semop(semaphoreId, &semaphoreOperation, 1) == -1) {
		perror("semop failed (semaphore capture)");
		exit(1);
	}

	// Выполняем операции в общей памяти
	sharedData->counter++;
	cout << "Counter value: " << sharedData->counter << endl;

	// Отпускаем семафор
	semaphoreOperation.sem_num = 0;
	semaphoreOperation.sem_op = 1; // Значение 1 означает освобождение семафора
	semaphoreOperation.sem_flg = 0;
	if (semop(semaphoreId, &semaphoreOperation, 1) == -1) {
		perror("semop failed (semaphore release)");
		exit(1);
	}

	// Отсоединяемся от общей памяти
	if (shmdt(sharedData) == -1) {
		perror("shmdt failed");
		exit(1);
	}
}

int main() {
	initialize();

	// Повторяем операции в общей памяти несколько раз
	for (int i = 0; i < 5; i++) {
		operateInSharedMemory();
	}

	return 0;
}
