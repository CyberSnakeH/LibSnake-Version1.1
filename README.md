# LibSnake-Version 1.0

# What does this library do?

-> Read Process Memory

-> Write Process Memory

-> Get the pid of a process 

-> Get the module of a process 

# How to use it ?

1) Compile it : bash compile1.bash
2) Go to the lib folder
3) You can now use the libsnake.a library. To do so, include in your folder the library plus the file MemoryManagement.h

# Exemple of use 1 :

## main.c file :
```
#include <stdio.h>
#include "MemoryManagement.h"

#define Addr 0x7ffdbe0a44c4

int main(void) {
	printf("Hello world \n");
	unsigned int Pid = GetThePid("FakeGame");
	unsigned long Module = GetModuleBase(Pid, "FakeGame.so");

	printf("Pid is %d and Module is %lx\n", Pid, Module);
	unsigned long ptr1;
	
	ReadProcessMemory(Addr, &ptr1, Pid);
	printf("Value of addresse is %d\n", ptr1);
	WriteProcessMemory(Addr, 200, Pid);
	return 0;
}

```

## Compile the code :
gcc main.c -L. ./libsnake.a -o your_file_name

# Example of use 2 :

https://youtu.be/GFM4YABdU_g

# Contact 

My Discord : https://discord.gg/BA9FN25
