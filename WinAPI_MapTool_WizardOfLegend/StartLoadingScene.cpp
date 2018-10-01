#include "stdafx.h"
#include "StartLoadingScene.h"

HRESULT StartLoadingScene::init(void)
{
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "Texture/Loading/loadingBackground_1000x1000.bmp", WINSIZEX, WINSIZEY);
	_loadingCircle = IMAGEMANAGER->addFrameImage("loadingCircle", "Texture/Loading/loadingCircle_26x1_3328x128.bmp", 3328, 128, 26, 1);

	_numbers = IMAGEMANAGER->addFrameImage("loadingNumber", "Texture/Loading/loadingNumber.bmp", 400, 60, 10, 1);

	_loadingImgIndex = _index = _count = 0;
	_loadingStr[0] = "�ҷ����� ��";
	_loadingStr[1] = "�ҷ����� ��.";
	_loadingStr[2] = "�ҷ����� ��..";
	_loadingStr[3] = "�ҷ����� ��...";

	//IMAGEMANAGER->addImage("initLoadingFront", "Texture/Loading/loadingBarFront.bmp", 600, 20, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("initLoadingBack", "Texture/Loading/loadingBarBack.bmp", 600, 20, true, RGB(255, 0, 255));

	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new Loading;
	_loading->init(); //�ε�ȭ�� �̹����� �ε� ���α׷�����

	_loadingBar = new ProgressBar;
	_loadingBar->init("initLoadingFront", "initLoadingBack", 100, WINSIZEY - 100, WINSIZEX - 200, 20);

	_loadingBar->setGauge(0, 100);

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	//SetTextAlign(getMemDC(), TA_CENTER); //�ؽ�Ʈ �߾�����

	return S_OK;
}

void StartLoadingScene::release(void)
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void StartLoadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update(); //�ε��� ������Ʈ
	_loadingBar->update();

	//�ε��Ϸ��� ������
	if (_loading->loadingDone()) //loadingImage�� loadingSound�� ���ڰ����� addimage, addframeimage�ϰ� �� �Ǹ� true
	{
		loadingEffect();
		SCENEMANAGER->loadScene("StartScene"); //���Ӿ����� ��ȯ
	}
}

void StartLoadingScene::render(void)
{
	//�ε�Ŭ���� ����
	//_loading->render();

	/*
	//��׶��� ����
	_background->render(getMemDC());
	
	//�ε��� Ŭ���� ����
	_loadingBar->render();

	if (_loading->getCurrnetGauge() < _loading->getLoadItem().size())
	{
		char str[128];
		sprintf_s(str, "%s.bmp", _loading->getLoadItem()[_loading->getCurrnetGauge()]->getImageResource().keyName.c_str());
		TextOut(getMemDC(), _loadingBar->getRect().left + 20, _loadingBar->getRect().top + 10, str, strlen(str));
	}

	float num = (float)_loading->getLoadItem().size();
	float cur = (float)_loading->getCurrnetGauge();
	float per = cur / num * 100;


	_numbers->frameRender(getMemDC(), _loadingBar->getRect().right - 200 - _numbers->getFrameWidth(), _loadingBar->getRect().top - 100, (int)per / 10, 0);
	_numbers->frameRender(getMemDC(), _loadingBar->getRect().right - 200, _loadingBar->getRect().top - 100, (int)per % 10, 0);

	_loadingBar->setGauge(per, 100);
	*/

	_count += 1;
	if (_count % 20 == 0)
	{
		_count = 0;
		_index = (_index + 1) % 4;
	}

	HFONT font;
	HFONT oldFont;
	font = CreateFont(20, 0, 0, 0, 1000, false, false, false, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	char str[128];
	sprintf_s(str, "%s", _loadingStr[_index].c_str());
	TextOut(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	float num = (float)_loading->getLoadItem().size();
	float cur = (float)_loading->getCurrnetGauge();
	float per = cur / num * 100;

	_loadingImgIndex = (_loadingCircle->getMaxFrameX() - 1) * (cur/num);
	_loadingCircle->frameRender(getMemDC(), WINSIZEX - _loadingCircle->getFrameWidth() - 50, WINSIZEY - _loadingCircle->getFrameHeight() - 50, _loadingImgIndex, 0);
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void StartLoadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();

	////�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	//for (int i = 0; i < 50; i++)
	//{
	//	_loading->loadImage(("�׽�Ʈ"+to_string(i)).c_str(), WINSIZEX, WINSIZEY);
	//}
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//��׶��� �̹���
	//_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	////Text
	//_loading->loadImage("tile1", "Texture/sky_100x100.bmp", 100, 100);
	//_loading->loadImage("tile2", "Texture/startBackgroundCloud_100x100.bmp", 100, 100);
	//_loading->loadImage("tile3", "Texture/ston2_100x100.bmp", 100, 100, true, RGB(255, 0, 255));
	//_loading->loadImage("tile4", "Texture/tree1_100x100.bmp", 100, 100, true, RGB(255, 0, 255));


	_loading->loadImage("miniMapImage", TILESIZEX / MINIMAP_RATE, TILESIZEY / MINIMAP_RATE, true, RGB(0, 0, 0));
	_loading->loadImage("tileMapImage", TILESIZEX, TILESIZEY);
	_loading->loadImage("tileMapPixel", TILESIZEX, TILESIZEY);
	_loading->loadImage("titleBackground", "Texture/UI/titleBackground_1920x1080.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("title", "Texture/UI/title_796x148.bmp", 796, 148, true, RGB(255, 0, 255));
	_loading->loadFrameImage("sampletilemap", "Texture/Tile/Wizard_Of_Legend_tile_672x288_21x9.bmp", 672, 288, SAMPLETILEX, SAMPLETILEY);
	_loading->loadFrameImage("tilemap", "Texture/Tile/Wizard_Of_Legend_tile_1344x576_21x9.bmp", 1344, 576, SAMPLETILEX, SAMPLETILEY);
	_loading->loadFrameImage("pixel_tile", "Texture/Tile/Wizard_Of_Legend_pixel_tile_1344x576_21x9.bmp", 1344, 576, SAMPLETILEX, SAMPLETILEY);


	_loading->loadImage("card_deck", "Texture/Tile/card_deck_110x169.bmp", 110, 169, true, RGB(255, 0, 255));


	// enemy
	_loading->loadFrameImage("shadow_attack1", "Texture/Enemy/shadowAttack_2x2_208x248.bmp", 208, 248, 2, 2);
	_loading->loadFrameImage("shadow_dead", "Texture/Enemy/shadowDead_10x2_1080x296.bmp", 1080, 296, 10, 2);
	_loading->loadFrameImage("shadow_idle", "Texture/Enemy/shadowIdle_1x2_68x248.bmp", 68, 248, 1, 2);
	_loading->loadFrameImage("shadow_walk", "Texture/Enemy/shadowWalk_6x2_600x264.bmp", 600, 264, 6, 2);




	_loading->loadFrameImage("mage_idle", "Texture/Enemy/mageIdle_78x320_1x2.bmp", 78, 320, 1, 2);
	_loading->loadFrameImage("mage_walk", "Texture/Enemy/mageWalk_552x328_6x2.bmp", 552, 328, 6, 2);
	_loading->loadFrameImage("mage_attack1", "Texture/Enemy/mageAttack1_896x156_7x1.bmp", 896, 156, 7, 1);
	_loading->loadFrameImage("mage_attack2", "Texture/Enemy/mageAttack2_296x304_2x2.bmp", 296, 304, 2, 2);
	_loading->loadFrameImage("mage_dead", "Texture/Enemy/mageDead_900x376_9x2.bmp", 900, 376, 9, 2);


	_loading->loadFrameImage("rogue_idle", "Texture/Enemy/rogueIdle_80x280_1x2.bmp", 80, 280, 1, 2);
	_loading->loadFrameImage("rogue_walk", "Texture/Enemy/rogueWalk_648x248_6x2.bmp", 648, 248, 6, 2);
	_loading->loadFrameImage("rogue_attack", "Texture/Enemy/rogueAttack_496x264_4x2.bmp", 496, 264, 4, 2);
	_loading->loadFrameImage("rogue_dash", "Texture/Enemy/rogueDash_240x200_2x2.bmp", 240, 200, 2, 2);
	_loading->loadFrameImage("rogue_dead", "Texture/Enemy/rogueDead_864x304_8x2.bmp", 864, 304, 8, 2);
	_loading->loadFrameImage("rogue_hide", "Texture/Enemy/rogueHide_276x264_3x2.bmp", 276, 264, 3, 2);

	// enemy - earth boss


	_loading->loadFrameImage("earthBoss_idle", "Texture/Enemy/Boss/bossIdle_132x224_1x1.bmp", 132, 224, 1, 1);
	_loading->loadFrameImage("earthBoss_attack1", "Texture/Enemy/Boss/bossAttack1_800x216_5x1.bmp", 800, 216, 5, 1);
	_loading->loadFrameImage("earthBoss_attack2", "Texture/Enemy/Boss/bossAttack2_1220x960_5x4.bmp", 1220, 960, 5, 4);
	_loading->loadFrameImage("earthBoss_attack3", "Texture/Enemy/Boss/bossAttack3_480x224_3x1.bmp", 480, 224, 3, 1);
	_loading->loadFrameImage("earthBoss_attackDelay", "Texture/Enemy/Boss/bossAttackDelay_510x208_3x1.bmp", 510, 208, 3, 1);
	_loading->loadFrameImage("earthBoss_dead", "Texture/Enemy/Boss/bossDead_120x172_1x1.bmp", 120, 172, 1, 1);
	_loading->loadFrameImage("earthBoss_hit", "Texture/Enemy/Boss/bossHit_660x456_5x2.bmp", 660, 456, 5, 2);
	_loading->loadFrameImage("earthBoss_jumpAttack", "Texture/Enemy/Boss/bossJumpAttack_1440x208_9x1.bmp", 1440, 208, 9, 1);


	// player
	_loading->loadFrameImage("player_attack1", "Texture/Player/playerAttack1_9x4_1224x624.bmp", 1224, 624, 9, 4);
	_loading->loadFrameImage("player_attack2", "Texture/Player/playerAttack2_8x4_1216x592.bmp", 1216, 592, 8, 4);
	_loading->loadFrameImage("player_attack3", "Texture/Player/playerAttack3_9x4_1260x608.bmp", 1260, 608, 9, 4);
	_loading->loadFrameImage("player_dash", "Texture/Player/playerDash_3x4_396x512.bmp", 396, 512, 3, 4);
	_loading->loadFrameImage("player_fall", "Texture/Player/playerFall_1x4_140x608.bmp", 140, 608, 1, 4);
	_loading->loadFrameImage("player_hit", "Texture/Player/playerHit_1x4_84x496.bmp", 84, 496, 1, 4);
	_loading->loadFrameImage("player_idle", "Texture/Player/playerIdle_1x4_64x528.bmp", 64, 528, 1, 4);
	_loading->loadFrameImage("player_walk", "Texture/Player/playerWalk_10x4_1120x496.bmp", 1120, 496, 10, 4);
	_loading->loadFrameImage("player_dead", "Texture/Player/playerDead_10x1_1040x168.bmp", 1040, 168, 10, 1);


	_loading->loadFrameImage("player_dummy", "Texture/Player/playerDummy_3x4_396x512.bmp", 396, 512, 3, 4);
	// Effect & skill
	_loading->loadFrameImage("water_skill", "Texture/Effect/waterBullet_464x112_4x1.bmp", 464, 112, 4, 1);
	_loading->loadFrameImage("ice_skill", "Texture/Effect/iceSkill_1312x220_8x1.bmp", 1312, 220, 8, 1);
	_loading->loadFrameImage("wind_skill", "Texture/Effect/windSkill_380x80_5x1.bmp", 380, 80, 5, 1);
	_loading->loadFrameImage("explode", "Texture/Effect/explode_4200x340_10x1.bmp", 4200, 340, 10, 1);

	_loading->loadImage("stoneBullet", "Texture/Effect/stoneBullet_80x78.bmp", 80, 78, true, RGB(255, 0, 255));

	
	_loading->loadFrameImage("appearEnemy", "Texture/Effect/appearEnemy_1200x187_10x1.bmp", 1200, 187, 10, 1);
	_loading->loadFrameImage("collideEffect2", "Texture/Effect/collideEffect2_240x145_3x1.bmp", 240, 145, 3, 1);
	_loading->loadFrameImage("collideEffect1", "Texture/Effect/collideEffect1_231x129_3x1.bmp", 231, 129, 3, 1);
	_loading->loadFrameImage("appearPlayer", "Texture/Effect/appearPlayer_384x512_4x1.bmp", 384, 512, 4, 1);
	

	//_loading->loadFrameImage("blue_portal", "Texture/Object/portal2_945x171_9x1.bmp", 945, 171, 9, 1);
	_loading->loadFrameImage("blue_portal", "Texture/Object/portal3_630x171_6x1.bmp", 630, 171, 6, 1);
	_loading->loadFrameImage("blue_portal_edge", "Texture/Object/portal4_630x171_6x1.bmp", 630, 171, 6, 1);

	loadingObjectImage();

	// ICON - skill
	_loading->loadImage("fireDash1Icon", "Texture/Icon/fireDash1Icon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("fireDash2Icon", "Texture/Icon/fireDash2Icon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("iceDashIcon", "Texture/Icon/iceDashIcon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("iceWaveIcon", "Texture/Icon/iceWaveIcon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("stoneAttackIcon", "Texture/Icon/stoneAttackIcon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("waterThrowIcon", "Texture/Icon/WaterThrowIcon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("stoneThrowIcon", "Texture/Icon/stoneThrowAttackIcon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("waterCircleIcon", "Texture/Icon/waterCircleIcon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));
	//////
	_loading->loadFrameImage("fireParticles", "Texture/Effect/fireParticles_768x512_6x4.bmp", 468, 512, 6, 4);
	//////


	// ICON - player
	_loading->loadImage("playerIcon", "Texture/Icon/playerIcon_30x30.bmp", 30, 30, true, RGB(255, 0, 255));

	// UI
	_loading->loadImage("playerHpBarBack", "Texture/PrograssBar/hpBarBack_189x30.bmp", 189, 30, true, RGB(255, 0, 255));
	_loading->loadImage("playerHpBarFront", "Texture/PrograssBar/hpBarFront_189x30.bmp", 189, 30, true, RGB(255, 0, 255));
	_loading->loadImage("bossHpBarBack", "Texture/PrograssBar/bosshpBarBack_300x41.bmp", 300, 41, true, RGB(255, 0, 255));
	_loading->loadImage("bossHpBarFront", "Texture/PrograssBar/bosshpBarFront_300x41.bmp", 300, 41, true, RGB(255, 0, 255));

	//_loading->loadImage("hpBarBack", "Texture/PrograssBar/hpBarBack.bmp", 600, 20, true, RGB(255, 0, 255));
	//_loading->loadImage("hpBarFront", "Texture/PrograssBar/hpBarFront.bmp", 600, 20, true, RGB(255, 0, 255));

	_loading->loadImage("inventory", "Texture/UI/inventory_432x630.bmp", 432, 630, true, RGB(255, 0, 255));
	_loading->loadImage("iconBox", "Texture/Icon/iconBox_44x44.bmp", 44, 44, true, RGB(255, 0, 255));
	_loading->loadImage("selectedIconBox", "Texture/Icon/selectedIconBox_50x50.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadFrameImage("loadingCircle", "Texture/Loading/loadingCircle_26x1_3328x128.bmp", 3328, 128, 26, 1);

	
	_loading->loadImage("card", "Texture/Tile/card_board_416x637.bmp", 416, 637, true, RGB(255, 0, 255));
	_loading->loadFrameImage("cardEffect", "Texture/Tile/card_board_effect_2496x637_6x1.bmp", 2496, 637, 6, 1);

	_loading->loadImage("aim", "Texture/UI/aim_115x115.bmp", 115, 115, true, RGB(255, 0, 255));

	_loading->loadImage("playerHpIcon", "Texture/UI/plyaerIcon_57x60.bmp", 57, 60, true, RGB(255, 0, 255));

	_loading->loadImage("button_f", "Texture/UI/FButton_27x30.bmp", 27, 30, true, RGB(255, 0, 255));
	_loading->loadImage("button_left", "Texture/UI/buttonleft_31x35.bmp", 31, 35, true, RGB(255, 0, 255));
	_loading->loadImage("button_right", "Texture/UI/buttonright_31x35.bmp", 31, 35, true, RGB(255, 0, 255));

}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void StartLoadingScene::loadingSound()
{
	_loading->loadSound("��������", "SOUND/OST/01WizardOfLegend_Title.mp3", true, true);
}

void StartLoadingScene::loadingEffect()
{
	EFFECTMANAGER->addEffect("�������", "ice_skill", 0.2, 20);
	EFFECTMANAGER->addEffect("����", "explode", 0.2, 10);
	EFFECTMANAGER->addEffect("�Ķ���Ż", "blue_portal", 0.2, 3);
	EFFECTMANAGER->addEffect("�Ķ���Ż_�����ڸ�", "blue_portal_edge", 0.2, 3);

	EFFECTMANAGER->addEffect("������", "appearEnemy", 0.15, 40);
	EFFECTMANAGER->addEffect("�浹1", "collideEffect1", 0.2, 40);
	EFFECTMANAGER->addEffect("�浹2", "collideEffect2", 0.2, 40);
	EFFECTMANAGER->addEffect("�÷��̾����", "appearPlayer", 0.2, 2);

}

void StartLoadingScene::loadingObjectImage()
{
	_loading->loadImage("���1", "Texture/Object/���1.bmp", 64 * 2, 2 * 160, true, RGB(255, 0, 255));	// 0
	_loading->loadImage("��1", "Texture/Object/��1.bmp", 96 * 2, 2 * 71, true, RGB(255, 0, 255));
	_loading->loadImage("��2", "Texture/Object/��2.bmp", 204 * 2, 2 * 210, true, RGB(255, 0, 255));
	_loading->loadImage("��3", "Texture/Object/��3.bmp", 204 * 2, 2 * 248, true, RGB(255, 0, 255));
	_loading->loadImage("��4", "Texture/Object/��4.bmp", 204 * 2, 2 * 210, true, RGB(255, 0, 255));
	_loading->loadImage("��ü1", "Texture/Object/��ü1.bmp", 44 * 2, 2 * 74, true, RGB(255, 0, 255));	// 5
	_loading->loadImage("��ü2", "Texture/Object/��ü2.bmp", 68 * 2, 2 * 64, true, RGB(255, 0, 255));
	_loading->loadImage("��ü3", "Texture/Object/��ü3.bmp", 31 * 2, 2 * 51, true, RGB(255, 0, 255));
	_loading->loadImage("��ü4", "Texture/Object/��ü4.bmp", 96 * 2, 2 * 96, true, RGB(255, 0, 255));
	_loading->loadImage("��ü5", "Texture/Object/��ü5.bmp", 118 * 2, 2 * 60, true, RGB(255, 0, 255));
	_loading->loadImage("��ü6", "Texture/Object/��ü6.bmp", 37 * 2, 2 * 33, true, RGB(255, 0, 255));	// 10
	_loading->loadImage("��ü7", "Texture/Object/��ü7.bmp", 112 * 2, 2 * 51, true, RGB(255, 0, 255));
	_loading->loadImage("��ü8", "Texture/Object/��ü8.bmp", 38 * 2, 2 * 39, true, RGB(255, 0, 255));
	_loading->loadImage("��ü9", "Texture/Object/��ü9.bmp", 64 * 2, 2 * 62, true, RGB(255, 0, 255));
	_loading->loadImage("��ü10", "Texture/Object/��ü10.bmp", 13 * 2, 2 * 26, true, RGB(255, 0, 255));
	_loading->loadImage("���1", "Texture/Object/���1.bmp", 45 * 2, 2 * 29, true, RGB(255, 0, 255));	// 15
	_loading->loadImage("�ٴ�1", "Texture/Object/�ٴ�1.bmp", 96 * 2, 2 * 41, true, RGB(255, 0, 255));
	_loading->loadImage("�����1", "Texture/Object/�����1.bmp", 26 * 2, 2 * 31, true, RGB(255, 0, 255));
	_loading->loadImage("�����2", "Texture/Object/�����2.bmp", 34 * 2, 2 * 48, true, RGB(255, 0, 255));
	_loading->loadImage("�����3", "Texture/Object/�����3.bmp", 34 * 2, 2 * 48, true, RGB(255, 0, 255));
	_loading->loadImage("�����4", "Texture/Object/�����4.bmp", 34 * 2, 2 * 48, true, RGB(255, 0, 255));	// 20
	_loading->loadImage("�����5", "Texture/Object/�����5.bmp", 34 * 2, 2 * 48, true, RGB(255, 0, 255));
	_loading->loadImage("�����6", "Texture/Object/�����6.bmp", 92 * 2, 2 * 86, true, RGB(255, 0, 255));
	_loading->loadImage("����1", "Texture/Object/����1.bmp", 32 * 2, 2 * 71, true, RGB(255, 0, 255));
	_loading->loadImage("����2", "Texture/Object/����2.bmp", 60 * 2, 2 * 80, true, RGB(255, 0, 255));
	_loading->loadImage("����3", "Texture/Object/����3.bmp", 70 * 2, 2 * 116, true, RGB(255, 0, 255));	// 25
	_loading->loadImage("����4", "Texture/Object/����4.bmp", 35 * 2, 2 * 62, true, RGB(255, 0, 255));
	_loading->loadImage("����5", "Texture/Object/����5.bmp", 22 * 2, 2 * 29, true, RGB(255, 0, 255));
	_loading->loadImage("����6", "Texture/Object/����6.bmp", 23 * 2, 2 * 41, true, RGB(255, 0, 255));
	_loading->loadImage("����7", "Texture/Object/����7.bmp", 19 * 2, 2 * 40, true, RGB(255, 0, 255));
	_loading->loadImage("����1", "Texture/Object/����1.bmp", 36 * 2, 2 * 54, true, RGB(255, 0, 255));	// 30
	_loading->loadImage("����1", "Texture/Object/����1.bmp", 158, 216, true, RGB(255, 0, 255));
	_loading->loadImage("����2", "Texture/Object/����2.bmp", 158, 216, true, RGB(255, 0, 255));
	_loading->loadImage("����3", "Texture/Object/����3.bmp", 158, 182, true, RGB(255, 0, 255));
	_loading->loadImage("����4", "Texture/Object/����4.bmp", 158, 182, true, RGB(255, 0, 255));	// 34
	_loading->loadFrameImage("����2", "Texture/Object/������_����2.bmp", 128, 68, 2, 1);
	_loading->loadFrameImage("��������1", "Texture/Object/������_��������1.bmp", 64, 188, 1, 2);
	_loading->loadFrameImage("��������1", "Texture/Object/������_��������1.bmp", 64, 188, 1, 2);	// 37
	

	_loading->loadImage("�ⱸ", "Texture/Object/endButton_259x240.bmp", 259, 240, true, RGB(255, 0, 255));
	_loading->loadImage("�Ա�", "Texture/Object/startButton_259x240.bmp", 259, 240, true, RGB(255, 0, 255)); // 39
	_loading->loadImage("â��", "Texture/Object/â��.bmp", 149, 130, true, RGB(255, 0, 255)); // 39
	
}
