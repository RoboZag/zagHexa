#include <WalkingPattern.h>

int i;
int Wmode;
int velocity = 40;
walkingPattern  HexaPod;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // Change the walking mode {Tripod=0, Wave-1, Ripple=2}
  for (Wmode = 0; i < 3; i++)
  {
    // Move Forward 10 Steps
    for (i = 0; i < 10 ; i++)
      HexaPod.forward (velocity, Wmode);
    // Move Backward 10 Steps
    for (i = 0; i < 10 ; i++)
      HexaPod.backward(velocity, Wmode);
    // Move Right 10 Steps
    for (i = 0; i < 10 ; i++)
      HexaPod.right   (velocity, Wmode);
    // Move Left 10 Steps
    for (i = 0; i < 10 ; i++)
      HexaPod.left    (velocity, Wmode);
  }
}
