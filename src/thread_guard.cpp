#include "thread_guard.h"

#include <pthread.h>
#include <bits/pthreadtypes.h>

#define _REENTRANT

using namespace std;

string client_id;

using namespace std;

void* threadGuard(void *arg)
{
  client_id = "sm";
  int port = 15000;

  struct sockaddr_in servaddr;
  int fd;
  bool ok = true;
  while(1)
  {
    ok = true;
    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      //should to continue
      ok = false;
    }
    memset(&servaddr, 0, sizeof (servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if(ok == true)
    {
      int mainsocketoption = 1;
      setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &mainsocketoption, sizeof (int));
      if(inet_aton("127.0.0.1", &servaddr.sin_addr) <= 0)
      {
        //should to continue
        close(fd);
        ok = false;
      }
      if(ok == true)
      {
        if(connect(fd, (struct sockaddr *) & servaddr, sizeof (servaddr)) < 0)
        {
          //should to continue
          close(fd);
          ok = false;
        }
        while(ok == true)
        {
          int x = write(fd, client_id.c_str(), client_id.length());
          if(x < 0)
          {
            ok = false;
            close(fd);
            sleep(300);
            break;
          }
          sleep(5);
        }
      }
    }
    sleep(30);
  }
}
