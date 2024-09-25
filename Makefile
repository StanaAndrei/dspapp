COMP = gcc
CFLAGS = -Wall
LEFLAGS = -lm
SRCS := $(shell find . -name "*.c")
OBJS := $(SRCS:.c=.o)
TARGET = dspapp.exe

all: check_sox $(TARGET)

check_sox:
	@which sox > /dev/null 2>&1 || { \
		echo "SoX is not installed. Attempting to install..."; \
		sudo apt-get update && sudo apt-get install -y sox; \
	}

$(TARGET): $(OBJS)
	$(COMP) $(CFLAGS) -o $@ $^ $(LEFLAGS)
	@echo "Removing object files..."
	@find . -name "*.o" -type f -delete

%.o: %.c
	$(COMP) $(CFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(TARGET)

.PHONY: all clean