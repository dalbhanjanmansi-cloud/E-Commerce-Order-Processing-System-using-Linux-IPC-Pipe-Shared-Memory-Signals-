# E-Commerce Order Processing System using Linux IPC

## Overview

This project implements a basic E-Commerce order processing system using multiple processes in Linux. It demonstrates how processes communicate using IPC mechanisms like Pipe, Shared Memory, and Signals.

---

## System Components

### Order Generator

* Creates new orders
* Sends order IDs using pipe
* Stores order data in shared memory

### Order Processor

* Reads orders from shared memory
* Processes the orders
* Updates status to "PROCESSED"
* Sends signal to dispatcher

### Order Dispatcher

* Reads processed orders
* Marks them as "DELIVERED"
* Displays final output

---

## Workflow

1. Orders are created by the generator
2. Orders are passed using pipe
3. Shared memory is used to store order data
4. Processor updates order status
5. Signals are used for communication
6. Dispatcher completes the process

---

## Technologies Used

* C Programming
* Linux Operating System
* Pipe
* Shared Memory
* Signals

---

## How to Run

### Compile

gcc order_generator.c -o order_generator
gcc order_processor.c -o order_processor
gcc order_dispatcher.c -o order_dispatcher
gcc main.c -o main

### Run

./main

---

## Features

* Multi-process implementation
* Use of IPC mechanisms
* Simple and clear workflow

---

## Future Improvements

* Add message queue
* Add file or database storage
* Improve user interface

---

## Author
Mansi Dalbhanjan

Your Name
