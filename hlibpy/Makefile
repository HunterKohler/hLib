SHELL := /usr/bin/env bash

.PHONY: all deps test clean

all:
	@echo "No default target"
	@exit 1

clean:
	$(RM) -r $$(find . -type d -name .pytest_cache -or -name __pycache__)

deps: requirements.txt

test: deps
	pytest tests


