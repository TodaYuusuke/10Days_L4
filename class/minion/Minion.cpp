#include "Minion.h"
#include "state/MinionStateFactory.h"

using namespace LWP;

Minion::Minion()
    :   stateMap_{},
        currentState_(nullptr),
        statePattern_(),
        spriteSystem_(nullptr)
{
}

Minion::~Minion()
{
}

void Minion::Initialize()
{

    // �X�e�[�^�X
    stateMap_ = MinionStateFactory::CreateStates();
    ChangeState(MinionStateType::Idle);
    statePattern_.Init();

    spriteSystem_ = std::make_unique<MinionSpriteSystem>();

}

void Minion::Update()
{

    // �X�e�[�^�X
    statePattern_.Update();
    if (currentState_) {
        currentState_->Update(this);
    }

    // �X�v���C�g
    spriteSystem_->Update(statePattern_.GetCurrentBehavior(), {640.0f, 360.0f});

}

void Minion::DebugGUI()
{
}

void Minion::ChangeState(MinionStateType newStateType)
{

    // �O�̃X�e�[�g�������Exit����
    if (currentState_) {
        currentState_->Exit(this);
    }

    // ���̃X�e�[�g��������
    auto it = stateMap_.find(newStateType);

    // ���̃X�e�[�g�ɂ���Enter����
    if (it != stateMap_.end()) {
        currentState_ = it->second.get();
        currentState_->Enter(this);
    }

}
