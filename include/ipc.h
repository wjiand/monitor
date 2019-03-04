#ifndef _IPC_H
#define _IPC_H

#define STNINFO_SHM_PATHNAME            "/dev/shm"
#define STNINFO_SHM_ID                  0x8001

#define CMD_FIFO_PATHNAME               "/dev/shm/cmdfifo"


void ipc_init(void);
void ipc_exit(void);

#endif
