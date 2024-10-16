
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
      float x=currentPoints[1];
      float x1=x+xMove;
      float x2=x-xMove;
      //
      // x->x1
      // | x1->x2 |
      // | x2->x1 |* repeat until stoped
      // x2|x1->xStand AKA 0
      // b=(4*hMax)/(3*(x+x1)-2*(x*x1))
      // a=-1*(b/(x+x1))
      // c=a*x*x1
      break;
    case Crab:
      break;
  }
}