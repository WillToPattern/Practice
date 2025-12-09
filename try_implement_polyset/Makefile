NAME = polyset

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror 

SRCS = main.cpp \
       array_bag.cpp \
       tree_bag.cpp \
       searchable_array_bag.cpp \
       searchable_tree_bag.cpp \
       set.cpp

OBJS = $(SRCS:.cpp=.o)

HEADERS = bag.hpp \
          searchable_bag.hpp \
          array_bag.hpp \
          tree_bag.hpp \
          searchable_array_bag.hpp \
          searchable_tree_bag.hpp \
          set.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re