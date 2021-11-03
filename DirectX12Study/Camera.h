#pragma once

struct CameraConstants
{
    XMFLOAT4X4 WorldViewProj;
};

class Camera
{
public:
    Camera();
    ~Camera();

    void Init();
    void Update();
    ULONG Release();

private:
    XMVECTOR _cameraPosition;
    XMVECTOR _cameraLookAt;
    XMVECTOR _cameraUp;

    XMMATRIX _perspectiveMatrix;
    XMMATRIX _worldViewProjection;
    
    CameraConstants _camCons;

    wrl::ComPtr<ID3D12Resource> _uploadCBuffer;
};

