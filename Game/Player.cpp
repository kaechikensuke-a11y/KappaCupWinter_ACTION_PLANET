#include "stdafx.h"
#include "Player.h"
namespace
{
    const float JUMP = { 700.0f };
}
Player::Player()
{
	animationClips[enAnimationClip_Idle].Load("Assets/animData/playerIdle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    animationClips[enAnimationClip_Jump].Load("Assets/animData/playerJump.tka");
    animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/playerwalk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);

	m_playerRender.Init("Assets/modelData/player.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ);
    m_playerRender.SetPosition(Vector3::Zero);
	characterController.Init(15.0f, 35.0f, m_position);
}

Player::~Player()
{

}

void Player::Update()
{
    Move();
    Rotation();
    ManagerState();
    Animation();

    m_playerRender.Update();
}

void Player::Move()
{
    //xzの移動速度を0.0fにする。

    m_moveSpeed.x = 0.0f;
    m_moveSpeed.z = 0.0f;

    //左スティックの入力量を取得。

    Vector3 stickL;

    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();

    //カメラの前方向と右方向のベクトルを持ってくる。
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    //y方向には移動させない。
    forward.y = 0.0f;
    forward.Normalize();
    right.y = 0.0f;
    right.Normalize();

    //移動速度にスティックの入力量を加算する。
    if (g_pad[0]->IsPress(enButtonB))
    {
        return;
    }
    
    else
    {
        right *= stickL.x * 240.0f;
        forward *= stickL.y * 240.0f;
    }
    //移動速度に上記で計算したベクトルを加算する。
   

    //地面に付いていたら。
    if (characterController.IsOnGround())
    {
        //重力を無くす。
        m_moveSpeed.y = 0.0f;
        jumpCount = 0;
    }
        //Aボタンが押されたら。
        if (g_pad[0]->IsTrigger(enButtonA))
        {
            //ジャンプさせる。
            
            switch (getJumpItem)
            {
            case true:
                if (jumpCount < 2)
                {
                    m_moveSpeed.y = JUMP;
                    jumpCount++;

                }
                break;
            case false:
                if (jumpCount < 1)
                {

                    m_moveSpeed.y = JUMP;
                    jumpCount++;
                }
               
                break;

            }
     
        }

    
    //地面に付いていなかったら。
    else
    {
        //重力を発生させる。
        m_moveSpeed.y -= 20.0f;
    }
    m_moveSpeed += right + forward;

    //キャラクターコントローラーを使って座標を移動させる。
    m_position = characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

    //絵描きさんに座標を教える。
    m_playerRender.SetPosition(m_position);
}

void Player::Rotation()
{
    if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
    {
        //キャラクターの方向を変える。
        m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
        //絵描きさんに回転を教える。
        m_playerRender.SetRotation(m_rotation);
    }
}

void Player::ManagerState()
{

    if (characterController.IsOnGround() == false)
    {
        playerState = enAnimationClip_Jump;
        return;
    }

    else if (fabsf(m_moveSpeed.x) >= 0.001f or fabsf(moveSpeed.z) >= 0.001f)
    {
        //ステートを2(歩き)にする。
        playerState = enAnimationClip_Walk;

        //ダッシュ判定
       /* if (g_pad[0]->IsPress(enButtonY))
        {
            playerState = 3;
        }*/
    }
 
    else
    {
        playerState = enAnimationClip_Idle;
    }
}


void Player::Animation()
{
    switch (playerState) {
        //プレイヤーステートが0(待機)だったら。
    case 0:
        //待機アニメーションを再生する。
        m_playerRender.PlayAnimation(enAnimationClip_Idle);
        break;
        //プレイヤーステートが１(歩き中)だったら。
    case 1:
        //歩きアニメーションを再生する。
        m_playerRender.PlayAnimation(enAnimationClip_Walk);
        break;

    case 2:
        //ジャンプアニメーションを再生する。
        m_playerRender.PlayAnimation(enAnimationClip_Jump);
        break;
    
    //case 3:
       /* m_modelRender.PlayAnimation(enAnimationClip_Run);
        break;*/
    }

}

void Player::Render(RenderContext& rc)
{
    m_playerRender.Draw(rc);
}


