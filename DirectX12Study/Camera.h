#pragma once

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
};

