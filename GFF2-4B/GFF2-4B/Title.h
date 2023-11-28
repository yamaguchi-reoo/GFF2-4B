#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
enum class TITLE_MENU
{
    GAME_START = 0,
    GAME_END
};
class Title :
    public AbstractScene
{
private:

    int title_font;             //タイトル文字画像

    int game_start_image;       //文字画像(開始:未選択状態)
    int game_start_select;      //文字画像(開始:選択状態)

    int game_finish_image;      //文字画像(終了:未選択状態)
    int game_finish_select;     //文字画像(終了:選択状態)

    int Select;                 //選択数
    bool Once;                  //Lスティックでカーソルを動かす用

    int title_alpha;            //タイトル画像の透明度
    int font_alpha;             //フォント画像の透明度
    int title_x;                //タイトルのX座標

public:
    //コンストラクタ
    Title();

    //デストラクタ
    ~Title();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    void ImageLoad(int& _handle, const char* _file_name);
};


