void transXY()
{
  switch (data)
  {
    case 'f':
      PosY-=4;
      if ( PosY <= -80)
        PosY = -80;
      break;
    case 'b':
      PosY+=4;
      if ( PosY >= 80)
        PosY = 80;
      break;
    case 'r':
    PosX-=4;
      if ( PosX <= -80)
        PosX = -80;
      break;
    case 'l':
      PosX+=4;
      if ( PosX >= 80)
        PosX = 80;
      break;
    default:
      data = ' ';
      break;
  }
  _WZagHexa.trans_rotat(velocity, PosX, PosY, 0, 0, 0, 0);
  data = ' ';
}

