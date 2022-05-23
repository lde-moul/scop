NAME = scop

CXX = clang++
# CXXFLAGS = -Wall -Wextra -Werror
CXXFLAGS = -Wall -Wextra

SRCDIR = src
OBJDIR = obj

SRC = Face.cpp\
      GLBuffer.cpp\
      GLError.cpp\
      GLProgram.cpp\
      GLShader.cpp\
      GLVAO.cpp\
      Main.cpp\
      Model.cpp\
      Util.cpp\
      Vertex.cpp\

INC = -Iglew

LIBS = -lglfw\
       -lGL\
       -lX11\
       -lpthread\
       -lXrandr\
       -lXi\
       -ldl\
       ./glew/libGLEW.so\

OBJ := $(SRC:%.cpp=$(OBJDIR)/%.o)
SRC := $(SRC:%=$(SRCDIR)/%)
DEP := $(OBJ:%.o=%.d)


all: $(NAME)

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

$(NAME): $(OBJDIR) $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(OBJ)

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	/bin/mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -std=c++11 -MMD -c $(INC) -o $@ $<

$(OBJDIR):
	/bin/mkdir $(OBJDIR)

.PHONY: all clean fclean re
