#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"

Order *orders;

// Signal handler
void process_order(int sig) {
    printf("⚙️ Processor received signal\n");

    for (int i = 0; i < MAX_ORDERS; i++) {

        if (orders[i].order_id != 0 &&
            strcmp(orders[i].status, "CREATED") == 0) {

            printf("⚙️ Processing Order %d...\n", orders[i].order_id);

            sleep(1);

            strcpy(orders[i].status, "PROCESSED");

            printf("✅ Order %d Processed\n", orders[i].order_id);

            kill(0, SIGUSR2); // notify dispatcher
        }
    }
}

int main() {

    printf("🚀 Processor Started\n");

    signal(SIGUSR1, process_order);

    int shmid = shmget(SHM_KEY, sizeof(Order)*MAX_ORDERS, 0666);
    orders = (Order*) shmat(shmid, NULL, 0);

    while (1) pause();

    return 0;
}
