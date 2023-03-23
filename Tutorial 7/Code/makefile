LIBS = 
SOURCES = task3.c task4.c sigtrap.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = process task3 task4 task5
.PHONY: clean help

.PHONY: debug
debug: CFLAGS += -O0 -g3
debug: $(EXE)

process : sigtrap.o
	gcc -Wall -Wextra -std=gnu99 $^ $(LIBS) -o $@ 
task3 : task3.o
	gcc -Wall -Wextra -std=gnu99 $^ $(LIBS) -o $@ 
task4 : task4.o
	gcc -Wall -Wextra -std=gnu99 $^ $(LIBS) -o $@ 
task5 : task5.o
	gcc -Wall -Wextra -std=gnu99 $^ $(LIBS) -o $@ 

%.o : %.c
	gcc -Wall -Wextra -std=gnu99 -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~