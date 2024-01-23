#pragma once
#include "Skill_Obj.h"

class JoTexture;
class Audio;

class PB_Obj :
    public Skill_Obj
{
public:
    PB_Obj();
    ~PB_Obj();

    void Initialize()   override;
    void Update()       override;
    void LateUpdate()   override;
    void Render()       override; 
    void Release()      override;

    void Skill_Start()  override;

    void OnCollisionEnter(Collider* other)  override;
    void OnCollisionStay(Collider* other)   override;
    void OnCollisionExit(Collider* other)   override;

private:
    vector<Audio*> m_vecAudio;
    int iPlayIdx = 0;
};

