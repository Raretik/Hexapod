Vector2 pointOnCurve(Vector2* iniPoints, float t, int numPoints) {
  Vector2 pos;
  for (int i = 0; i < numPoints; i++) {
    float b = binomialCoefficient(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
    pos.x += b * iniPoints[i].x;
    pos.y += b * iniPoints[i].y;
    Serial.print("b=");
    Serial.println(b);
    Serial.print("x");
    Serial.println(pos.x);
    Serial.print("y");
    Serial.println(pos.y);
  }
  return pos;
}
Vector3 pointOnCurve(Vector3* iniPoints, float t, int numPoints) {
  Vector3 pos;
  for (int i = 0; i < numPoints; i++) {
    float b = binomialCoefficient(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
    pos.x += b * iniPoints[i].x;
    pos.y += b * iniPoints[i].y;
    pos.z += b * iniPoints[i].z;
    /*Serial.print("b=");
    Serial.println(b);
    Serial.print("x");
    Serial.println(pos.x);
    Serial.print("y");
    Serial.println(pos.y);
    Serial.print("z=");
    Serial.println(pos.z);*/
  }
  //Serial.println("b");Serial.println("b2");Serial.println("b3");
  return pos;
}
int binomialCoefficient(int n, int k) {
  int result = 1;
  // (n!) / (k! * (n - k)!)
  for (int i = 1; i <= k; i++) {
    result *= (n - (k - i));
    result /= i;
  }
  /*Serial.print("binomialCoe=");
  Serial.println(result);*/
  return result;
}