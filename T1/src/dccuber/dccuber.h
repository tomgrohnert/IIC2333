#include <stdlib.h>

void handle_state(int sig, siginfo_t *siginfo, void *context);

void handle_sigint(int sig);

void handle_sigabrt_1(int sig);

void handle_sigabrt_2(int sig);

void handle_sigabrt_3(int sig);