#include <SoftTimer.h>
#include <TonePlayer.h>

#define speakerPin  8

TonePlayer tonePlayer1(speakerPin, 100); // -- Tone manager

void setup(void)
{
  tonePlayer1.play("c1g1c1g1j2j2c1g1c1g1j2j2o1n1l1j1h2l2_2j1h1g1e1c2c2");
  //tonePlayer1.play("a1g1e1c1d1b1f1c1a1g1e1c1d1b1f1c1");
}

