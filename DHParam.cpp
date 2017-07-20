/*
    DHParam.cpp - Library for implementing Denavit-Hartenberg Parameters.
    Created by Nathan Rukavina, July 17, 2017.
    Released into the public domain.
*/

#include "Arduino.h"
#include "DHParam.h"

float theta;
float a;
float d;
float alpha;

DHParam::DHParam(float theta_, float a_, float d_, float alpha_) {
  theta = theta_;
  a = a_;
  d = d_;
  alpha = alpha_;
}

void DHParam::setTheta(float theta_) {
  theta = theta_;
}

void DHParam::setA(float a_) {
  a = a_;
}

void DHParam::setD(float d_) {
  d = d_;
}

void DHParam::setAlpha(float alpha_) {
  alpha = alpha_;
}

float DHParam::getTheta() {
  return theta;
}

float DHParam::getA() {
  return a;
}

float DHParam::getD() {
  return d;
}

float DHParam::getAlpha() {
  return alpha;
}

void DHParam::getTransformation(float arr[4][4], DHParam from) {
  arr[0][0] = cos(theta);
  arr[0][1] = -sin(theta);
  arr[0][2] = 0;
  arr[0][3] = a;
  arr[1][0] = sin(theta) * cos(from.getAlpha());
  arr[1][1] = cos(theta) * cos(from.getAlpha());
  arr[1][2] = -sin(from.getAlpha());
  arr[1][3] = -sin(from.getAlpha()) * d;
  arr[2][0] = sin(theta) * sin(from.getAlpha());
  arr[2][1] = cos(theta) * sin(from.getAlpha());
  arr[2][2] = cos(from.getAlpha());
  arr[2][3] = cos(from.getAlpha()) * d;
  arr[3][0] = 0;
  arr[3][1] = 0;
  arr[3][2] = 0;
  arr[3][3] = 1;
}

