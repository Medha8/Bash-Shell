TARGETS = shell_main shell_prompt

.PHONY: clean

all: $(TARGETS)

%: %.c
	gcc $< -o $@

clean:
	rm -f $(TARGETS)
