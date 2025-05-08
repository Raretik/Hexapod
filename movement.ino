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
void walk(Vector2 move) {
  int zMax = 0;
  int zMin = -90;
  float t = 0;
  switch (currentGait) {
    case Tripod:
      /*
Step Phase 0:
legs 0,2,4 move step forward with a curve 
legs 1,3,5 slide back
Step Phase 1:
legs 0,2,4 move step forward with a curve 
legs 1,3,5 slide back

moving in a curve 
Point1:current Point
Point2:half of the move but at highest point
Point3:Current point+Vector(move)
*/

      Vector3 Point1 = currentPoints[1];
      Vector3 Point2 = Vector3(currentPoints[1].x+((1/2)*(move.x)),currentPoints[1].y+((1/2)*(move.y)),zMax);
      Vector3 Point3 = Vector3(currentPoints[1].x+move.x,currentPoints[1].y+move.y,zMin);
      Vector3 movePoints[3]{Point1,Point2,Point3};
      for (int i = 1; i < 6; i++) {
        moveLeg(1, pointOnCurve(movePoints, t, 3));
        t += 0.2;
      }
      stepPhase = 1;
      t = 0;
      for (int i = 1; i < 6; i++) {
        moveLeg(1, pointOnCurve(movePoints, t, 2));
        t += 0.2;
      }
      stepPhase = 0;

      break;
    case Crab:
      break;
  }
}