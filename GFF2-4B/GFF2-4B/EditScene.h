#pragma once
#include "AbstractScene.h"
#include "BoxCollider.h"
#include "StageData.h"
#include "Stage.h"
#include "PadInput.h"

#define OBJECT_TYPE_NUM 8   //配置できるオブジェクトの種類数

 //エリア区分
enum SelectErea
{
    STAGE_EDIT=0,
    TOOL_BOX,
};
class EditScene :
    public AbstractScene
{
private:
    int now_select_erea;                                  //現在選択中のエリア(0=ツールボックス 1=ステージ)
    int now_stage;                                        //現在編集中のステージ
    CURSOR cursor;                                        //マウスカーソル
    int stage_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];    //ステージのデータ格納用
    int old_stage_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];    //ステージの変更前データ格納用
    Stage* stage[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];      //床のオブジェクト
    int current_type;                                     //今選ばれているオブジェクトタイプ
    Location tool_location;                               //ツールボックスの左上座標
    Erea tool_size;                                       //左上のツールボックスの幅
    bool select_data[MAX_STAGE_HEIGHT][MAX_STAGE_WIDTH];  //そのデータが現在選択中かどうか

    int stage_width;        //ステージのブロックの横の個数 
    int stage_height;       //ステージのブロックの縦の個数
public:
    //コンストラクタ
    EditScene(int _stage);
    //デストラクタ
    ~EditScene();

    // 描画以外の更新を実装
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //ステージを生成する
    void LoadStageData(int _stage);

    //ステージのファイルを更新する
    void UpdateStageData(int _stage);

    //ステージの再読み込み
    void UpdateStage();

    //ひとつ前のデータの保持
    void SaveOldData();

    //今どのエリアにカーソルがあるか
    int ChechSelectErea(int _i, int _j);

    //ツールボックスが画面外に出ないように移動する
    void MoveInsideScreen();

    //すべてのステージオブジェクトを指定した値動かす
    void MoveAllStageObj(int _x, int _y);

    //どの箱が選択中かの情報をリセットする
    void ResetSelectData();
};


