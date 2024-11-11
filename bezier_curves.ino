Vector2 pointOnCurve(Vector2* iniPoints, float t, int numPoints){
  Vector2 pos;
  for(int i; i<=numPoints;i++){
      float b=binomialCoefficient(numPoints,i)*pow(1-t,numPoints-1)*pow(t,i);
      pos.x+=b*iniPoints[i].x;
      pos.y+=b*iniPoints[i].y;
  } 
  return pos;
}
Vector3 pointOnCurve(Vector3* iniPoints, float t, int numPoints){
  Vector3 pos;
  for(int i; i<=numPoints;i++){
      float b=binomialCoefficient(numPoints,i)*pow(1-t,numPoints-1)*pow(t,i);
      pos.x+=b*iniPoints[i].x;
      pos.y+=b*iniPoints[i].y;
      pos.z+=b*iniPoints[i].z;
  } 
  return pos;
}
float binomialCoefficient(int numPoints, int i){
//(n/i)=n!/(k!(n-k)!)
float b=(factorial(numPoints))/(factorial(i)*factorial((numPoints-i)));
return b;
}