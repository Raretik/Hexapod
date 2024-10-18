void bodyMovement(Vector2 change) {
  float xChange = change.x;
  float yChange = change.y;
  for (int legNumber = 0; legNumber < 6; legNumber++) {
    // Retrieve the current position of the leg
    float x = currentPoints[legNumber].x;
    float y = currentPoints[legNumber].y;
    float z = currentPoints[legNumber].z;

    switch (legNumber) {
      case 0:
        y = y - (yChange * cos(3.14 / 3) + xChange * sin(3.14 / 3));  //Rotating vector
        x = x - (-yChange * sin(3.14 / 3) + xChange * cos(3.14 / 3));
        break;
      case 1:
        y -= yChange;
        x -= xChange;
        break;
      case 2:
        y = y - (yChange * cos(-3.14 / 3) + xChange * sin(-3.14 / 3));  //Rotating vector
        x = x - (-yChange * sin(-3.14 / 3) + xChange * cos(-3.14 / 3));
        break;
      case 3:
        y = y + (yChange * cos(3.14 / 3) + xChange * sin(3.14 / 3));  //Rotating vector
        x = x + (-yChange * sin(3.14 / 3) + xChange * cos(3.14 / 3));
        break;
      case 4:
        y += yChange;
        x += xChange;
        break;
      case 5:
        y = y + (yChange * cos(-3.14 / 3) + xChange * sin(-3.14 / 3));  //Rotating vector
        x = x + (-yChange * sin(-3.14 / 3) + xChange * cos(-3.14 / 3));
        break;
    }
    moveLeg(legNumber, Vector3(x, y, z));
  }
}
void walk(Vector2 center) {
  switch (currentGait) {
    case Tripod:
      float xMove = center.x;
      float x = currentPoints[1].x;
      float x1 = x + xMove;
      float x2 = x - xMove;
      float stepLength = abs(x1) + abs(x);
      int hMax=50;
      float b=(4*hMax)/(3*(x+x1)-2*(x*x1));
      float a=-1*(b/(x+x1));
      float c=a*x*x1;
      //Serial.print("a");Serial.println(a);
      //Serial.print("b");Serial.println(b);
      //Serial.print("c");Serial.println(c);
      //Serial.print("x1");Serial.println(x1);
      //Serial.print("step");Serial.println(stepLength);
      int hMin=-90;
      for (int i = 1; i < 6; i++) {
        float curX = x + (stepLength / i);
        float curZ = a*pow(curX,2)+b*curX-c;
        //Serial.print("curX");Serial.println(curX);
        //Serial.print("curZ");Serial.println(curZ);
        moveLeg(1,Vector3(curX,currentPoints[1].y,hMin+curZ));
      }
      //
      // x->x1
      // | x1->x2 |
      // | x2->x1 |* repeat until stoped
      // x2|x1->xStand AKA 0
      // b=(4*hMax)/(3*(x+x1)-2*(x*x1))
      // a=-1*(b/(x+x1))
      // c=a*x*x1
      //5 0
      //4-1
      //3 2
      //
      break;
    case Crab:
      break;
  }
}