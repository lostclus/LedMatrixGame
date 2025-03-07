#include <NonBlockingRtttl.h>

#include "Speaker.h"

Speaker::Speaker(int pin) : pin(pin) {
}

void Speaker::sound1() {
  rtttl::begin(pin, ":d=16,o=5,b=600:a,b,c,d,e,f,g");
}

void Speaker::sound2() {
  rtttl::begin(pin, ":d=16,o=5,b=600:a");
}

void Speaker::handle() {
  rtttl::play();
}

void Speaker::stop() {
  rtttl::stop();
}

// vim:sw=2:ai
