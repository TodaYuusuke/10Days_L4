#include "Wall.h"
#include "../PlayerGlobalData.h"
#include "../../ColMaskGetter.h"
#include "../wall/WallManager.h"
#include "../../boss/EnemyManager.h"

using namespace LWP::Math;
using namespace LWP::Utility;
using namespace LWP::Object;

Wall::Wall()
	:	start_({0.0f,0.0f}),
		end_({ 0.0f,0.0f }),
		hp_(0),
		lifeTime_(0.0f),
		sprite_(),
		isDead_(false),
		collider_()
{
}

Wall::Wall(const LWP::Math::Vector2& start, const LWP::Math::Vector2 end, int hp, float lifeTime)
	:	start_(start),
		end_(end),
		hp_(hp),
		lifeTime_(lifeTime),
		sprite_(),
		isDead_(false),
		collider_()
{
	Initilaize();
}

Wall::~Wall()
{
}

void Wall::Initilaize()
{

	sprite_.LoadTexture("Wall.png");

	// 位置
	const Vector2 spritePosition = (end_ + start_) / 2.0f;
	sprite_.worldTF.translation = { spritePosition.x, spritePosition.y, PlayerGlobalData::GetWallPositionZ()};
	// 回転
	const Vector2 kDir2D = (end_ - start_).Normalize();
	const Vector3 kDir3D = { kDir2D.x, kDir2D.y, 0.0f };
	sprite_.worldTF.rotation = Quaternion::ConvertFromTo(Vector3{ 0.0f,1.0f,0.0f }, kDir3D);
	// 大きさ
	sprite_.worldTF.scale = PlayerGlobalData::GetWallSpriteScale();
	const float kLength = (end_ - start_).Length();
	sprite_.worldTF.scale.y = (kLength / PlayerGlobalData::GetWallTextureSize().y) + PlayerGlobalData::GetLineSpriteScale().x;
	sprite_.material.uvTransform.scale = sprite_.worldTF.scale;

	// レクタングル
	Collider2D::Rectangle& rectangle = collider_.SetBroadShape<Collider2D::Rectangle>();
	rectangle.size = { PlayerGlobalData::GetWallTextureSize().x * sprite_.worldTF.scale.x,
		PlayerGlobalData::GetWallTextureSize().y * sprite_.worldTF.scale.y };
	rectangle.rotation = std::atan2f(kDir2D.y, kDir2D.x);
	rectangle.rotation += 1.57f;
	// 親子
	collider_.worldTF.Parent(&sprite_.worldTF);

	// 関数
	// ヒットした瞬間のとき
	collider_.enterLambda = [this](Collision2D* hitTarget) {
		if (hitTarget->mask.GetBelongFrag() & ColMaskGetter::GetEnemy()) {
			hp_ -= *wallManager_->GetEnemyManager()->GetEnemyAttackPowerPtr();
			if (hp_ <= 0) {
				isDead_ = true;
			}
		}
		};

	// マスク、所属
	collider_.mask.SetBelongFrag(ColMaskGetter::GetWall());
	// マスク,hit
	collider_.mask.SetHitFrag(ColMaskGetter::GetPlayer() | ColMaskGetter::GetEnemy() | ColMaskGetter::GetBullet() | ColMaskGetter::GetEnemyAttack());

}

void Wall::Update()
{

	//生存時間
	lifeTime_ -= static_cast<float>(LWP::Info::GetDeltaTime());

	if (lifeTime_ <= 0.0f) {
		isDead_ = true;
	}

	// 色
	int colorValue = static_cast<int>(255.0f * Easing::CallFunction(Easing::Type::Liner, std::clamp(lifeTime_, 0.0f, 1.0f)));
	sprite_.material.color = { colorValue , colorValue , colorValue , colorValue };

}
