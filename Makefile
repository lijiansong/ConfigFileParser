
# Makefile

CC := g++
# Optimized flags
CFLAGS := -Wall -g -O2 -I.
#Debug flags.
#CFLAGS := -Wall -g -I.
#LIBS := -lgflags -lglog
LIBS :=
LFLAGS :=

OBJ_UTIL = \
  util/util.o

OBJ_CONFIG = \
  config/tuple.yy.o \
  config/tuple.tab.o \
  config/config_map_builder.o \
  config/tuple_parser.o \
  config/config_loader.o \
  config/config_map.o \
  config/constant.o

MAIN_OBJ = \
  config/config_main.o

OBJ_LIB := \
  $(OBJ_UTIL) \
  $(OBJ_CONFIG)

ALL_OBJ := $(OBJ_LIB) $(MAIN_OBJ)

PROGRAMS = \
  config_parser

LIBRARY = \
  lib_cfg_parser.a

all: $(PROGRAMS) $(LIBRARY)

# include all dependency rules created by the compiler
# unless we are executing "make clean"
# don't complain for missing includes
DEPS = $(ALL_OBJ:.o=.d)
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

# rule to build dependency files
#  use fix_dep.sh to add correct directories to .d files.
%.d: %.cc
	g++ -MM -MG $(CFLAGS) $*.cc > $@
	./scripts/fix_dep.sh $@

%.d: %.c
	g++ -MM -MG $(CFLAGS) $*.c > $@
	./scripts/fix_dep.sh $@

# rule to build object files
%.o: %.cc
	$(CC) $(CFLAGS) -c $*.cc -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $@

# rules for flex/bison
%.yy.c: %.l
	flex -o $@ $*.l

%.tab.c %.tab.h: %.y
	bison -d $*.y -o $@

config_parser: config/config_main.o $(OBJ_LIB)
	$(CC) $(LFLAGS) -o $@ config/config_main.o $(OBJ_LIB) $(LIBS) -pthread

lib_cfg_parser.a: $(OBJ_LIB)
	ar -rs $@ $(OBJ_LIB)

clean:
	@rm -f *.out
	@rm -f *.o
	@rm -f *.a
	@rm -f $(ALL_OBJ)
	@rm -f $(DEPS)
	@rm -f config/*.tab.*
	@rm -f config/*.yy.c
