OBJS = tokenizer.o history.o
OBJS_MAIN = $(OBJS) uimain.o
OBJS_TEST = $(OBJS) tester.o

CFLAGS = -g -O3

tokenizer.h: tokenizer.o uimain.o
history.h: history.o uimain.o

tokenizer: $(OBJS_MAIN)
	cc -o tokenizer $(CFLAGS) $(OBJS_MAIN)

all: tokenizer

clean:
	rm -f *.o *.c~ *.h~ *~ *.c# *.h# src

run: tokenizer
	./tokenizer


