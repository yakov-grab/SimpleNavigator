NAME 	=	navigator

SRCS 	=	main.cpp graph/s21_graph.cpp graph_algorithms/s21_graph_algorithms.cpp\
			console/console.cpp graph_algorithms/s21_aco_tsp.cpp
HEDER	=	graph/s21_graph.h  graph_algorithms/s21_graph_algorithms.h queue/Queue.hpp\
			stack/Stack.hpp console/console.h graph_algorithms/s21_aco_tsp.h
OBJ		=	$(SRCS::.cpp=.o)
GENERATOR = graph_generator.cpp

CC		=	g++

FLAGS	=	-Wall -Wextra -Werror -std=c++17 -g
TEST_FLAGS= -lgtest -lgtest_main -lpthread

RM		= rm -rf

.PHONY:		all	clean	fclean	re

%.o: %.cpp $(HEDER)
	$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME) :	$(OBJ) $(HEDER) $(MAKEFILE)
			${CC} ${FLAGS} ${OBJ} -I. -o ${NAME}

s21_graph.a:
	$(CC) -std=c++17 -c graph/s21_graph.cpp
	ar rcs s21_graph.a *.o
	ranlib $@
	cp $@ lib$@

s21_graph_algorithms.a:
	$(CC) -std=c++17 -c graph_algorithms/s21_graph_algorithms.cpp
	ar rcs s21_graph_algorithms.a *.o
	ranlib $@
	cp $@ lib$@

style:
	clang-format -n -verbose -style=Google $(SRCS) $(HEDER)

clean:
			@$(RM) *.o
			@$(RM) ./tests/test*

fclean:		clean
			@$(RM) *.o *.a test.out $(NAME) generator

test: clean s21_graph.a
	$(CC) $(FLAGS) tests.cpp s21_graph.a -lstdc++ $(TEST_FLAGS) -o test.out
	./test.out

leaks: clean test
	leaks --atExit -- ./test.out

re:			fclean all