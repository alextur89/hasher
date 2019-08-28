CC := g++
CFLAGS := -Wall -g -O0

OBJS = main.o

all: hasher

hasher: $(OBJS)
	@$(CC) -o $@ $(CFLAGS) $(OBJS) -lcrypto

$(OBJS) : %.o: %.cpp
	@$(CC) -c $(CFLAGS) $< -o $@

.PHONY:
clean:
	@rm -f *.o hasher
	@echo clear
