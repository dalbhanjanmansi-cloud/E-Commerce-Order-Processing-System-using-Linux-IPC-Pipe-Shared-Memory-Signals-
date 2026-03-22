#include <stdio.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "common.h"

Order *orders;

void dispatch_order(int sig) {

    printf("📦 Dispatcher received signal\n");

    for (int i = 0; i < MAX_ORDERS; i++) {

        if (orders[i].order_id != 0 &&
            strcmp(orders[i].status, "PROCESSED") == 0) {

            strcpy(orders[i].status, "DELIVERED");

            printf("📦 Order %d Delivered\n", orders[i].order_id);
        }
    }
}

int main() {

    printf("🚀 Dispatcher Started\n");

    signal(SIGUSR2, dispatch_order);

    int shmid = shmget(SHM_KEY, sizeof(Order)*MAX_ORDERS, 0666);
    orders = (Order*) shmat(shmid, NULL, 0);

    while (1) pause();

    return 0;
}
