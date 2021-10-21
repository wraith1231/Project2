#include "stdafx.h"
#include "Camera.h"
#include "SingletonManager.h"
#include "SceneManager.h"
#include "Time.h"
#include "Input.h"
#include "Window.h"

Camera::Camera()
{
    Init();
}

Camera::~Camera()
{
    Release();
}

void Camera::Init()
{
    _cameraPosition = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
    _cameraLookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    _cameraUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    _perspectiveMatrix = XMMatrixPerspectiveFovLH(0.25f * XM_PI, Singleton<Window>()->GetAspectRatio(), 1.0f, 1000.0f);
}

void Camera::Update()
{
}

ULONG Camera::Release()
{
    return 0;
}

