
void bodyMovement(Vector2 change) {
  float xChange = change.x;
  float yChange = change.y;
  for (int legNumber = 0; legNumber < 6; legNumber++) {
    // Retrieve the current position of the leg
    float x = currentPoints[legNumber].x;
    float y = currentPoints[legNumber].y;
    float z = currentPoints[legNumber].z;

    if (1 != vectorApplied) {
      switch (legNumber) {
        case 0:
          y = y + (yChange * cos(3.14 / 3) + xChange * sin(3.14 / 3));
          x = x + (-yChange * sin(3.14 / 3) + xChange * cos(3.14 / 3));
          break;
        case 1:
          y += yChange;
          x += xChange;
          break;
        case 2:
          y = y + (yChange * cos(-3.14 / 3) + xChange * sin(-3.14 / 3));
          x = x + (-yChange * sin(-3.14 / 3) + xChange * cos(-3.14 / 3));
          break;
        case 3:
          y = y - (yChange * cos(3.14 / 3) + xChange * sin(3.14 / 3));
          x = x - (-yChange * sin(3.14 / 3) + xChange * cos(3.14 / 3));
          break;
        case 4:
          y -= yChange;
          x -= xChange;
          break;
        case 5:
          y = y - (yChange * cos(-3.14 / 3) + xChange * sin(-3.14 / 3));
          x = x - (-yChange * sin(-3.14 / 3) + xChange * cos(-3.14 / 3));
          break;
      }
    }
    moveLeg(legNumber, Vector3(x, y, z));
  }
  vectorApplied = 1;
}