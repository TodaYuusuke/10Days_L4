#include "EnemyBullet.h"
#include "../ColMaskGetter.h"

EnemyBullet::EnemyBullet() {

}

void EnemyBullet::Initialize() {
    isAlive_ = true;

    coll2D_.mask.SetBelongFrag(ColMaskGetter::GetEnemyAttack());
    coll2D_.mask.SetHitFrag(ColMaskGetter::GetWall() | ColMaskGetter::GetPlayer());

    // 衝突時
    coll2D_.stayLambda = [this](LWP::Object::Collision2D* hit) {
        isAlive_ = false;
        };
}

