#ifndef MEMORYMANAGEMENT
#define MEMORYMANAGEMENT

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>


#define MAXSIZE                 1024
#define INITMEMORY              0
#define BUFF                    512
#define GETFIRSTLINESIZE        13
#define ADDROFFSET              12

int ReadProcessMemory(unsigned long addr, unsigned long *tmp, unsigned int pid);
int WriteProcessMemory(unsigned long addr, unsigned long NewValue, unsigned int pid);


typedef struct _StockPid {
    pid_t pid;
    char buff[BUFF];
    char pidofbuff[BUFF];
    FILE *pid_pipe;

} StockPid; //stockthepid;

typedef struct _get_modulebase {
    char FileMaps[MAXSIZE];
    char Line[MAXSIZE];
    char GetFirstLine[GETFIRSTLINESIZE];
    char RealModule[ADDROFFSET];

    unsigned long ConvertModule;

    FILE *GetModuleBaseAddrFile;
} get_modulebase; //get_modulebaseaddr;


unsigned int GetThePid(const char *targetprocess);
unsigned long GetModuleBase(unsigned int pid, const char *module);
unsigned long long int GetRegs(unsigned int pid, struct user_regs_struct *X);

#endif
