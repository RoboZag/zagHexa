#include <Servo.h>
/*
  ////////////////////////////////////////////////// calibrations ////////////////////////////////////////////////////////////
  - dist1= 3.7 cm //coxa
  - dist2= 5.9 cm //Femur
  - dist3= 9.45 cm //tibia

joint limits:
  a1LF -> xº + 45                a1RF -> 138 - xº
  a2LF ->                        a2RF -> 185 - xº
  a3LF -> 210 - xº               a3RF -> xº - 37

  a1LB -> 144 - xº               a1RB -> xº + 37
  a2LB -> 198 - xº               a2RB -> xº - 8
  a3LB -> xº - 33                a3RB -> 222 - xº

  x & z -> max = 19
  x & z -> min = 7
  y -> max = 14
  y -> min = 2.5
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Servo s1RF;	Servo s2RF;	Servo s3RF;
Servo s1LF;	Servo s2LF;	Servo s3LF;
Servo s1RB;	Servo s2RB;	Servo s3RB;
Servo s1LB;	Servo s2LB;	Servo s3LB;
////////////////////////////////////////////////////////////
double RFx, RFy, RFz;
double LFx, LFy, LFz;
double RBx, RBy, RBz;
double LBx, LBy, LBz;
////////////////////////////////////////////////////////////
double dist1 = 3.7;

void setup() {

  s1RF.attach(2);	  s2RF.attach(3);		s3RF.attach(4);
  s1LF.attach(11);	s2LF.attach(12); 	s3LF.attach(13);
  s1RB.attach(5);	  s2RB.attach(6);		s3RB.attach(7);
  s1LB.attach(8); 	s2LB.attach(9);		s3LB.attach(10);
  ////////////////////////////////////////////////////////////
  RFx = 9;
  RFy = 6.5;
  RFz = 9;

  LFx = 9;
  LFy = 6.5;
  LFz = 9;

  RBx = 9;
  RBy = 6.5;
  RBz = 9;

  LBx = 9;
  LBy = 6.5;
  LBz = 9;
  movLegs(RFx, RFy, RFz, RBx, RBy, RBz, LFx, LFy, LFz, LBx, LBy, LBz, 10, 10);
}

////////////////////////////////////////////////////////////

void loop() {
  walk2(6, 3, 9, 11);
  delay(10);
}


//functions to move the robot
void sit(int div, int time) {
  movLegs(12, 1, 12, 12, 1, 12, 15, 0.5, 15, 15, 0.5, 15, div, time);
}

void wakeup(int div, int time) {
  movLegs(9, 6.5, 9, 9, 6.5, 9, 9, 6.5, 9, 9, 6.5, 9, div, time);
}

void walk2(double d, double u, int div, int time) {
  //movLegs(RFx,RFy,RFz, RBx,RBy,RBz, LFx,LFy,LFz,      LBx,LBy,LBz,div,time);
  movLegs(9, u, 6,      9, d + 0.75, 7,      9, d + 0.75, 7,      9, u, 8, div, time);        //2
  movLegs(9, d, 10,     9, d + 0.75, 7,      9, d + 0.75, 7,      9, d, 4, div, time);        //3
  movLegs(9, d, 7,      9, d + 0.75, 10,     9, d + 0.75, 4,      9, d, 7, (div * 1.3), (time * 1.3)); //4
  movLegs(9, d, 7,      9, u, 8,           9, u, 6,           9, d, 7, div, time);            //5
  movLegs(9, d, 7,      9, d + 0.75, 4,      9, d + 0.75, 10,     9, d, 7, div, time);        //6
  movLegs(9, d, 4,      9, d + 0.75, 7,      9, d + 0.75, 7,      9, d, 10, (div * 1.3), (time * 1.3)); //7
}

void walk(char dir, int div, int time) {
  moveAll(1.5, 0, 0, div, time);

  movLegRB(RBx, 2.5, RBz, div, time);
  movLegRB(11, 2.5, 3, div, time);
  movLegRB(RBx, 6.5 + 0.75, RBz, div, time);

  movLegRF(RFx, 1, RFz, div, time);
  movLegRF(11, 1, 11, div, time);
  movLegRF(RFx, 6.5, RFz, div, time);

  moveAll(-3, 0, 4, div, time);

  movLegLB(LBx, 2.5, LBz, div, time);
  movLegLB(11, 2.5, 3, div, time);
  movLegLB(LBx, 6.5, LBz, div, time);

  movLegLF(LFx, 2.5, LFz, div, time);
  movLegLF(11, 2.5, 11, div, time);
  movLegLF(LFx, 6.5 + 0.75, LFz, div, time);

  moveAll(1.5, 0, 4, div, time);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//functions to move the servos
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//update all legs position
void movLegs(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4, int div, int time) {
  double subx1 = (x1 - RFx) / div;
  double suby1 = (y1 - RFy) / div;
  double subz1 = (z1 - RFz) / div;
  double subx2 = (x2 - RBx) / div;
  double suby2 = (y2 - RBy) / div;
  double subz2 = (z2 - RBz) / div;
  double subx3 = (x3 - LFx) / div;
  double suby3 = (y3 - LFy) / div;
  double subz3 = (z3 - LFz) / div;
  double subx4 = (x4 - LBx) / div;
  double suby4 = (y4 - LBy) / div;
  double subz4 = (z4 - LBz) / div;

  for (int i = 0; i < div; i++) {
    RFx += subx1;
    RFy += suby1;
    RFz += subz1;
    RBx += subx2;
    RBy += suby2;
    RBz += subz2;
    LFx += subx3;
    LFy += suby3;
    LFz += subz3;
    LBx += subx4;
    LBy += suby4;
    LBz += subz4;
    s1RF.write(138 - ang1(RFx, RFy, RFz) );
    s2RF.write(185 - ang2(RFx, RFy, RFz) );

    double sca31 = ang3(RFx, RFy, RFz) - 37;
    if (sca31 > 4) {
      s3RF.write(sca31);
    } else {
      s3RF.write(5);
    }
    s1LF.write(ang1(LFx, LFy, LFz) + 45 );
    s2LF.write(ang2(LFx, LFy, LFz) );

    double sca33 = 210 - ang3(LFx, LFy, LFz);
    if (sca33 < 171) {
      s3LF.write(sca33);
    } else {
      s3LF.write(170);
    }
    s1RB.write(ang1(RBx, RBy, RBz) + 37 );
    s2RB.write(ang2(RBx, RBy, RBz) - 8 );

    double sca32 = 222 - ang3(RBx, RBy, RBz);
    if (sca32 < 180) {
      s3RB.write(sca32);
    } else {
      s3RB.write(180);
    }
    s1LB.write(138 - ang1(LBx, LBy, LBz) );
    s2LB.write(198 - ang2(LBx, LBy, LBz) );

    double sca34 = ang3(LBx, LBy, LBz) - 37;
    if (sca34 > 10) {
      s3LB.write(sca34);
    } else {
      s3LB.write(9);
    }
    delay(time);
  }
}

//updates for a single leg
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

void movLegLF(double x, double y, double z, int div, int time) {
  double subx = (x - LFx) / div;
  double suby = (y - LFy) / div;
  double subz = (z - LFz) / div;
  for (int i = 0; i < div; i++) {
    LFx += subx;
    LFy += suby;
    LFz += subz;
    s1LF.write(ang1(LFx, LFy, LFz) + 45 );
    s2LF.write(ang2(LFx, LFy, LFz) );

    double sca3 = 210 - ang3(LFx, LFy, LFz);
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

//move the body
void moveAll(double x, double y, double z, int div, int time) {
  double subx = x / div;
  double suby = y / div;
  double subz = z / div;

  for (int i = 0; i < div; i++) {
    RFx += subx;
    RFy += suby;
    RFz -= subz;

    LFx -= subx;
    LFy += suby;
    LFz -= subz;

    RBx += subx;
    RBy += suby;
    RBz += subz;

    LBx -= subx;
    LBy += suby;
    LBz += subz;

    s1RF.write(138 - ang1(RFx, RFy, RFz) );
    s2RF.write(180 - ang2(RFx, RFy, RFz) );
    s3RF.write(ang3(RFx, RFy, RFz) - 37);

    s1LF.write(ang1(LFx, LFy, LFz) + 45 );
    s2LF.write(ang2(LFx, LFy, LFz) );
    s3LF.write(201 - ang3(LFx, LFy, LFz));

    s1RB.write(ang1(RBx, RBy, RBz) + 37 );
    s2RB.write(ang2(RBx, RBy, RBz) - 3 );
    s3RB.write(222 - ang3(RBx, RBy, RBz) );

    s1LB.write(138 - ang1(LBx, LBy, LBz) );
    s2LB.write(180 - ang2(LBx, LBy, LBz) );
    s3LB.write(ang3(LBx, LBy, LBz) - 37);
    delay(time);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function to calculate the angles of the servos (IK)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
