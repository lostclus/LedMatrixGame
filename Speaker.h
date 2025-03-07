#ifndef Speaker_h
#define Speaker_h

class Speaker {
  protected:
    int pin;

  public:
    Speaker(int pin);
    void handle();
    void stop();
    void sound1();
    void sound2();
};

#endif

// vim:sw=2:ai
