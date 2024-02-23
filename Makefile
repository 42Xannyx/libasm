TARGET = libasm

OBJD = objs/
SRCD = src/
SRCS_C = main.c
SRCS_S = functions/ft_strlen.s functions/ft_write.s
OBJS = $(SRCS_C:%.c=$(OBJD)%.o) $(SRCS_S:%.s=$(OBJD)%.o)

CFLAGS = -Wall -fPIC
ASFLAGS =
GCC = gcc
AS = as
RM = rm -rf

all: $(OBJD) $(TARGET)

$(OBJD):
	@mkdir -p $(OBJD) $(OBJD)functions

$(OBJD)%.o: $(SRCD)%.c
	$(GCC) $(CFLAGS) -c $< -o $@

$(OBJD)%.o: $(SRCD)%.s
	$(AS) $(ASFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) -no-pie $^ -o $@

clean:
	$(RM) $(OBJD) $(TARGET)

.PHONY: all clean
