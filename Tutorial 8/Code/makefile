LIBS = 
SOURCES = task1.c sigtrap-1.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = process task1
.PHONY: clean help

.PHONY: debug
debug: CFLAGS += -O0 -g3
debug: $(EXE)

process : sigtrap-1.o
	gcc -Wall -Wextra -std=gnu99 $^ $(LIBS) -o $@ 
task3 : task1.o
	gcc -Wall -Wextra -std=gnu99 $^ $(LIBS) -o $@ 

%.o : %.c
	gcc -Wall -Wextra -std=gnu99 -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~