SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:%.c=%.o)
MAIN = test.o

OUT=Overflow

FLAGS+=-Wall -Wextra -Werror=pedantic -g -fsanitize=address
CC=gcc

all: $(OBJS) $(MAIN)
	$(CC) $(OBJS) $(MAIN) -o $(OUT) $(FLAGS) $(LDFLAGD)

clean: $(OBJS) $(MAIN)
	rm $(OBJS) $(MAIN)