/*
 * Skinny Leens - Ultra-Lean Minimalist Init (PID 1)
 * Apache 2.0 License with Indigenous Sovereignty Protections
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <signal.h>
#include <errno.h>

#define TARGET_SHELL "/bin/sh"

void mount_virtual_filesystems(void) {
    // Mount proc, sysfs, and devtmpfs without external tool bloat
    if (mount("proc", "/proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL) != 0) {
        perror("skinny-init: warning: failed to mount /proc");
    }
    if (mount("sysfs", "/sys", "sysfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL) != 0) {
        perror("skinny-init: warning: failed to mount /sys");
    }
    if (mount("devtmpfs", "/dev", "devtmpfs", MS_NOSUID | MS_NOEXEC, NULL) != 0) {
        perror("skinny-init: warning: failed to mount /dev");
    }
}

void reap_zombies(int sig) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Silently reap orphaned background tasks
    }
}

int main(int argc, char *argv[]) {
    // Ensure we are PID 1
    if (getpid() != 1) {
        fprintf(stderr, "skinny-init: error: must be run as PID 1\n");
        return 1;
    }

    // Set up signal handler to prevent zombie accumulation
    struct sigaction sa;
    sa.sa_handler = reap_zombies;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    // Mount essentials
    mount_virtual_filesystems();

    // Spawn primary execution loop or shell
    pid_t pid = fork();
    if (pid < 0) {
        perror("skinny-init: fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: execute shell / local runtime manager
        char *exec_args[] = { TARGET_SHELL, NULL };
        execve(TARGET_SHELL, exec_args, NULL);
        perror("skinny-init: execve failed");
        _exit(1);
    }

    // Parent init loop: hold the line and reap
    while (1) {
        pause();
    }

    return 0;
}
