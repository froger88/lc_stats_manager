/* 
 * File:   main.cpp
 * Author: froger
 *
 * Created on 26 wrzesień 2009, 21:58
 */
#include "main.h"

using namespace std;

int main()
{
  string CROSS = "    ++\n    ++\n    ++\n++++++++++\n++++++++++\n    ++\n    ++\n    ++\n    ++\n    ++\n    ++\n    ++";
  cout << CROSS << endl; //krzyza nic nie ruszy @wydarzenia z sierpnia 2010
  pthread_t Thread;
  pthread_attr_t AttrThread;

  pthread_setconcurrency(1);
  pthread_attr_init(&AttrThread);
  pthread_attr_setdetachstate(&AttrThread, PTHREAD_CREATE_DETACHED);

  int cpid = (int) pthread_create(&Thread, &AttrThread, threadGuard, NULL);
  if(cpid != 0)
  {
    return EXIT_FAILURE;
  }

  int timeStart;
  int timeStop;
  int TL = 25;
  int timer2 = (time_t) time(NULL);
  int TL2 = 14400;
  string run;
  while(1)
  {
    timeStart = (time_t) time(NULL);
    run = "nice -n 16 php5 /srv/www/lc.web-anatomy.com/admin/cron/statistics.php >> /dev/null";
    system(run.c_str());
    timeStop = (time_t) time(NULL);
    if(timeStop >= timer2 + TL2)//uruchom drugi skrypt
    {
      timer2 = (time_t) time(NULL);
      run = "nice -n 16 php5 /srv/www/lc.web-anatomy.com/admin/cron/clear_ip.php >> /dev/null";
      system(run.c_str());
    }
    if(timeStart - timeStop + TL > 0)
    {
      sleep(timeStart - timeStop + TL);
    }
  }
  return (EXIT_SUCCESS);
}

