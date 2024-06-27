find . -name "*.c" -exec gcc -c {} -o {}.o \;
gcc -o dspapp.exe $(find . -name "*.o")
find . -name "*.o" -exec rm {} \;