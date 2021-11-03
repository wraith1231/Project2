#include "stdafx.h"
#include "Camera.h"
#include "SingletonManager.h"
#include "SceneManager.h"
#include "Time.h"
#include "Input.h"
#include "Window.h"
#include "D3D.h"

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
    _worldViewProjection = XMMatrixIdentity();
    UINT elementBySize = d3dUtil::CalcConstantBufferByteSize(sizeof(CameraConstants));

    auto temp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto temp2 = CD3DX12_RESOURCE_DESC::Buffer(elementBySize);
    Singleton<D3D>()->GetDevice()->CreateCommittedResource(&temp, D3D12_HEAP_FLAG_NONE,
        &temp2, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
        IID_PPV_ARGS(&_uploadCBuffer)
    );
}

void Camera::Update()
{
    
}

ULONG Camera::Release()
{
    return 0;
}

