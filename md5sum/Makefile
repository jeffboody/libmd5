TARGET   = md5sum
CLASSES  =
SOURCE   = $(TARGET).c $(CLASSES:%=%.c)
OBJECTS  = $(TARGET).o $(CLASSES:%=%.o)
HFILES   = $(CLASSES:%=%.h)
OPT      = -O2 -Wall
CFLAGS   = $(OPT) -I.
LDFLAGS  = -L/usr/lib -Llibmd5 -lmd5
CCC      = gcc

all: $(TARGET)

$(TARGET): $(OBJECTS) libmd5
	$(CCC) $(OPT) $(OBJECTS) -o $@ $(LDFLAGS)

.PHONY: libmd5

libmd5:
	$(MAKE) -C libmd5

clean:
	rm -f $(OBJECTS) *~ \#*\# $(TARGET)
	$(MAKE) -C libmd5 clean
	rm libmd5

$(OBJECTS): $(HFILES)
