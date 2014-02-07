SHELL  = bash
TARGET = tlbones.so
CC     = gcc
CCFL   = -Wall -I../include -fPIC -g
LDFL   = -Wall -shared -g

OBJS := bones.o arith.o
OBJS := $(addprefix obj/,$(OBJS))
SRCS := $(addprefix src/,$(patsubst %.o,%.c,$(OBJS)))
DEPS := $(addprefix dep/,$(patsubst %.o,%.d,$(OBJS)))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFL) $(OBJS) -o $(TARGET)

obj/%.o: src/%.c
	@ mkdir -p $(@D)
	@ mkdir -p $(subst obj,dep,$(@D))
	@ $(CC) -MM -MP -MT $@ -MF $(patsubst %.o,%.d,$(subst obj,dep,$@)) $<
	$(CC) $(CCFL) -c $< -o $@

clean:
	rm -rf obj
	rm -rf dep
	rm -f $(TARGET)

-include $(DEPS)
