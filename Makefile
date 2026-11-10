include qmk.mk

QMK_HOME ?= $(CURDIR)/qmk_firmware
JOBS ?= 4
export QMK_HOME

# Source archives contain the complete tree without Git metadata.
ifeq ($(wildcard $(QMK_HOME)/.git),)
export SKIP_GIT := yes
endif

.PHONY: all setup prepare build package
all: build

setup:
	@if [ ! -d "$(QMK_HOME)" ]; then \
		git clone --no-checkout --depth 1 https://github.com/qmk/qmk_firmware.git "$(QMK_HOME)"; \
	fi
	git -C "$(QMK_HOME)" fetch --depth 1 origin tag "$(QMK_VERSION)"
	@test "$$(git -C "$(QMK_HOME)" rev-parse "$(QMK_VERSION)^{commit}")" = "$(QMK_REVISION)" || \
		{ echo 'QMK tag does not match the pinned commit in qmk.mk.' >&2; exit 1; }
	git -C "$(QMK_HOME)" checkout --detach "$(QMK_REVISION)"
	git -C "$(QMK_HOME)" submodule update --init --recursive --depth 1

prepare:
	@test -f "$(QMK_HOME)/Makefile" || { echo 'Run make setup first.' >&2; exit 1; }
	@if [ -e "$(QMK_HOME)/.git" ]; then \
		test "$$(git -C "$(QMK_HOME)" rev-parse HEAD)" = "$(QMK_REVISION)" || \
		{ echo 'QMK revision differs from qmk.mk; run make setup.' >&2; exit 1; }; \
	fi
	# QMK discovers board definitions in its firmware tree, outside userspace.
	cp -R vendor/mechboards/keyboards/. "$(QMK_HOME)/keyboards/"
	mkdir -p "$(QMK_HOME)/keyboards/mechboards/crkbd/r2g/qp_font"
	cp vendor/pixelify-sans/generated/*.qff.[ch] "$(QMK_HOME)/keyboards/mechboards/crkbd/r2g/qp_font/"

build: prepare
	qmk userspace-compile -j $(JOBS) -p

package: build
	python3 scripts/package.py
