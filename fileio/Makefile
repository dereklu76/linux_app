TARGETS := copy seek_io bad_exclusive_open good_exclusive_open

all : $(TARGETS)

% : %.c
	gcc $< -o $@

clean:
	rm $(TARGETS)

.PHONY : all clean



