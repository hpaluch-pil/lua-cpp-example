VALGRIND_FLAGS := --leak-check=full

# cflags and libs via pkg-config - separated by comma!
PKGS := lua5.3
PKG_CONFIG_CPPFLAGS := $(shell pkg-config --cflags $(PKGS))
PKG_CONFIG_LDLIBS   := $(shell pkg-config --libs $(PKGS)) 



CPPFLAGS := -Wall -g $(PKG_CONFIG_CPPFLAGS)
LDFLAGS  := -g
LDLIBS   := $(PKG_CONFIG_LDLIBS)

APP := lua_ex

all : $(APP)

$(APP) : $(APP).o

$(APP).o : $(APP).cpp

.PHONY: run
run: $(APP)
	./$(APP)

.PHONY: valgrind
valgrind: $(APP)
	valgrind $(VALGRIND_FLAGS) ./$(APP)


.PHONY: clean
clean:
	rm -f $(APP) $(APP).o

