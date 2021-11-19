# Makefile

SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(addprefix obj/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard inc/*.h)
EXEC_FILE = libmx.a

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: $(EXEC_FILE)

$(EXEC_FILE): build link

link:
	@printf "\r\33[2KArchiving $(EXEC_FILE)\t\t"
	@ar -rc $(EXEC_FILE) obj/*.o
	@printf "\033[32;1marchived\033[0m\n"

	@printf "\r\33[2KIndexing $(EXEC_FILE)\t\t"
	@ranlib $(EXEC_FILE)
	@printf "\033[32;1mindexed\033[0m\n"

build: $(OBJ_FILES)

$(OBJ_FILES): obj

obj:
	@mkdir -p $@

obj/%.o: src/%.c $(INC_FILES)
	@printf "\r\33[2KCompiling $(<:src/%.c=%).o\t\t"
	@clang $(CFLAGS) -c $< -o $@ -I inc
	@printf "\033[32;1mcompiled\033[0m\n"

clean:
	@printf "Deleting obj/\t\t"
	@rm -rf obj $@
	@rm -rf $(OBJ_FILES) $@
	@printf "\033[31;1mdeleted\033[0m\n"

uninstall: clean
	@printf "Deleting $(EXEC_FILE)\t\t"
	@rm -rf minilibmx.a
	@printf "\033[31;1mdeleted\033[0m\n"

reinstall: uninstall all

.PHONY: all build uninstall clean reinstall