#ifndef COMMON_H
#define COMMON_H

#define SHM_KEY 1234
#define MAX_ORDERS 5

typedef struct {
    int order_id;
    char status[20];
} Order;

#endif
