#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

include dpf/Makefile.base.mk

all: plugins
# --------------------------------------------------------------

plugins:
	$(MAKE) all -C plugins/MidiThroughExamplePlugin

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C plugins/MidiThroughExamplePlugin
	rm -rf bin build

# --------------------------------------------------------------

.PHONY: plugins
