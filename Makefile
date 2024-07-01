CC=gcc
FLAGS=-Wall -Werror
OBJS=mtll.o main.o
TARGET=mtll

.PHONY: build tests run_tests clean

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

tests: build
	echo "Prepare my tests (if necessary)!"

run_tests: tests
	echo "Running my tests!"
	./run_tests.sh

clean:
	rm -f $(OBJS) $(TARGET)