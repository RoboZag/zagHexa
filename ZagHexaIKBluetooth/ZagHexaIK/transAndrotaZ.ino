void transAndrotaZ()
{
  switch (data)
  {
    case 'f':
      PosZ-=2;
      if ( PosZ <= - 30)
        PosZ = - 30;
      break;
      
    case 'b':
      PosZ+=3;
      if ( PosZ >= 55)
        PosZ = 55;
      break;

    case 'r':
      RotZ+=2;
      if ( RotZ >= 15)
        RotZ = 15;
      break;

    case 'l':
      RotZ-=2;
      if ( RotZ <= -15)
        RotZ = -15;
      break;

    default:
      data = ' ';
      break;
  }
  _WZagHexa.trans_rotat(velocity, 0, 0, PosZ, 0, 0, RotZ);
  data = ' ';
}

