#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *_buf;
};

int binary_semaphore_allocation (key_t key, int sem_flags)
{
  return semget(key, 1, sem_flags);
}

int binary_semaphore_deallocate (int semid)
{
  union semun ignored_argument;
  return semctl(semid, 1, IPC_RMID, ignored_argument);
}

int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl(semid, 0, SETALL, argument);
}

int binary_semaphore_wait (int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = -1;
  operations[0].sem_flg = SEM_UNDO;

  return semop(semid, operations, 1);
}

int binary_semaphore_post (int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = 1;
  operations[0].sem_flg = SEM_UNDO;

  return semop(semid, operations, 1);
}

int get_binary_semaphore_val (int semid, unsigned short *val)
{
  int ret;
  union semun argument;
  unsigned short values[1];
  argument.array = values;
  ret = semctl(semid, 0, GETALL, argument);
  *val = values[0];

  return ret;
}
