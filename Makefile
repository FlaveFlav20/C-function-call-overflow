SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:%.c=%.o)
MAIN = test.o

OUT=Overflow

FLAGS+=-Wall -Wextra -Werror=pedantic -g #-fsanitize=address
LDFLAGS+=-g
CC=gcc

all: $(OBJS) $(MAIN)
	$(CC) $(OBJS) $(MAIN) -o $(OUT) $(FLAGS) $(LDFLAGD)

clean: $(OBJS) $(MAIN)
	rm $(OBJS) $(MAIN) t.c te.c 2> /dev/null
