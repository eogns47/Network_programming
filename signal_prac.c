#include <signal.h>

__sighandler_t signal(int signum, __sighandler_t handler);

void print_sigint(int signo) { printf("SIG NUM %d: %d\n", signo, SIGINT); }

int main() {
  int i = 0;

  signal(SIGINT, SIG_IGN);
  while (1) {
    printf("%d\n", ++i);
    sleep(1);
  }
  return 0;
}
