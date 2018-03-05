
void normalMode()
{
  if (data == 'f')
    _WZagHexa.forward (velocity, Wmode);
  if (data == 'b')
    _WZagHexa.backward(velocity, Wmode);
  if (data == 'r')
    _WZagHexa.right   (velocity, Wmode);
  if (data == 'l')
    _WZagHexa.left    (velocity, Wmode);
  data = ' ';
}

