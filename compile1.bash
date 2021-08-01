mkdir lib
cd src
gcc -c -o libsnake.o MemoryManagement.c
ar rcs libsnake.a libsnake.o
rm libsnake.o
cp libsnake.a MemoryManagement.h ../lib/
rm libsnake.a
