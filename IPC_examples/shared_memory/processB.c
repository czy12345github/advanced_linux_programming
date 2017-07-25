#include "shared_memory.h"

int main(int argc, char* argv[])
{
  int segment_id;
  char* shared_memory;
  char msg[100];
  struct shmid_ds shmbuffer;
  key_t key;
  const int shared_segment_size = 0x6400;

  if(argc != 2){
    printf("Usage: %s <filepath>\n", argv[0]);
    exit(0);
  }
  if((key = ftok(argv[1], 1)) == -1){
    printf("ftok failed\n");
    exit(0);
  }
  segment_id = shmget(key, shared_segment_size, IPC_CREAT | S_IRUSR | S_IWUSR);
  if(segment_id == -1){
    printf("shmget failed\n");
    exit(0);
  }
  shared_memory = shmat(segment_id, NULL, 0);
  printf("shared memory attached at address %p\n", shared_memory);
  shmctl(segment_id, IPC_STAT, &shmbuffer);
  printf("processA's pid is %d\n", shmbuffer.shm_lpid);
  printf("shm_nattch is %d\n", (unsigned)shmbuffer.shm_nattch);

  do{
    fgets(msg, 100, stdin);
    strncpy(shared_memory, msg, strlen(msg));
  }while(strncmp(msg, "quit", 4) != 0);

  strncpy(shared_memory, "quit", 4);

  shmdt(shared_memory);
  shmctl(segment_id, IPC_RMID, 0);

  return 0;
}
