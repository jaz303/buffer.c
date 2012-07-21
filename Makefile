CC			= gcc
CFLAGS		= -Iinclude

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJ			=	src/buffer.o

obj: $(OBJ)

clean:
	find . -name '*.o' -delete