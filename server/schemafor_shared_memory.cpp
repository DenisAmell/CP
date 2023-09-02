#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

// ��������� ������, ������� ����� ��������� � ����� ������
struct SharedData {
	int counter;
};

// ������� ��� ��������� �������������� ��� ������� ����� ������
int getSharedMemoryId() {
	key_t key = ftok("shared_memory_key", 1234);
	if (key == -1) {
		perror("ftok failed");
		exit(1);
	}

	return shmget(key, sizeof(SharedData), IPC_CREAT | 0666);
}

// ������� ��� ��������� �������������� ��� ��������
int getSemaphoreId() {
	key_t key = ftok("semaphore_key", 5678);
	if (key == -1) {
		perror("ftok failed");
		exit(1);
	}

	return semget(key, 1, IPC_CREAT | 0666);
}

// ������� ��� ������������� ����� ������ � ��������
void initialize() {
	int sharedMemoryId = getSharedMemoryId();
	int semaphoreId = getSemaphoreId();

	// �������������� � ����� ������
	SharedData* sharedData = (SharedData*)shmat(sharedMemoryId, nullptr, 0);
	if (sharedData == (void*)-1) {
		perror("shmat failed");
		exit(1);
	}

	// �������������� �������� ��������
	sharedData->counter = 0;

	// �������������� �������
	semctl(semaphoreId, 0, SETVAL, 1);

	// ������������� �� ����� ������
	if (shmdt(sharedData) == -1) {
		perror("shmdt failed");
		exit(1);
	}
}

// ������� ��� ���������� �������� � ����� ������
void operateInSharedMemory() {
	int sharedMemoryId = getSharedMemoryId();
	int semaphoreId = getSemaphoreId();

	// �������������� � ����� ������
	SharedData* sharedData = (SharedData*)shmat(sharedMemoryId, nullptr, 0);
	if (sharedData == (void*)-1) {
		perror("shmat failed");
		exit(1);
	}

	// ����������� �������
	struct sembuf semaphoreOperation;
	semaphoreOperation.sem_num = 0;
	semaphoreOperation.sem_op = -1; // �������� -1 �������� ������ ��������
	semaphoreOperation.sem_flg = 0;
	if (semop(semaphoreId, &semaphoreOperation, 1) == -1) {
		perror("semop failed (semaphore capture)");
		exit(1);
	}

	// ��������� �������� � ����� ������
	sharedData->counter++;
	cout << "Counter value: " << sharedData->counter << endl;

	// ��������� �������
	semaphoreOperation.sem_num = 0;
	semaphoreOperation.sem_op = 1; // �������� 1 �������� ������������ ��������
	semaphoreOperation.sem_flg = 0;
	if (semop(semaphoreId, &semaphoreOperation, 1) == -1) {
		perror("semop failed (semaphore release)");
		exit(1);
	}

	// ������������� �� ����� ������
	if (shmdt(sharedData) == -1) {
		perror("shmdt failed");
		exit(1);
	}
}

int main() {
	initialize();

	// ��������� �������� � ����� ������ ��������� ���
	for (int i = 0; i < 5; i++) {
		operateInSharedMemory();
	}

	return 0;
}