#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "log.h"


static void sig_intr_handle(int sg)
{
  int sig = sig_interrupt;

  zlog_warn(o, "Signal <SIGINT> received!");

  if(write(sigint_pipe[1], &sig, 1) == -1)
  {
    zlog_error(o, "write sigint_pipe error! (%s)", strerror(errno));
  }
/*
  //Do not close watchdog when reset system by watchdog
  if(g_wtdrst_flag != 1)
  {
    wtd_close();
  }
*/
}


static void sig_term_handle(int sg)
{
  int sig = sig_interrupt;

  zlog_warn(o, "Signal <SIGTERM> received!");

  if(write(sigint_pipe[1], &sig, 1) == -1)
  {
    zlog_error(o, "write sigint_pipe error! (%s)", strerror(errno));
  }
/*
  //Do not close watchdog when reset system by watchdog
  if(g_wtdrst_flag != 1)
  {
    wtd_close();
  }
*/
}


static void sig_pipe_handle(int sg)
{
  struct sigaction sa;

  zlog_warn(o, "Signal <SIGPIPE> received!");

  sa.sa_handler = SIG_IGN;
  sigaction(SIGPIPE, &sa, 0);
}


static void sig_chld_handle(int sg)
{
  struct sigaction sa;

  zlog_warn(o, "Signal <SIGCHLD> received!");

  sa.sa_handler = SIG_IGN;
  sigaction(SIGCHLD, &sa, 0);
}


static void system_initialize(void)
{
  ipc_init();
}


int main(void)
{
  int ret = 0;

  // Get main path
  strcpy(main_path, "/root");

  ret = log_init();
  if(ret < 0)
  {
    return -1;
  }

  zlog_info(o, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

  /* setup signal handler */
  signal(SIGINT, sig_intr_handle);
  signal(SIGTERM, sig_term_handle);
  signal(SIGPIPE, sig_pipe_handle);
  signal(SIGCHLD, sig_chld_handle);

  system_initialize();

  return 0;
}

