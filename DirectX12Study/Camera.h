#pragma once
#include "Singletons.h"
class Camera :
    public Singletons
{
public:
    Camera();
    ~Camera();

    // Singletons��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual ULONG Release() override;

private:
    XMVECTOR _cameraPosition;
    XMVECTOR _cameraLookAt;
    XMVECTOR _cameraUp;

    XMMATRIX _perspectiveMatrix;
};

