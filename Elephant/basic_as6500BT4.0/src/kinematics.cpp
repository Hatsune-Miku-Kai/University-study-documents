#include"kinematics.hpp"

/*****************************************************************************************
*
*           正运动学(关节建模):
*                                 input:joints 当前关节角度
*                                 output:kinematic_pose末端位姿
*
*           该函数没做舵机方向的转换，使用的是关节方向建模，无offset
******************************************************************************************/
Coords RobotKinematics::ForwardKinematics(Angles joints)
{
    float nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;
    float q1 = joints.at(0);
    float q2 = joints.at(1);
    float q3 = joints.at(2);
    float q4 = joints.at(3);
    float q5 = joints.at(4);
    float q6 = joints.at(5);
    float q7 = joints.at(6);

    nx = cos(q7) * (sin(q6) * (sin(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) + cos(q1) * cos(q4) * sin(q2)) - cos(q6) * (cos(q5) * (cos(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) - cos(q1) * sin(q2) * sin(q4)) + sin(q5) * (cos(q3) * sin(q1) + cos(q1) * cos(q2) * sin(q3)))) - sin(q7) * (sin(q5) * (cos(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) - cos(q1) * sin(q2) * sin(q4)) - cos(q5) * (cos(q3) * sin(q1) + cos(q1) * cos(q2) * sin(q3)));
    
    ox = -sin(q7) * (sin(q6) * (sin(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) + cos(q1) * cos(q4) * sin(q2)) - cos(q6) * (cos(q5) * (cos(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) - cos(q1) * sin(q2) * sin(q4)) + sin(q5) * (cos(q3) * sin(q1) + cos(q1) * cos(q2) * sin(q3)))) - cos(q7) * (sin(q5) * (cos(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) - cos(q1) * sin(q2) * sin(q4)) - cos(q5) * (cos(q3) * sin(q1) + cos(q1) * cos(q2) * sin(q3)));
    
    ax = -cos(q6) * (sin(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) + cos(q1) * cos(q4) * sin(q2)) - sin(q6) * (cos(q5) * (cos(q4) * (sin(q1) * sin(q3) - cos(q1) * cos(q2) * cos(q3)) - cos(q1) * sin(q2) * sin(q4)) + sin(q5) * (cos(q3) * sin(q1) + cos(q1) * cos(q2) * sin(q3)));
    
    px = a4*(cos(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) - cos(q1)*sin(q2)*sin(q4)) - a3*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + d5*(sin(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + cos(q1)*cos(q4)*sin(q2)) + a6*(sin(q6)*(sin(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + cos(q1)*cos(q4)*sin(q2)) - cos(q6)*(cos(q5)*(cos(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) - cos(q1)*sin(q2)*sin(q4)) + sin(q5)*(cos(q3)*sin(q1) + cos(q1)*cos(q2)*sin(q3)))) - df*(cos(q6)*(sin(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + cos(q1)*cos(q4)*sin(q2)) + sin(q6)*(cos(q5)*(cos(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) - cos(q1)*sin(q2)*sin(q4)) + sin(q5)*(cos(q3)*sin(q1) + cos(q1)*cos(q2)*sin(q3)))) - a7*(cos(q7)*(sin(q6)*(sin(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) + cos(q1)*cos(q4)*sin(q2)) - cos(q6)*(cos(q5)*(cos(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) - cos(q1)*sin(q2)*sin(q4)) + sin(q5)*(cos(q3)*sin(q1) + cos(q1)*cos(q2)*sin(q3)))) - sin(q7)*(sin(q5)*(cos(q4)*(sin(q1)*sin(q3) - cos(q1)*cos(q2)*cos(q3)) - cos(q1)*sin(q2)*sin(q4)) - cos(q5)*(cos(q3)*sin(q1) + cos(q1)*cos(q2)*sin(q3)))) + d3*cos(q1)*sin(q2);

    ny = sin(q7) * (sin(q5) * (cos(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) + sin(q1) * sin(q2) * sin(q4)) - cos(q5) * (cos(q1) * cos(q3) - cos(q2) * sin(q1) * sin(q3))) - cos(q7) * (sin(q6) * (sin(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) - cos(q4) * sin(q1) * sin(q2)) - cos(q6) * (cos(q5) * (cos(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) + sin(q1) * sin(q2) * sin(q4)) + sin(q5) * (cos(q1) * cos(q3) - cos(q2) * sin(q1) * sin(q3))));
    
    oy = sin(q7) * (sin(q6) * (sin(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) - cos(q4) * sin(q1) * sin(q2)) - cos(q6) * (cos(q5) * (cos(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) + sin(q1) * sin(q2) * sin(q4)) + sin(q5) * (cos(q1) * cos(q3) - cos(q2) * sin(q1) * sin(q3)))) + cos(q7) * (sin(q5) * (cos(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) + sin(q1) * sin(q2) * sin(q4)) - cos(q5) * (cos(q1) * cos(q3) - cos(q2) * sin(q1) * sin(q3)));
    
    ay = cos(q6) * (sin(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) - cos(q4) * sin(q1) * sin(q2)) + sin(q6) * (cos(q5) * (cos(q4) * (cos(q1) * sin(q3) + cos(q2) * cos(q3) * sin(q1)) + sin(q1) * sin(q2) * sin(q4)) + sin(q5) * (cos(q1) * cos(q3) - cos(q2) * sin(q1) * sin(q3)));
    
    py = a3*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) - a4*(cos(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) + sin(q1)*sin(q2)*sin(q4)) - d5*(sin(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) - cos(q4)*sin(q1)*sin(q2)) - a6*(sin(q6)*(sin(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) - cos(q4)*sin(q1)*sin(q2)) - cos(q6)*(cos(q5)*(cos(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) + sin(q1)*sin(q2)*sin(q4)) + sin(q5)*(cos(q1)*cos(q3) - cos(q2)*sin(q1)*sin(q3)))) + df*(cos(q6)*(sin(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) - cos(q4)*sin(q1)*sin(q2)) + sin(q6)*(cos(q5)*(cos(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) + sin(q1)*sin(q2)*sin(q4)) + sin(q5)*(cos(q1)*cos(q3) - cos(q2)*sin(q1)*sin(q3)))) + a7*(cos(q7)*(sin(q6)*(sin(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) - cos(q4)*sin(q1)*sin(q2)) - cos(q6)*(cos(q5)*(cos(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) + sin(q1)*sin(q2)*sin(q4)) + sin(q5)*(cos(q1)*cos(q3) - cos(q2)*sin(q1)*sin(q3)))) - sin(q7)*(sin(q5)*(cos(q4)*(cos(q1)*sin(q3) + cos(q2)*cos(q3)*sin(q1)) + sin(q1)*sin(q2)*sin(q4)) - cos(q5)*(cos(q1)*cos(q3) - cos(q2)*sin(q1)*sin(q3)))) + d3*sin(q1)*sin(q2);

    nz = sin(q7) * (sin(q5) * (cos(q2) * sin(q4) - cos(q3) * cos(q4) * sin(q2)) - cos(q5) * sin(q2) * sin(q3)) + cos(q7) * (cos(q6) * (cos(q5) * (cos(q2) * sin(q4) - cos(q3) * cos(q4) * sin(q2)) + sin(q2) * sin(q3) * sin(q5)) + sin(q6) * (cos(q2) * cos(q4) + cos(q3) * sin(q2) * sin(q4)));
    
    oz = cos(q7) * (sin(q5) * (cos(q2) * sin(q4) - cos(q3) * cos(q4) * sin(q2)) - cos(q5) * sin(q2) * sin(q3)) - sin(q7) * (cos(q6) * (cos(q5) * (cos(q2) * sin(q4) - cos(q3) * cos(q4) * sin(q2)) + sin(q2) * sin(q3) * sin(q5)) + sin(q6) * (cos(q2) * cos(q4) + cos(q3) * sin(q2) * sin(q4)));
    
    az = sin(q6) * (cos(q5) * (cos(q2) * sin(q4) - cos(q3) * cos(q4) * sin(q2)) + sin(q2) * sin(q3) * sin(q5)) - cos(q6) * (cos(q2) * cos(q4) + cos(q3) * sin(q2) * sin(q4));
    
    pz = d1 + a6*(cos(q6)*(cos(q5)*(cos(q2)*sin(q4) - cos(q3)*cos(q4)*sin(q2)) + sin(q2)*sin(q3)*sin(q5)) + sin(q6)*(cos(q2)*cos(q4) + cos(q3)*sin(q2)*sin(q4))) + df*(sin(q6)*(cos(q5)*(cos(q2)*sin(q4) - cos(q3)*cos(q4)*sin(q2)) + sin(q2)*sin(q3)*sin(q5)) - cos(q6)*(cos(q2)*cos(q4) + cos(q3)*sin(q2)*sin(q4))) - a4*(cos(q2)*sin(q4) - cos(q3)*cos(q4)*sin(q2)) + d5*(cos(q2)*cos(q4) + cos(q3)*sin(q2)*sin(q4)) + d3*cos(q2) - a7*(sin(q7)*(sin(q5)*(cos(q2)*sin(q4) - cos(q3)*cos(q4)*sin(q2)) - cos(q5)*sin(q2)*sin(q3)) + cos(q7)*(cos(q6)*(cos(q5)*(cos(q2)*sin(q4) - cos(q3)*cos(q4)*sin(q2)) + sin(q2)*sin(q3)*sin(q5)) + sin(q6)*(cos(q2)*cos(q4) + cos(q3)*sin(q2)*sin(q4)))) - a3*cos(q3)*sin(q2);

    float rotation_matrix[3][3] = { nx, ox, ax, ny, oy, ay, nz, oz, az };
    float rotation[3];
    CvtRotationMatrixToEulerAngle(rotation_matrix, rotation);
    Coords coord = {px, py, pz, rotation[0], rotation[1], rotation[2]};

    return coord;
}

/*****************************************************************************************
*
*               左右臂转换为BASE坐标
*                                   input:1.Posture 左右臂位姿（1*6）
*                                         2.dire: 0 - 左, 1 - 右
*                                   output:Base：Base位姿（1*6）
*
******************************************************************************************/
Coords RobotKinematics::SingleToBaseCoords(Coords Posture, int dire)
{
    int i, j;
    float position[3], rotation[3], rotation_matrix[3][3];
    double T[4][4], Matrix[3][3], TBF[4][4];

    //----------------------------算法部分------------------------------//
    for (i = 0; i < 3; ++i) {
        rotation[i] = Posture[i + 3];
    }

    CvtEulerAngleToRotationMatrix(rotation, Matrix);

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            T[i][j] = Matrix[i][j];
        }
        T[i][3] = Posture[i];
    }
    T[3][0] = 0;
    T[3][1] = 0;
    T[3][2] = 0;
    T[3][3] = 1;
 
    if (dire == LEFT) {    //LEFT
        Matrix_multiplication_4x4_4x4(TBL, T, TBF);
    } else {
        Matrix_multiplication_4x4_4x4(TBR, T, TBF);
    }


    //---------------------输出最终的位姿kinematic_pose----------------------------------------//
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            rotation_matrix[i][j] = TBF[i][j];
        }
        position[i] = TBF[i][3];  //输出坐标
    }

    CvtRotationMatrixToEulerAngle(rotation_matrix, rotation);  //输出姿态
    Coords Base;
    for (i = 0; i < 3; ++i) {
        Base[i] = position[i];
        Base[i + 3] = rotation[i];
    }
    return Base;
}
/*****************************************************************************************
*
*               矩阵乘法4*4 * 4*4
*
******************************************************************************************/
void RobotKinematics::Matrix_multiplication_4x4_4x4(double a[][4],double b[][4],double c[][4])
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
        }
    }
}

/*****************************************************************************************
*
*               方向转换（电机→关节）
*
******************************************************************************************/
void RobotKinematics::cvDirServoToJoint(Angles &Update_joints)
{

    for (int i = 0; i < JOINTS; ++i) {
        Update_joints.at(i) = dir[i] * Update_joints.at(i);
    }
}

Angles RobotKinematics::cvRadToDegree(Angles Update_joints)
{
    float COEFFICIENT_KIN = 180.0 / PI;
    Angles angles;
    for (int i = 0; i < JOINTS; ++i) {
        angles.at(i) = COEFFICIENT_KIN * Update_joints.at(i);
    }
    return angles;
}

void RobotKinematics::CvtCoordsToRadCoords(Coords *coords)
{
    float COEFFICIENT_KIN = 180.0 / PI;
    for (int i = 3; i < 6; ++i) {
        coords->at(i) /= COEFFICIENT_KIN;
    }
}

void RobotKinematics::CvtRadCoordsToCoords(Coords *coords)
{
    float COEFFICIENT_KIN = 180.0 / PI;
    for (int i = 3; i < 6; ++i) {
        coords->at(i) *= COEFFICIENT_KIN;
    }
}
/*****************************************************************************************
 *
 *           遍历容器并打印
 *
 ******************************************************************************************/
void RobotKinematics::ArrayPrint(Encoders arr, String name) 
{
    Serial.print(name);
    Serial.print(" ");
    for (const auto elem : arr) {
        Serial.print(elem);
        Serial.print(' '); // 打印空格分隔符
    }
    Serial.println(); // 打印换行符
}
void RobotKinematics::ArrayPrintAngles(Angles arr, String name) 
{
    Serial.print(name);
    Serial.print(" ");
    for (const auto elem : arr) {
        Serial.printf("%f ", elem);
    }
    Serial.println(); // 打印换行符
}
void RobotKinematics::ArrayPrintCoords(Coords arr, String name) 
{
    Serial.print(name);
    Serial.print(" ");
    for (const auto elem : arr) {
        Serial.printf("%f ", elem);
    }
    Serial.println(); // 打印换行符
}