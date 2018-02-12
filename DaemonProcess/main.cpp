#include "CSpeakerDaemon.h"

int main()
{
    pid_t pid, sid;


    /* create new process */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /* exit on parent process */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* create a new session */
    sid = setsid();
    if (sid < 0) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    /* chanhe the root directory */
    if (chdir("/") < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    /* reset umask */
    umask(0);

    /* close file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* service implementation */
    CSpeakerDaemon * speaker = CSpeakerDaemon::getInstance();
    speaker->initSpeaker();

    while (1) {
        speaker->sharedMemory();
        speaker->wrtieSpeaker();
    }
    speaker->closeSpeaker();
    exit(EXIT_SUCCESS);
}
