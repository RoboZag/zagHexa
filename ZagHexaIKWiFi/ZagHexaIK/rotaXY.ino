void rotaXY()
{
  switch (data)
  {
    case 'f':
      RotX+=2;
      if ( RotX >= 20)
        RotX = 20;
      break;
    case 'b':
      RotX-=2;
      if ( RotX <= -20)
        RotX = -20;
      break;
    case 'r':
      RotY+=2;
      if ( RotY >= 20)
        RotY = 20;
      break;
    case 'l':
      RotY-=2;
      if ( RotY <= -20)
        RotY = -20;
      break;
    default:
      data = ' ';
      break;
  }
  _WZagHexa.trans_rotat(velocity, 0, 0, 0, RotX, RotY, 0);
  data = ' ';
}
