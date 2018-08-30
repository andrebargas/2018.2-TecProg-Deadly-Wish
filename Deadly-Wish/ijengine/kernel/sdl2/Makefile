NAME = kernel
VERSION = 0.1.0
EXTENSION = so
TARGET = $(NAME).$(EXTENSION).$(VERSION)

CC = g++
CFLAGS = -std=c++11 -W -Wall -Wextra -Wshadow -Wcast-align -Wcast-qual -Wctor-dtor-privacy\
		 -Wdisabled-optimization -Wformat=2 -Wlogical-op -Wmissing-declarations\
		 -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls\
		 -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef\
		 -Wzero-as-null-pointer-constant -Wuseless-cast -Wnon-virtual-dtor\
		 -fPIC
		 
INCLUDES = -I../../include `sdl2-config --cflags`
LIBS = -L../../lib  -lijengine `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer


SRC = ${wildcard *.cpp}
OBJ = ${notdir ${SRC:.cpp=.o}}

.PHONY: clean depend dist-clean 

all:
	$(MAKE) $(TARGET)

%.o: %.cpp
	@echo Building $@
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TARGET): $(OBJ)
	@echo Building $@
	@echo $(CC) -shared -rdynamic $(CFLAGS) $(INCLUDES) $(OBJ) -o $@
	@$(CC) -shared -rdynamic $(CFLAGS) $(INCLUDES) $(OBJ) -o $@ $(LIBS)
	@echo Done.

clean:
	@echo Cleaning...
	@find . -name '*.o' -exec rm -f {} \;
	@find . -name '*.d' -exec rm -f {} \;
	@rm -rf *~ *.o prog out.txt

dist-clean: clean
	@find . -name *.a -exec rm {} \;
	@rm -f test/test $(TARGET)
	@rm -rf *.tar.gz

-include $(OBJ:.o=.d)
