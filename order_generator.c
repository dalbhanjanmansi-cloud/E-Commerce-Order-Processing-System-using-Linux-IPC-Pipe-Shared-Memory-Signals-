#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
#include "common.h"

int main() {

    printf("🚀 Generator Started\n");

    int shmid = shmget(SHM_KEY, sizeof(Order)*MAX_ORDERS, 0666 | IPC_CREAT);
    Order *orders = (Order*) shmat(shmid, NULL, 0);

    // Clear shared memory once
    memset(orders, 0, sizeof(Order)*MAX_ORDERS);

    int order_id;
    int index = 0;

    while (read(0, &order_id, sizeof(int)) > 0) {

        orders[index].order_id = order_id;
        strcpy(orders[index].status, "CREATED");

        printf("\n🟢 New Order %d Created\n", order_id);

        // 🔥 IMPORTANT: Send signal to ALL (processor will handle)
        kill(0, SIGUSR1);

        index++;
        sleep(1); // small delay for clarity
    }

    return 0;
}
