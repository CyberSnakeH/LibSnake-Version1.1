# LibSnake-Version 1.1

# What does this library do?

-  Read Process Memory
-  Write Process Memory
-  Get the pid of a process 
-  Get the module of a process
-  Get the registers of a process

# How to use it ?

1) git clone https://github.com/CyberSnakeH/LibSnake-Version1.1.git
2) cd LibSnake-Version1.1
3) Compile it : bash compile1.bash
4) Go to the lib folder
5) You can now use the libsnake.a library. To do so, include in your folder the library plus the file MemoryManagement.h

# Exemple of use 1 :

## main.c file :
```c
#include <stdio.h>
#include "MemoryManagement.h"

#define Addr 0x7ffdbe0a44c4

int main(void) {
	printf("Hello world \n");
	struct user_regs_struct X;
	
	// Get Pid
	unsigned int Pid = GetThePid("FakeGame");
	// Get Module
	unsigned long Module = GetModuleBase(Pid, "FakeGame.so");
	
	printf("Pid is %d and Module is %lx\n", Pid, Module);
	unsigned long ptr1;
	
	// Read Process Memory
	ReadProcessMemory(Addr, &ptr1, Pid);
	printf("Value of addresse is %d\n", ptr1);
	//Write Process Memory
	WriteProcessMemory(Addr, 200, Pid);
	
	// Get registers 
	GetRegs(Pid, &X);
	// Print rax register for exemple
	printf("Rax register : 0x%lx\n", X.rax);
	
	return 0;
}

```

## Compile the code :
gcc main.c -L. ./libsnake.a -o your_file_name

# Example of use 2 :

https://youtu.be/GFM4YABdU_g

# Contact 

My Discord : https://discord.gg/BA9FN25

# What changes
[Version 1.0]

In version 1.0 of the library you could just do :
-  Read Process Memory
-  Write Process Memory
-  Get the pid of a process 
-  Get the module of a process

[which has been added]

Get the registers of a process
