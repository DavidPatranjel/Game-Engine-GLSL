#pragma once

#include "esUtil.h"
#include "../NewTrainingFramework/Globals.h"

//Vector2

class Vector2
{
public:
	//Constructors
	Vector2() : x(0.0f), y(0.0f){}
	Vector2(GLfloat _x, GLfloat _y) : x(_x), y(_y) {}
	Vector2(GLfloat * pArg) : x(pArg[0]), y(pArg[1]) {}
	Vector2(Vector2 & vector) : x(vector.x), y(vector.y) {}

	//Vector's operations
	GLfloat Length();
	Vector2 & Normalize();
	Vector2 operator + (Vector2 & vector);
	Vector2 & operator += (Vector2 & vector);
	Vector2 operator - ();
	Vector2 operator - (Vector2 & vector);
	Vector2 & operator -= (Vector2 & vector);
	Vector2 operator * (GLfloat k);
	Vector2 & operator *= (GLfloat k);
	Vector2 operator / (GLfloat k);
	Vector2 & operator /= (GLfloat k);
	Vector2 & operator = (Vector2 & vector);
	Vector2 Modulate(Vector2 & vector);
	GLfloat Dot(Vector2 & vector);

	//access to elements
	GLfloat operator [] (unsigned int idx);

	//data members
	GLfloat x;
	GLfloat y;
};

//Vector3
class Vector4;

class Vector3
{
public:
	//Constructors
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(Vector4& v4);
	Vector3(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z) {}
	Vector3(GLfloat * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}
	Vector3(const Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z) {}
	
	//Vector's operations
	GLfloat Length();
	Vector3 & Normalize();
	Vector3 operator + (Vector3 & vector);
	Vector3 & operator += (Vector3 & vector);
	Vector3 operator - ();
	Vector3 operator - (Vector3 & vector);
	Vector3 & operator -= (Vector3 & vector);
	Vector3 operator * (GLfloat k);
	Vector3 & operator *= (GLfloat k);
	Vector3 operator / (GLfloat k);
	Vector3 & operator /= (GLfloat k);
	Vector3 & operator = (Vector3 & vector);
	Vector3 Modulate(Vector3 & vector);
	GLfloat Dot(Vector3 & vector);
	Vector3 Cross(Vector3 & vector);

	//access to elements
	GLfloat operator [] (unsigned int idx);

	// data members
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

//Vector4

class Matrix;

class Vector4
{
public:
	//Constructors
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(Vector3 v3): x(v3.x), y(v3.y), z(v3.z), w(1.0f) {}
	Vector4(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z), w(1.0f) {}
	Vector4(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4(GLfloat * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]), w(pArg[3]) {}
	Vector4(Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f){}
	Vector4(Vector3 & vector, GLfloat _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}
	Vector4(Vector4 & vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	//Vector's operations
	GLfloat Length();
	Vector4 & Normalize();
	Vector4 operator + (Vector4 & vector);
	Vector4 & operator += (Vector4 & vector);
	Vector4 operator - ();
	Vector4 operator - (Vector4 & vector);
	Vector4 & operator -= (Vector4 & vector);
	Vector4 operator * (GLfloat k);
	Vector4 & operator *= (GLfloat k);
	Vector4 operator / (GLfloat k);
	Vector4 & operator /= (GLfloat k);
	Vector4 & operator = (Vector4 & vector);
	Vector4 Modulate(Vector4 & vector);
	GLfloat Dot(Vector4 & vector);

	//matrix multiplication
	Vector4 operator * ( Matrix & m );

	//access to elements
	GLfloat operator [] (unsigned int idx);

	//data members
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

//Matrix 4 X 4


class Matrix
{
public:
	//constructors
	Matrix() {}
	Matrix(GLfloat val);
	Matrix(Matrix & mat);

	// Matrix operations
	Matrix & SetZero();
	Matrix & SetIdentity();

	Matrix & SetRotationX(GLfloat angle);
	Matrix & SetRotationY(GLfloat angle);
	Matrix & SetRotationZ(GLfloat angle);
	Matrix & SetRotationAngleAxis( float angle, float x, float y, float z );

	Matrix & SetScale(GLfloat scale);
	Matrix & SetScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
	Matrix & SetScale(GLfloat * pScale);
	Matrix & SetScale(Vector3 &scaleVec);

	Matrix & SetTranslation(GLfloat x, GLfloat y, GLfloat z);
	Matrix & SetTranslation(GLfloat *pTrans);
	Matrix & SetTranslation(Vector3 &vec);

	Matrix & SetPerspective(GLfloat fovY, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane);

	Matrix Transpose();

	Matrix operator + (Matrix & mat);
	Matrix & operator += (Matrix & mat);
	Matrix operator - (Matrix & mat);
	Matrix &operator -= (Matrix & mat);

	Matrix operator * (Matrix & mat);
	Matrix operator * (GLfloat k);
	Matrix & operator *= (GLfloat k);

	Vector4 operator * (Vector4 & vec);

	Matrix & operator = (Matrix & mat);

	//data members
	GLfloat m[4][4];
};


// Camera 

class Camera {
public:

	// constructors
	Camera() :
		position(0.0f, 0.0f, 200.0f),
		target(0.0f, 0.0f, -1.0f),
		up(0.0f, 1.0f, 0.0f),
		moveSpeed(40.5f),
		rotateSpeed(0.8f),
		nearPlane(0.2f), farPlane(2000.0f), fov(0.785f),
		deltaTime(0.1f),
		xAxis(1.0f, 0.0f, 0.0f),
		yAxis(0.0f, 1.0f, 0.0f),
		zAxis(0.0f, 0.0f, 1.0f),
		viewMatrix(0.0f),
		worldMatrix(0.0f)
	{
		updateWorldView();
		GLfloat aspect = (float) Globals::screenWidth / Globals::screenHeight;
		perspectiveMatrix.SetPerspective(fov, aspect, nearPlane, farPlane);
	}

	Camera(Vector3 _position,
			Vector3 _target,
			Vector3 _up,
			GLfloat _moveSpeed = 0.01f,
			GLfloat _rotateSpeed = 0.01f,
			GLfloat _nearPlane = 0.2f,
			GLfloat _farPlane = 2000.0f,
			GLfloat _fov = 0.785f,
			GLfloat _deltaTime = 0.1f,
			Vector3 _xAxis = Vector3(1.0f, 0.0f, 0.0f),
			Vector3 _yAxis = Vector3(0.0f, 1.0f, 0.0f),
			Vector3 _zAxis = Vector3(0.0f, 0.0f, 1.0f),
			Matrix _viewMatrix = 0.0f,
			Matrix _worldMatrix = 0.0f) : 
				position(_position), target(_target), up(_up), moveSpeed(_moveSpeed),
				rotateSpeed(_rotateSpeed), nearPlane(_nearPlane), farPlane(_farPlane), fov(_fov),
				deltaTime(_deltaTime), 
				xAxis(_xAxis), yAxis(_yAxis), zAxis(_zAxis),
				viewMatrix(_viewMatrix), worldMatrix(_worldMatrix), perspectiveMatrix()
	{
		updateWorldView();
		GLfloat aspect = (float) Globals::screenWidth / Globals::screenHeight;
		perspectiveMatrix.SetPerspective(fov, aspect, nearPlane, farPlane);
	}

	// Camera operations
	Camera& moveOx(int sense);
	Camera& moveOy(int sense);
	Camera& moveOz(int sense);
	Camera& rotateOx(int sense);
	Camera& rotateOy(int sense);
	Camera& rotateOz(int sense);
	Camera& updateAxes();
	Camera& updateWorldView(); // uA + wM + vM

	// setters
	void setDeltaTime(GLfloat dt);

	//data members
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat nearPlane;
	GLfloat farPlane;
	GLfloat fov;
	GLfloat deltaTime;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	Matrix viewMatrix;
	Matrix worldMatrix;
	Matrix perspectiveMatrix;
};

