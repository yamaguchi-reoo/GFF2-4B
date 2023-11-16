#include "DxLib.h"
#include "SceneManager.h"
#include "FpsController.h"
#include "PadInput.h"
#include "common.h"
#include "Title.h"

#define FRAMERATE 60.0 //�t���[�����[�g
//���C���v���O���� �J�n

int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow) {
    SetMainWindowText("GFF2-4B");         // �E�B���h�E�^�C�g����ݒ�

    ChangeWindowMode(TRUE);                        // �E�C���h�E���[�h�ŋN��

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // �E�C���h�E�̃T�C�Y

    if (DxLib_Init() == -1) return -1;             // DX���C�u�����̏���������

    SetDrawScreen(DX_SCREEN_BACK);                 // �`����ʂ𗠂ɂ���i�_�u���o�b�t�@�����O�j

    // �^�C�g�� �V�[���I�u�W�F�N�g�쐬
    SceneManager* sceneMng = new SceneManager((AbstractScene*) new Title());

    Fps* fps = new Fps;

    FpsController* FPSC= new FpsController(FRAMERATE, 800);

    // �Q�[�����[�v���A�V�[���}�l�W���[�ŃV�[���̍X�V
    while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr))
    {
        ClearDrawScreen(); // ��ʂ̏�����

        PadInput::UpdateKey();//�p�b�h�̓��͏���
        KeyInput::UpdateKey();//�L�[�{�[�h�̓��͏���

        // �V�[���}�l�W���[�ŃV�[���̕`��J�n
        sceneMng->Draw();

        FPSC->All();
        FPSC->Disp();

        //�����I��
        //Escape�L�[�܂��̓o�b�N�{�^�����������狭���I��
        if(KeyInput::OnKey(KEY_INPUT_ESCAPE)||PadInput::OnButton(XINPUT_BUTTON_BACK)) {  
            break;
        }
        ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f����

        fps->Wait();//�ҋ@
    };

    DxLib_End(); // DX���C�u�����g�p�̏I������
    return 0;    // �v���O�����̏I��
};