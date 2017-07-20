#include <DHParam.h>

#include <MatrixMath.h>

float AB[4][4];
float BC[4][4];
float CD[4][4];
float temp1[4][4];
float AD[4][4];
float toolTip[4];
float origin[4] = {0, 0, 0, 1};
float theta1 = 0;
float theta2 = 0;
DHParam j0 = DHParam(0, 0, 0, 0); //our base frame
DHParam j1 = DHParam(theta1, 0, 0, 0);// the joint directly connecting to the base
DHParam j2 = DHParam(theta2, 52, 0, 0);//the next joint, distanced the length of link 1 away from the last (L1 in our case is 52mm)
DHParam j3 = DHParam(0, 30, 0, 0);//the tool tip, distanced the length of link 2 away from the last joint (L2 in our case is 30mm)

void setup() {
  Serial.begin(9600);
  establishContact();
}

void loop() {
  if (Serial.available() > 0) {
    readSerial();
    j1.setTheta(theta1);
    j2.setTheta(theta2);
    j1.getTransformation(AB, j0);
    j2.getTransformation(BC, j1);
    j3.getTransformation(CD, j2);
    Matrix.Multiply((float*)AB, (float*)BC, 4, 4, 4, (float*)temp1);
    Matrix.Multiply((float*)temp1, (float*)CD, 4, 4, 4, (float*)AD);
    Matrix.Multiply((float*)AD, (float*)origin, 4, 4, 1, (float*)toolTip);
    printMatrices();
  }
}

//wait for a serial command
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("hello");
    delay(300);
  }
}

//reads in two joint angles separated by a comma
void readSerial() {
  char bytes[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Serial.readBytes(bytes, 15);
  String combine = "";
  combine.concat(bytes[0]);
  combine.concat(bytes[1]);
  combine.concat(bytes[2]);
  combine.concat(bytes[3]);
  combine.concat(bytes[4]);
  combine.concat(bytes[5]);
  combine.concat(bytes[6]);
  combine.concat(bytes[7]);
  combine.concat(bytes[8]);
  combine.concat(bytes[9]);
  combine.concat(bytes[10]);
  combine.concat(bytes[11]);
  combine.concat(bytes[12]);
  combine.concat(bytes[13]);
  combine.concat(bytes[14]);
  theta1 = radians(combine.substring(0, combine.indexOf(",")).toInt());
  theta2 = radians(combine.substring(combine.indexOf(",") + 1).toInt());
}

//print out the transformations and the resulting coordinate point - mostly for debugging
void printMatrices() {
  Matrix.Print((float*)AB, 4, 4, "Base frame to J1:");
  Matrix.Print((float*)BC, 4, 4, "J1 to J2:");
  Matrix.Print((float*)CD, 4, 4, "J2 to tool tip:");
  Matrix.Print((float*)AD, 4, 4, "Base frame to tool tip:");
  Matrix.Print((float*)toolTip, 4, 1, "Tool Tip");
}
