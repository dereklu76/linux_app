TARGETS := copy seek_io

all : $(TARGETS)

% : %.c
	gcc $< -o $@

clean:
	rm $(TARGETS)

.PHONY : all clean



