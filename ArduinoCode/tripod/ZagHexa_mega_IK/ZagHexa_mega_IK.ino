#include <Servo.h>
////////////////////////////////
Servo RFR; Servo RFL; Servo RFT;
Servo RMR; Servo RML; Servo RMT;
Servo RBR; Servo RBL; Servo RBT;
Servo LFR; Servo LFL; Servo LFT;
Servo LMR; Servo LML; Servo LMT;
Servo LBR; Servo LBL; Servo LBT;
////////////////////////////////
double RFx, RFy, RFz;
double RMx, RMy, RMz;
double RBx, RBy, RBz;
double LFx, LFy, LFz;
double LMx, LMy, LMz;
double LBx, LBy, LBz;
/////////////////////
void setup() {
RFR.attach(2);  RFL.attach(3);  RFT.attach(4);
RMR.attach(5);  RML.attach(6);  RMT.attach(7);
RBR.attach(8);  RBL.attach(9);  RBT.attach(10);
LFR.attach(11); LFL.attach(12); LFT.attach(13);
LMR.attach(14); LML.attach(15); LMT.attach(16);
LBR.attach(17); LBL.attach(18); LBT.attach(19);

}

void loop() {
}

//////////////////////////
//updates for a single leg
//////////////////////////

void movLegRF(double x, double y, double z, int div, int time) {
  double subx = (x - RFx) / div;
  double suby = (y - RFy) / div;
  double subz = (z - RFz) / div;
  for (int i = 0; i < div; i++) {
    RFx += subx;
    RFy += suby;
    RFz += subz;
    s1RF.write(138 - ang1(RFx, RFy, RFz) );
    s2RF.write(185 - ang2(RFx, RFy, RFz) );

    double sca3 = ang3(RFx, RFy, RFz) - 37;
    if (sca3 > 4) {
      s3RF.write(sca3);
    } else {
      s3RF.write(5);
    }
    delay(time);
  }
}

void movLegRM(double x, double y, double z, int div, int time) {
  double subx = (x - RMx) / div;
  double suby = (y - RMy) / div;
  double subz = (z - RMz) / div;
  for (int i = 0; i < div; i++) {
    RMx += subx;
    RMy += suby;
    RMz += subz;
    s1LF.write(ang1(RMx, RMy, RMz) + 45 );
    s2LF.write(ang2(RMx, RMy, RMz) );

    double sca3 = 210 - ang3(RMx, RMy, RMz);
    if (sca3 < 171) {
      s3LF.write(sca3);
    } else {
      s3LF.write(170);
    }
    delay(time);
  }
}

void movLegRB(double x, double y, double z, int div, int time) {
  double subx = (x - RBx) / div;
  double suby = (y - RBy) / div;
  double subz = (z - RBz) / div;
  for (int i = 0; i < div; i++) {
    RBx += subx;
    RBy += suby;
    RBz += subz;
    s1RB.write(ang1(RBx, RBy, RBz) + 37 );
    s2RB.write(ang2(RBx, RBy, RBz) - 8 );

    double sca3 = 222 - ang3(RBx, RBy, RBz);
    if (sca3 < 180) {
      s3RB.write(sca3);
    } else {
      s3RB.write(180);
    }
    delay(time);
  }
}

void movLegLF(double x, double y, double z, int div, int time) {
  double subx = (x - LFx) / div;
  double suby = (y - LFy) / div;
  double subz = (z - LFz) / div;
  for (int i = 0; i < div; i++) {
    LFx += subx;
    LFy += suby;
    LFz += subz;
    s1LB.write(138 - ang1(LFx, LFy, LFz) );
    s2LB.write(198 - ang2(LFx, LFy, LFz) );

    double sca3 = ang3(LFx, LFy, LFz) - 37;
    if (sca3 > 10) {
      s3LB.write(sca3);
    } else {
      s3LB.write(9);
    }
    delay(time);
  }
}

void movLegLM(double x, double y, double z, int div, int time) {
  double subx = (x - LMx) / div;
  double suby = (y - LMy) / div;
  double subz = (z - LMz) / div;
  for (int i = 0; i < div; i++) {
    LMx += subx;
    LMy += suby;
    LMz += subz;
    s1LB.write(138 - ang1(LMx, LMy, LMz) );
    s2LB.write(198 - ang2(LMx, LMy, LMz) );

    double sca3 = ang3(LMx, LMy, LMz) - 37;
    if (sca3 > 10) {
      s3LB.write(sca3);
    } else {
      s3LB.write(9);
    }
    delay(time);
  }
}

void movLegLB(double x, double y, double z, int div, int time) {
  double subx = (x - LBx) / div;
  double suby = (y - LBy) / div;
  double subz = (z - LBz) / div;
  for (int i = 0; i < div; i++) {
    LBx += subx;
    LBy += suby;
    LBz += subz;
    s1LB.write(138 - ang1(LBx, LBy, LBz) );
    s2LB.write(198 - ang2(LBx, LBy, LBz) );

    double sca3 = ang3(LBx, LBy, LBz) - 37;
    if (sca3 > 10) {
      s3LB.write(sca3);
    } else {
      s3LB.write(9);
    }
    delay(time);
  }
}

/////////////////////////////////////////////////////
//function to calculate the angles of the servos (IK)
/////////////////////////////////////////////////////
int ang1(double x, double y, double z) {
  double a1 = atan2(z, x); //gamma
  return (a1 * 57.3); // convert from rad to deg and return the result
}
int ang2(double x, double y, double z) {
  double hip = sqrt( pow(y, 2) + pow((x - dist1), 2)); //L
  double al1 = acos(y / hip);                        //alpha_1
  double al2 = acos( (54.5 - pow(hip, 2)) / (-11.8 * hip)); //alpha_2
  double a2 = al1 + al2; //alpha
  return (a2 * 57.3);
}
int ang3(double x, double y, double z) {
  double hip = sqrt( pow(y, 2) + pow((x - dist1), 2));
  double a3 = acos( (pow(hip, 2) - 124.1) / (-111.5)); //beta
  return (a3 * 57.3);
}
