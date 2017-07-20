/*
  DHParam.h - Library for implementing Denavit-Hartenberg Parameters.
  Created by Nathan Rukavina, July 17, 2017.
  Released into the public domain.
*/

#ifndef DHParam_h
#define DHParam_h

#include "Arduino.h"

class DHParam
{
	public:
		DHParam(float theta_, float a_, float d_, float alpha_);
		void getTransformation(float arr[4][4], DHParam from);
		void setTheta(float theta_);
		void setA(float a_);
		void setD(float d_);
		void setAlpha(float alpha_);
		float getTheta();
		float getA();
		float getD();
		float getAlpha();
	private:
		float theta;
		float a;
		float d;
		float alpha;
};


#endif

