#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
     signal(SIGUSR1, SIG_IGN);  // ignore signal 1
    signal(SIGUSR2, SIG_IGN);  // ignore signal 2
    int fd[2];
    pipe(fd);

    pid_t generator_pid, processor_pid, dispatcher_pid;

    generator_pid = fork();
    if (generator_pid == 0) {
        dup2(fd[0], 0);
        execl("./order_generator", "order_generator", NULL);
    }

    processor_pid = fork();
    if (processor_pid == 0) {
        execl("./order_processor", "order_processor", NULL);
    }

    dispatcher_pid = fork();
    if (dispatcher_pid == 0) {
        execl("./order_dispatcher", "order_dispatcher", NULL);
    }

    close(fd[0]);

    for (int i = 1; i <= 5; i++) {
        write(fd[1], &i, sizeof(int));
        usleep(500000);
    }

    close(fd[1]);

    wait(NULL); wait(NULL); wait(NULL);

    return 0;
}
