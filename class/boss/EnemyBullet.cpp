#include "EnemyBullet.h"
#include "../ColMaskGetter.h"

const std::string kBulletPath = "Bullet_RED.png";

EnemyBullet::EnemyBullet() {
    Initialize();
}

void EnemyBullet::Initialize() {
    sprite_.LoadTexture(kBulletPath);
    isAlive_ = false;
    // spriteの設定
    float exSize = sprite_.GetFitSizeImpl(&sprite_.material).x * 0.5f;
    exSize = 10.0f / exSize;
    sprite_.worldTF.scale = { exSize,exSize,0.0f };
    sprite_.isActive = false;

    // コライダーの設定
    coll2D_.mask.SetBelongFrag(ColMaskGetter::GetEnemyAttack());
    coll2D_.mask.SetHitFrag(ColMaskGetter::GetWall() | ColMaskGetter::GetPlayer());
    coll2D_.isActive = false;
    // 衝突時
    coll2D_.enterLambda = [this](LWP::Object::Collision2D* hit) {
        isAlive_ = false;
        coll2D_.isActive = false;
        sprite_.isActive = false;
        };
    coll2D_.worldTF.Parent(&sprite_.worldTF);
    LWP::Object::Collider2D::Circle& circle = coll2D_.SetBroadShape<LWP::Object::Collider2D::Circle>();
    circle.radius = exSize;

}

void EnemyBullet::Update(const LWP::Math::Vector2& dir) {
    sprite_.DebugGUI();
    sprite_.worldTF.translation += {dir.x, dir.y, 0.0f};

    Limit();
}

void EnemyBullet::SetBullet(const LWP::Math::Vector2& pos, const float& radius) {
    sprite_.worldTF.translation = { pos.x,pos.y,0.0f };
    sprite_.worldTF.scale = { radius,radius,0.0f };
    isAlive_ = true;
    coll2D_.isActive = isAlive_;
    sprite_.isActive = isAlive_;
}

void EnemyBullet::Limit() {
    if (std::fabsf(sprite_.worldTF.translation.y) > LWP::Info::GetWindowHeightF()
        || std::fabsf(sprite_.worldTF.translation.x) > LWP::Info::GetWindowWidthF()) {
        isAlive_ = false;
    }
    coll2D_.isActive = isAlive_;
    sprite_.isActive = isAlive_;
}
