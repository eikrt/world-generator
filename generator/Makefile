OBJS = generator.c generator.h ../file/file.c ../file/file.h ../world/tile.h ../world/entity.h

CC = gcc

COMPILER_FLAGS = -w

LINKER_FLAGS = -lm

OBJ_NAME = application

all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
