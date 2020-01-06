#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <glob.h>
#include <sys/sysmacros.h>
#include <sys/utsname.h>
#include <sys/mount.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <linux/un.h>
#include <poll.h>
#include <assert.h>
#include <linux/if.h>
#include <linux/types.h>
#include <linux/wireless.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <dirent.h>

int shutdownProcess(char *process_name){
        const char* directory = "/proc";
        size_t  taskNameSize = 1024;
        char* taskName = (char*)calloc(1, taskNameSize);
        DIR* dir = opendir(directory);
        int arr[100];
        int count=0;
        if (dir){
                struct dirent* de = 0;
                while ((de = readdir(dir)) != 0){
                        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
                        int pid = -1;
                        int res = sscanf(de->d_name, "%d", &pid);
                        if (res == 1){
                                // we have a valid pid
                                // open the cmdline file to determine what's the name of the process running
                                char cmdline_file[1024] = {0};
                                sprintf(cmdline_file, "cat %s/%d/cmdline |xargs  -0", directory, pid);
                                FILE* cmdline = popen(cmdline_file, "r");
                                //printf("this is cmd line = [%s ]", cmdline_file);
                                if (getline(&taskName, &taskNameSize, cmdline) > 0){
                                        //printf("---------- [ %s ] \n",taskName);
                                        // is it the process we care about?
                                        if (strstr(taskName, process_name) != 0){
                                                printf( "A process, with PID %d, [ %s ] has been detected.\n", pid, process_name);
                                                arr[count]=pid;
                                                count++;
                                        }
                                }
                                pclose(cmdline);
                        }
                }
                closedir(dir);
        }
        for (int i=0;i<count;i++){
                kill(arr[i],SIGKILL); //SIGKILL can be changed too
        }
        // just let the OS free this process' memory!
        free(taskName);
        return 0;
}

int main(){
        shutdownProcess((char*)"test.py"); //change the process name as you wish to
}
