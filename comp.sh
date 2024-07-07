find . -name "*.c" -exec gcc -Wall -c {} -o {}.o \;
gcc -o dspapp.exe $(find . -name "*.o") -lm #lm-for math.h
find . -name "*.o" -exec rm {} \;