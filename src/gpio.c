#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define LOW 0
#define HIGH 1
#define IN 0
#define OUT 1

int GPIOExport(int pin) {
    #define BUFFER_MAX 3
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open export for writing!\n");
        return -1;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return 0;
}

int GPIOUnexport(int pin) {
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open unexport for writing!\n");
        return -1;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return 0;
}

int GPIODirection(int pin, int dir) {
    static const char s_directions_str[] = "in\0out";
    #define DIRECTION_MAX 35
    char path[DIRECTION_MAX];
    int fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open gpio direction for writing\n");
        return -1;
    }

    if (write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3) == -1) {
        fprintf(stderr, "Failed to set direction!\n");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int GPIOWrite(int pin, int value) {
    char path[35];
    int fd;
    snprintf(path, 35, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open gpio value for writing\n");
        return -1;
    }

    if (write(fd, value == LOW ? "0" : "1", 1) != 1) {
        fprintf(stderr, "Failed to write value!\n");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int GPIORead(int pin) {
    char path[35];
    char value_str[3];
    int fd;
    snprintf(path, 35, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open gpio value for reading\n");
        return -1;
    }

    if (read(fd, value_str, 3) == -1) {
        fprintf(stderr, "Failed to read value!\n");
        close(fd);
        return -1;
    }

    close(fd);
    return atoi(value_str);
}
