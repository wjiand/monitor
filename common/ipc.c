#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ipc.h"
#include "station.h"
#include "log.h"


#define INVALID_ID	-1
#define ERROR		-1


station_t *p_stn = NULL;

int g_stninfo_shm_id = INVALID_ID;


static int create_stninfo_shm(void)
{
  int key = 0;

  // convert share memory key
  key = ftok(STNINFO_SHM_PATHNAME, STNINFO_SHM_ID);
  if(key == (key_t)-1)
  {
    zlog_error(o, "ftok error! (%s)", strerror(errno));
    return ERROR;
  }
  
  // allocates shared memory segment
  if(g_stninfo_shm_id == INVALID_ID)
  {
    g_stninfo_shm_id = shmget(key, sizeof(station_t), IPC_CREAT | 0666);
  }
  else
  {
    g_stninfo_shm_id = shmget(key, sizeof(station_t), 0666);
  }

  if(-1 == g_stninfo_shm_id)
  {
    zlog_error(o, "shmget error! (%s)", strerror(errno));
    return ERROR;
  }

  // attach the share memory
  p_stn = shmat(g_stninfo_shm_id , NULL, 0);
  if(NULL == p_stn)
  {
    zlog_error(o, "shmat error! (%s)", strerror(errno));
    return ERROR;
  }

  return 1;
}


static int delete_stninfo_shm(void)
{
  // detach the share memory
  if(shmdt(p_stn) < 0)
  { 
    zlog_error(o, "shmdt failed!");
    return ERROR;
  }

  // delete the share memory
  if(shmctl(g_stninfo_shm_id, IPC_RMID, NULL) < 0)
  { 
    zlog_error(o, "shmctl:IPC_RMID failed!");
    return ERROR;
  }
  
  return 1;
}


static int create_cmd_fifo(void)
{
  if(access(CMD_FIFO_PATHNAME, F_OK) == -1)
  {
    if(mkfifo(CMD_FIFO_PATHNAME, S_IFIFO|0777) == -1)
    {
      zlog_error(o, "mkfifo failed!");
      return ERROR;
    }

    chmod(CMD_FIFO_PATHNAME, 0777);
  }

  return 1;
}

static int delete_cmd_fifo(void)
{
  if(access(CMD_FIFO_PATHNAME, F_OK) == 0)
  {
    if(unlink(CMD_FIFO_PATHNAME) == -1)
    {
      zlog_error(o, "unlink failed!");
      return ERROR;
    }
  }

  return 1;
}


void ipc_init(void)
{
  int ret = 0;

  ret = create_stninfo_shm();
  if(ret == ERROR)
  {
    zlog_error(o, "Create station info share memory failed!");
    exit(1);
  }

  ret = create_cmd_fifo();
  if(ret == ERROR)
  {
    zlog_error(o, "Create cmd fifo failed!");
    exit(1);
  }
}


void ipc_exit(void)
{
  int ret = 0;

  ret = delete_stninfo_shm();
  if(ret == ERROR)
  {
    zlog_error(o, "Delete station info share memory failed!");
    exit(1);
  }

  ret = delete_cmd_fifo();
  if(ret == ERROR)
  {
    zlog_error(o, "Delete cmd fifo failed!");
    exit(1);
  }
}

