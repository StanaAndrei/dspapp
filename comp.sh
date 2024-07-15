find . -name "*.c" -exec gcc -Wall -c {} -o {}.o \;
gcc -o build/dspapp.exe $(find . -name "*.o") -lm #lm-for math.h
find . -name "*.o" -exec rm {} \;