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
void walk(Vector3 move) {
  int zMax = 0;
  int zMin = -90;
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
currentx 

Current points+Vector(move)
*/
      float x2 = 0;
      float y2 = 0;
      x2 = (currentPoints[1].x + move.x) / 2;
      y2 = (currentPoints[1].y + move.y) / 2;
      Vector3 movePoints=currentPoints[1]+move;
      Vector3 points[3]{ currentPoints[1], Vector3(x2, y2, zMax), movePoints};
      float t = 0;
      for (int i = 1; i < 6; i++) {
        moveLeg(1, pointOnCurve(points, t, 3));
        t += 0.2;
      }
      stepPhase = 1;

      Vector3 points2[2]{ movePoints, Vector3(-movePoints.x, movePoints.y, movePoints.z) };
      t = 0;
      for (int i = 1; i < 6; i++) {
        moveLeg(1, pointOnCurve(points2, t, 2));
        t += 0.2;
      }
      stepPhase = 0;

      break;
    case Crab:
      break;
  }
}