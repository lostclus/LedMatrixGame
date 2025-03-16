BOARD=arduino:avr:nano:cpu=atmega328old
PORT=/dev/ttyUSB0

EXTRA_FLAGS=

compile:
	arduino-cli compile \
		-b "$(BOARD)" \
		--build-property build.extra_flags="$(EXTRA_FLAGS)" \
		.

upload:
	arduino-cli upload \
		-v \
		-b "$(BOARD)" \
		-p $(PORT) \
		.

install: compile upload

monitor:
	minicom -D $(PORT)

compile-stl:
	$(MAKE) -C 3DPrint compile
