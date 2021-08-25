void setup() {
  size(1000, 600);
  colorMode(HSB, 255, 255, 255);
}

int prevY = 0;
void draw() {
  background(200);
  int count = 0;
  stroke(0);
  for (int i = 0; i < 255; i+=30) {
    line(0, i*2, width, i*2);
  }

  for (int i = 0; i < 150; i++) {
    int thisVal = count % 255;
    stroke(0);
    line((i-1) * 12+10, prevY*2, i * 12+10, thisVal*2);
    prevY = thisVal;
    noStroke();
    fill(thisVal, 255, 255);
    circle(i*12 + 10, thisVal * 2, 10);
    square(i*12 + 10, 550, 10);
    count += /*round(random(90,110));//*/mouseX/5;
  }
  fill(0);
  text(mouseX/5, 10, 580);
  //noLoop();
}
//151
//129
