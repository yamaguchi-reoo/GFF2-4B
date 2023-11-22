#pragma once
class LockPlayer
{
private:
    bool lock_flg; //強制戦闘時のフラグ
    int grass_lx;  //左の草のX座標
    int grass_rx;  //右の草のX座標
    bool grass_flg;//草のアニメーションフラグ
    int img;    //蔓、草の画像
    int enemy_cnt; //敵の生成時間カウント
    int create_en; //生成した敵の数
    int attack_en; //斬った敵の数

public:
    //コンストラクタ
    LockPlayer();

    //デストラクタ
    ~LockPlayer();

    //更新処理
    void Update();

    //描画処理
    void Draw()const;

    //プレイヤーが強制戦闘ゾーンに閉じ込められているか(true:いる false:いない)
    void SetLockFlg(bool _flg) { lock_flg = _flg; }

    bool GetLockFlg() { return lock_flg; }
    bool GetGrassFlg() { return grass_flg; }


    //生成した敵の数をカウント
    void CntCreateEn() { create_en++; }

    //斬った敵の数をカウント
    void CntAttackEn() { attack_en++; }

    //草のアニメーション
    void GrassAnim();

};

