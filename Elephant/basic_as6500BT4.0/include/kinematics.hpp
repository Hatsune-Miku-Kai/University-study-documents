#ifndef ATOMMAIN_KINEMATICS_H
#define ATOMMAIN_KINEMATICS_H
#include <array>
#include "math.h"
#include<Arduino.h>
#include "config.h"

#define PI 3.1415926535897932384626433832795

class RobotKinematics
{
public:
    Coords ForwardKinematics(Angles joints);
    Coords SingleToBaseCoords(Coords Posture, int dire);
    void Matrix_multiplication_4x4_4x4(double a[][4],double b[][4],double c[][4]);
    void cvDirServoToJoint(Angles &Update_joints);
    Angles cvRadToDegree(Angles Update_joints);
    void CvtCoordsToRadCoords(Coords *coords);
    void CvtRadCoordsToCoords(Coords *coords);

    void ArrayPrint(Encoders arr, String name = {""});
    void ArrayPrintAngles(Angles arr, String name = {""});
    void ArrayPrintCoords(Coords arr, String name = {""});
protected:
    inline void CvtRotationMatrixToEulerAngle(float pdtRotationMatrix[3][3], float* pdtEulerAngle)
    {
        float fCosRoll, fSinRoll;
        *(pdtEulerAngle + 2) = atan2(pdtRotationMatrix[1][0], pdtRotationMatrix[0][0]);

        fCosRoll = cos(*(pdtEulerAngle + 2));
        fSinRoll = sin(*(pdtEulerAngle + 2));

        *(pdtEulerAngle + 1) = atan2(-pdtRotationMatrix[2][0], (fCosRoll * pdtRotationMatrix[0][0]) + (fSinRoll * pdtRotationMatrix[1][0]));
        *pdtEulerAngle = atan2((fSinRoll * pdtRotationMatrix[0][2]) - (fCosRoll * pdtRotationMatrix[1][2]), (-fSinRoll * pdtRotationMatrix[0][1]) + (fCosRoll * pdtRotationMatrix[1][1]));
    }
    inline void CvtEulerAngleToRotationMatrix(float* ptrEulerAngle, double ptrRotationMatrix[3][3])
    {
        float ptrSinAngle[3] = { 0.0 };
        float ptrCosAngle[3] = { 0.0 };

        ptrSinAngle[0] = sin(ptrEulerAngle[0]);
        ptrSinAngle[1] = sin(ptrEulerAngle[1]);
        ptrSinAngle[2] = sin(ptrEulerAngle[2]);
        ptrCosAngle[0] = cos(ptrEulerAngle[0]);
        ptrCosAngle[1] = cos(ptrEulerAngle[1]);
        ptrCosAngle[2] = cos(ptrEulerAngle[2]);


        ptrRotationMatrix[0][0] = ptrCosAngle[2] * ptrCosAngle[1];
        ptrRotationMatrix[0][1] = ptrCosAngle[2] * ptrSinAngle[1] * ptrSinAngle[0] - ptrSinAngle[2] * ptrCosAngle[0];
        ptrRotationMatrix[0][2] = ptrCosAngle[2] * ptrSinAngle[1] * ptrCosAngle[0] + ptrSinAngle[2] * ptrSinAngle[0];
        ptrRotationMatrix[1][0] = ptrSinAngle[2] * ptrCosAngle[1];
        ptrRotationMatrix[1][1] = ptrSinAngle[2] * ptrSinAngle[1] * ptrSinAngle[0] + ptrCosAngle[2] * ptrCosAngle[0];
        ptrRotationMatrix[1][2] = ptrSinAngle[2] * ptrSinAngle[1] * ptrCosAngle[0] - ptrCosAngle[2] * ptrSinAngle[0];
        ptrRotationMatrix[2][0] = -ptrSinAngle[1];
        ptrRotationMatrix[2][1] = ptrCosAngle[1] * ptrSinAngle[0];
        ptrRotationMatrix[2][2] = ptrCosAngle[1] * ptrCosAngle[0];
    }
private:
    const float a3 = 19.99;
    const float a4 = 47.331;
    const float a6 = 84;
    // const float a7 = 172.705;
    const float a7 = 0;
    const float d1 = 92.2;
    const float d3 = 214.641;
    const float d5 = 216.604;
    // const float df = 152.891;
    const float df = 82.891;

    double af = PI/4;
    double L1 = 200;
    double L2 = 0;

    double TBR[4][4] = {cos(af), 0, sin(af), 0, 
                        sin(af), 0, -cos(af), -L1,
                        0, 1, 0, L2,
                        0, 0, 0, 1};
    double TBL[4][4] = { cos(af), 0, sin(af), 0,
                     -sin(af), 0, cos(af), L1,
                     0, -1, 0, L2,
                     0, 0, 0, 1 };
    
    float dir[JOINTS] = {1.0, -1.0, 1.0, -1.0, 1.0, 1.0, 1.0};


};

#endif