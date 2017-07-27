#include "binary_semaphore.h"


int main(int argc, char *argv[])
{
  int semid;
  key_t key;
  unsigned short sem_val;

  if(argc != 2){
    printf("Usage: %s <path>\n", argv[0]);
    exit(0);
  }

  printf("Initialize\n");
  semid = binary_semaphore_allocation(ftok(argv[1], 1), IPC_CREAT | S_IRUSR | S_IWUSR);
  binary_semaphore_initialize(semid);

  get_binary_semaphore_val(semid, &sem_val);
  printf("semaphore value is %d\n", sem_val);

  if(binary_semaphore_wait(semid) == -1){
    printf("error message: %s\n", strerror(errno));
  }
  get_binary_semaphore_val(semid, &sem_val);
  printf("after wait operation, semaphore value is %d\n", sem_val);

  binary_semaphore_post(semid);
  get_binary_semaphore_val(semid, &sem_val);
  printf("after post operation, semaphore value is %d\n", sem_val);

  binary_semaphore_deallocate(semid);

  return 0;
}
