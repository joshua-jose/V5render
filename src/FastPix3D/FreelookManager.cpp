#include "FastPix3D.h"

FreelookManager::FreelookManager()
{
	OldTime = pros::millis();
	Position = Vector3f();
	Rotation = Vector3f();
	Translation = Vector3f();
	RotationTranslation = Vector3f();
	Speed = 1;
}
FreelookManager::FreelookManager(Vector3f position)
{
	OldTime = pros::millis();
	Position = position;
	Rotation = Vector3f();
	Translation = Vector3f();
	RotationTranslation = Vector3f();
	Speed = 1;
}
FreelookManager::FreelookManager(Vector3f position, Vector3f rotation)
{
	OldTime = pros::millis();
	Position = position;
	Rotation = rotation;
	Translation = Vector3f();
	RotationTranslation = Vector3f();
	Speed = 1;
}
FreelookManager::FreelookManager(Vector3f position, Vector3f rotation, float speed)
{
	OldTime = pros::millis();
	Position = position;
	Rotation = rotation;
	Translation = Vector3f();
	RotationTranslation = Vector3f();
	Speed = speed;
}

Matrix FreelookManager::Update()
{
	clock_t time = clock();
	float speed = (time - OldTime) * Speed * .003f * (Input::getKeyDown(DIGITAL_L1) + 1);
	OldTime = time;

	int32 walkX = Input::getJoyXSpeed(1);
	int32 walkZ = Input::getJoyYSpeed(1);

	Matrix walkMatrix = Matrix::Translate(Vector3f(-walkX * speed, 0, -walkZ * speed)) * Matrix::RotateX(-Rotation.X) * Matrix::RotateY(-Rotation.Y);
	Translation = (Translation + walkMatrix * Vector3f()) * .8f;
	Position += Translation;

	RotationTranslation = (RotationTranslation - Vector3f(Input::getJoyYSpeed(0) * -.01f, Input::getJoyXSpeed(0) * .01f, 0)) * .75f;
	Rotation += RotationTranslation;
	Rotation.X = min(90.0f, max(-90.0f, Rotation.X));

	return getCameraSpace();
}
void FreelookManager::StopVelocities()
{
	Translation = Vector3f();
	RotationTranslation = Vector3f();
}

Matrix FreelookManager::getCameraSpace()
{
	return Matrix::Translate(Position) * getCameraSpaceRotationOnly();
}
Matrix FreelookManager::getCameraSpaceRotationOnly()
{
	return Matrix::RotateY(Rotation.Y) * Matrix::RotateX(Rotation.X) * Matrix::RotateZ(Rotation.Z);
}
Vector3f FreelookManager::getPosition()
{
	return Position;
}
Vector3f FreelookManager::getRotation()
{
	return Rotation;
}
float FreelookManager::getSpeed()
{
	return Speed;
}

void FreelookManager::setPosition(Vector3f position)
{
	Position = position;
}
void FreelookManager::setRotation(Vector3f rotation)
{
	Rotation = rotation;
}
void FreelookManager::setSpeed(float speed)
{
	Speed = speed;
}
