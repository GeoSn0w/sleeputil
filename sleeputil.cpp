#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <unistd.h> //geteuid();
#include <string.h>

char offargument[] = "--off";
char onargument[] = "--on";

kern_return_t get_privileges_status(){
    
    if (geteuid() != 0){
        return KERN_FAILURE;
    } else if (geteuid() == 0){
       //Got root
    }
    return KERN_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Usage: sleeputil --off / --on\n");
        return -1;
    } else if (argc == 2){
        if (get_privileges_status() == KERN_SUCCESS){
            char *controlstring = new char[strlen(argv[1])];
            strcpy(controlstring, argv[1]);
            printf("Sleeputil by GeoSn0w (@FCE365)\nA wrapper around pmset I did for my own use.\nUse at your own risk!\n\nNOTE! Other processes may prevent sleep from occuring!\n\n");
            if (strcmp(offargument, controlstring) == 0){
                printf("Disabling sleep on this Mac...\n\n");
                system("pmset -b sleep 0");
                system("pmset -b disablesleep 1");
            } else if (strcmp(onargument, controlstring) == 0){
                printf("Enabling sleep on this Mac...\n\n");
                system("pmset -b sleep 5");
                system("pmset -b disablesleep 0");
            } else {
                printf("Usage: sleeputil --off / --on\n");
            }
        } else {
            printf("Please run this program as root. Do that with sudo\n");
        }
    } else if (argc > 2){
        printf("Too many arguments!\nUsage: sleeputil --off / --on\n");
        return -1;
    }
    return 0;
}
