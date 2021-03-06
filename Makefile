NAME = scop

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror

SRCDIR = src
OBJDIR = obj

SRC = App.cpp\
      Main.cpp\
      Math/Matrix.cpp\
      Math/Quaternion.cpp\
      Math/Vector.cpp\
      Model/Face.cpp\
      Model/Model.cpp\
      Model/Vertex.cpp\
      OpenGL/GLBuffer.cpp\
      OpenGL/GLError.cpp\
      OpenGL/GLProgram.cpp\
      OpenGL/GLShader.cpp\
      OpenGL/GLTexture.cpp\
      OpenGL/GLVAO.cpp\
      TGA.cpp\
      Util.cpp\

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
