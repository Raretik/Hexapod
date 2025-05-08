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
Point2:middle point betweem 1 and 3 at the highest possible position
Point3:standPos moved by move
Point4:reverse of 3
Point5:standPos but in the air
*/
      /*1->2->3->4->5->3...
curve1(1-2-3)
curve2(3-4)
curve3(4-5-3)
*/
      if (bool firstTime = 0; firstTime == 0) {
        firstTime = 1;
        float t = 0;
        Point1 = currentPoints[1];
        Point2 = Vector3(currentPoints[1].x + (0.5 * abs((standPos.x + move.x) - currentPoints[1].x)), currentPoints[1].y + (0.5 * abs((standPos.x + move.x) - currentPoints[1].x)), zMax);
        Point3 = Vector3(standPos.x + move.x, standPos.y + move.y, zMin);
        Point4 = Vector3(standPos.x - move.x, standPos.y - move.y, zMin);
        Point5 = Vector3(standPos.x, standPos.y, zMax);
        for (int i = 0; i < 6; i++) {
          Vector3 movePoints1[3]{ Point1, Point2, Point3 };
          Vector3 movePoints2[3]{ Point3, Point4 };
          Vector3 movePoints3[3]{ Point4, Point5, Point3 };
          curves[i][0] = pointOnCurve(movePoints1, t, 3);
          curves[i][1] = pointOnCurve(movePoints2, t, 2);
          curves[i][2] = pointOnCurve(movePoints3, t, 3);
          t += 0.2;
        }
      }
      switch (stepPhase) {
        case 0:
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
              moveLeg(1, curves[j][i]);
              delay(100);
            }
          }
          stepPhase = 1;
          break;
        case 1:
          for (int i = 1; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
              moveLeg(1, curves[j][i]);
              delay(100);
            }
          }
            break;
          }

          break;
        case Crab:
          break;
      }
  }