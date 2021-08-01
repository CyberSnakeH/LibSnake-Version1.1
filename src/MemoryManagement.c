#include <stdio.h>
#include "MemoryManagement.h"

static StockPid stockthepid;

static get_modulebase get_modulebaseaddr;

int ReadProcessMemory(unsigned long addr, unsigned long *tmp, unsigned int pid) {
    long ret;

    int err_code = ptrace(PTRACE_ATTACH, pid, NULL, NULL);

    if (err_code == -1) {
        printf("Error we can't attach the process ! \n");
        return -1;
    }

    usleep(1000);

    ret = ptrace(PTRACE_PEEKDATA, pid, addr, NULL);

    if (ret == -1) {
        printf("Error we can't peak data \n");
        return -1;
    }

    err_code = ptrace(PTRACE_DETACH, pid, NULL, NULL);

    if (err_code == -1) {
        printf("Error we can't dettach the process ! \n");
        return -1;
    }

    *tmp = ret;

    return 1;
}

int WriteProcessMemory(unsigned long addr, unsigned long NewValue, unsigned int pid) {
    long tmp;

    int err_code = ptrace(PTRACE_ATTACH, pid, NULL, NULL);

    if (err_code == -1) {
        printf("Error we can't attach the process ! \n");
        return -1;
    }

    usleep(15*1000);

    for (int i = 0; i < 1; i++) {
        tmp = ptrace(PTRACE_POKEDATA, pid, addr, NewValue);

        if (tmp == -1) {
            printf("Error we can't peek data ! \n");
        }
    }

    err_code = ptrace(PTRACE_DETACH, pid, NULL, NULL);
    if (err_code == -1) {
        printf("Error we can't detach the process ! \n");
    }
    
    return tmp;
}


unsigned int GetThePid(const char *targetprocess) {
    sprintf(stockthepid.pidofbuff, "pidof -s %s", targetprocess);
    stockthepid.pid_pipe = popen(stockthepid.pidofbuff, "r");
    char *ppp = fgets(stockthepid.buff, BUFF, stockthepid.pid_pipe);
    stockthepid.pid = strtoul(stockthepid.buff, NULL, 10);

    if (stockthepid.pid == 0) {
        printf("Application is not launch ! \n");
        pclose(stockthepid.pid_pipe);
        exit(-1);
    } else {
        pclose(stockthepid.pid_pipe);
    }

    return stockthepid.pid;
}

unsigned long GetModuleBase(unsigned int pid, const char *module) {
    memset(get_modulebaseaddr.FileMaps, INITMEMORY, MAXSIZE);
    memset(get_modulebaseaddr.Line, INITMEMORY, MAXSIZE);
    memset(get_modulebaseaddr.GetFirstLine, INITMEMORY, GETFIRSTLINESIZE);

    sprintf(get_modulebaseaddr.FileMaps, "/proc/%d/maps", stockthepid.pid);
    sprintf(get_modulebaseaddr.RealModule, "/%s", module);

    get_modulebaseaddr.GetModuleBaseAddrFile = fopen(get_modulebaseaddr.FileMaps, "r");

    if (get_modulebaseaddr.GetModuleBaseAddrFile != NULL) {
        while(fgets(get_modulebaseaddr.Line, MAXSIZE, get_modulebaseaddr.GetModuleBaseAddrFile)) {
            if(strstr(get_modulebaseaddr.Line, get_modulebaseaddr.RealModule)) {
                strncpy(get_modulebaseaddr.GetFirstLine, get_modulebaseaddr.Line, ADDROFFSET);
                get_modulebaseaddr.ConvertModule = strtoul(get_modulebaseaddr.GetFirstLine, NULL, 16);
                break;
            }
        }
    }
    fclose(get_modulebaseaddr.GetModuleBaseAddrFile);
    return get_modulebaseaddr.ConvertModule;
}


unsigned long long int GetRegs(unsigned int pid, struct user_regs_struct *X) {
    struct user_regs_struct regs;

    int ret;

    ret = ptrace(PTRACE_ATTACH, pid, NULL, NULL);

    if (ret == -1) {
        perror("Error we can't attach the process ! \n");
        return -1;
    }

    wait(NULL);

    ret = ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    if (ret == -1) {
        perror("Error we can't get regs of the process ! \n");
        return -1;
    }

    memcpy(X, &regs, sizeof(regs));

    ret = ptrace(PTRACE_DETACH, pid, NULL, NULL);
    if (ret == -1) {
        perror("Error we can't detach the process ! \n");
        return -1;
    }

    return 0;
}
