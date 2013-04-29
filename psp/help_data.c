#include "psp.h"

#define HELP_TOTAL_ENTRIES 27

static char help_data_en[HELP_TOTAL_ENTRIES][1024]  __attribute__((aligned(16))) = {
	//english
		"Select slot to use for loading and saving state.",
		"Load state from current slot\nCurrent game progress will be lost!",
		"Save state to current slot.",
		"Import savestate from another emulator.\nY's uosnes9x and zsnes should work (not always)",
		"Takes a jpeg snapshot from current game screen.\nIt will be used as game icon in browser.",
		"Reset the SNES.\nGame progress will be lost!",
		"Choose between 3 modes :\n-off : sound processor not emulated, incompatible with some games\n-emulated/no output : compatible mode, but no sound.\n-on : compatible mode with sound.",
		"Choose mixing frequency.\nHigher sounds better, but is slower.",
		"Choose the GPUPack.GFX engine :\n-Approx. software\n-Accurate software mode\nPSP Accelerated\nPSP accel.+accu.Soft. : mixed mode\nPSP accel.+approx.Soft. : mixed mode\nThe PSP hardware cannot handle all snes graphics operations.\nFor this the mixed modes have been created.\nThey provide an autoswitch to best rendering mode, depending on\ncurrent snes graphics requirements.\nUse approx. modes for speed and accurate mode for quality.",
		"Frameskip is used to boost speed\nFrameskip 0 means all snes frames are drawn\n1 is 1 frame skipped for 1 frame rendered\n2 is 2 frame skipped for 1 frame rendered...",
		"Show how much call to rendering function was needed to compute the screen\nThe lowest, the fastest. This is usefull to check the impact of hacks (below)\n",
		"Use SNESAdvance speedhacks if available in the database.\nOnly used at rom loading time.",
		"Ignore Fixed Colour Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (gradient, ...)",
		"Ignore Windows clipping Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (missing area, ...)",
		"Ignore Add/Sub modes Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (pixels being opaque instead of transparent, ...)",
		"Ignore Palette writes Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (wrong colours, ...)",
		"Fast mode 7.\nWith this hack some controls aren't done in mode 7.\nGFX may be altered (pixels being opaque instead of transparent, ...)",
		"OBJ On/Off.\nUse this to disactivate(Off) SPRITES drawing.",
		"BG0 On/Off.\nUse this to disactivate(Off) BACKGROUND 0 drawing.",
		"BG1 On/Off.\nUse this to disactivate(Off) BACKGROUND 1 drawing.",
		"BG2 On/Off.\nUse this to disactivate(Off) BACKGROUND 2 drawing.",
		"BG3 On/Off.\nUse this to disactivate(Off) BACKGROUND 3 drawing.",
		"No Transparency.\nUse this to force no transparency rendering.\nGFX may be altered (pixels being opaque instead of transparent, ...)",
		"Fast sprites.\nUse this to disactivate intra-sprites priorities handling.\nGFX may be altered",
		"Render PAL as NTSC.\nPAL games have 240 vertical lines, NTSC 224.\nMost PAL games are NTSC conversion and so the 16 more lines not used.\nEnabling this option will help removing the black border at bottom.",
		"Autosave timer.\nThis usefull feature will create a savestate for you every n minutes.\nn can be choosen between 1 to 10min.",
		"Autosave SRAM.\nThis option will save SRAM after each modification by the game.\nThis can cause big slowdowns in some games."
};

static char help_data_ja[HELP_TOTAL_ENTRIES][1024]  __attribute__((aligned(16))) = {
	//japanese TODO : translation
		"�X���b�g��I��ŁA�����ŃX�e�[�g�����[�h�ƕۑ��ł��܂��B",
		"���݂̃X���b�g����X�e�[�g�����[�h\n���݂̃Q�[����񂪏����Ă��܂��̂ł����ӁB",
		"���݂̃X���b�g�ɃX�e�[�g��ۑ��B",
		"�X�e�[�g�f�[�^�𑼂̃G�~���[���烍�[�h\nY��uosnes9x��ZSNES�����v�����ł����ꍇ�ɂ���ďo���܂���B",
		"���݂̃Q�[����ʂ�JPEG�摜�ɕۑ�\n�u���E�U�[�ɃA�C�R���Ƃ��ė��p����܂��B",
		"SFC���Z�b�g\n���݂̃Q�[����񂪏����Ă��܂��̂ł����ӁB",
		"�O�̃��[�h���I�ׂ�A\n-�G�~�����[�g���Ȃ� : ���Ȃ��A��CPU�Ȃ�, �Q�[���ɂ���ē������Ȃ��B\n-�G�~�����[�g���邪�o�͂��Ȃ� : ���Ȃ��A��CPU�L��\n-�G�~�����[�g���A�o�͂��� : ���L��A��CPU�L��",
		"���̕i����I�ԁA\n������΍����قǁA�����ǂ����A�G�~�����x���Ȃ�܂��B",
		"�`��G���W���̑I��\n-�قڐ��m�ȃ\\�t�g�E�F�A�`��\n-���m�ȃ\\�t�g�E�F�A�`��\nPSP�A�N�Z�����[�^\nPSP�A�N�Z�����[�^ + ���m�ȃ\\�t�g�E�F�A�`�� : �������[�h\nPSP�A�N�Z�����[�^ + �قڐ��m�ȃ\\�t�g�E�F�A�`�� : �������[�h\nPSP�̃n�[�h�E�G�A�����ׂẴX�[�t�@�~�̕`��@�\\���Č��o���Ȃ����߁A\n�\\�t�g�E�G�A���g���������[�h�����݂���̂ł��B\n�����I�ɕ`��ړI�ɂ����\n�x�X�g�ȕ`�惋�[�`����I������ł����A\n�قڐ��m�ȃ\\�t�g�E�F�A�`�悪���x��D��A���m�ȃ\\�t�g�E�F�A�`�悪�{���Ɠ����`���ڎw���܂��B",
		"Snes�̑��x��ڎw�����߁A���鎞�ɕ`�悵�Ȃ��Ƃ����I�����o���܂�\n0�̏ꍇ�A���ׂẴt���[�����`��\n1�͂P�F�P�`�悷��i����A���Ȃ��̐؂�ւ��j\n2�͕`����P�񂷂�A�Q�񂵂Ȃ�...",
		"������ʂ�`�悷��̂ɕK�v�Ƃ����`��֐����Ăяo���Ă��邩��\\�����܂��B\n�Ⴏ��΁A�����Ȃ�܂��B����̓n�b�N(�ڍׂ͈ȉ�)�̉e�����m�F����̂Ɏg���܂��B\n",
		"�f�[�^�x�[�X�ɑ��݂���ꍇSNESAdvance�X�s�[�h�n�b�N���g�p���܂��B\nROM�ǂݍ��ݎ��݂̂Ɏg���܂��B",
		"�Œ肵���F�ʕω��𖳎����܂��B\n���̂悤�ȕύX�͉�ʂ̕ω����i�s���邫�������ɂ͂Ȃ�܂���B\nCG���ω�����\\��������܂��B(�O���f�[�V�����Ȃ�)",
		"��ʂ�؂���ω��𖳎����܂��B\n���̂悤�ȕύX�͉�ʂ̕ω����i�s���邫�������ɂ͂Ȃ�܂���B\nCG���ω�����\\��������܂��B(missing area�Ȃ�)",
		"�ǉ�/�T�u���[�h�̕ω��𖳎����܂��B\n���̂悤�ȕύX�͉�ʂ̕ω����i�s���邫�������ɂ͂Ȃ�܂���B\nCG���ω�����\\��������܂��B(�s�N�Z�������߂̑���ɂ����ނȂ�)",
		"�p���b�g�������ω��𖳎����܂��B\n���̂悤�ȕύX�͉�ʂ̕ω����i�s���邫�������ɂ͂Ȃ�܂���B\nCG���ω�����\\��������܂��B(������F�ɂȂ�Ȃ�)",
		"�������[�h7�ł��B\n���̃n�b�N�ł͂������̃R���g���[�������[�h7�łł��܂���B\nCG���ω�����\\��������܂��B(�s�N�Z�������߂̑���ɂ����ނȂ�)",
		"�I�u�W�F�N�g�̃I��/�I�t�ł��B\n�I�u�W�F�N�g�`��𖳌���(�I�t)�ɂ��邽�߂Ɏg���܂��B",
		"�w�i0�̃I��/�I�t�ł��B\n�w�i0�̕`��𖳌���(�I�t)�ɂ��邽�߂Ɏg���܂��B",
		"�w�i1�̃I��/�I�t�ł��B\n�w�i1�̕`��𖳌���(�I�t)�ɂ��邽�߂Ɏg���܂��B",
		"�w�i2�̃I��/�I�t�ł��B\n�w�i2�̕`��𖳌���(�I�t)�ɂ��邽�߂Ɏg���܂��B",
		"�w�i3�̃I��/�I�t�ł��B\n�w�i3�̕`��𖳌���(�I�t)�ɂ��邽�߂Ɏg���܂��B",
		"���߂������܂���B\n���ߕ`��������I�ɂȂ������߂Ɏg���܂��B\nCG���ω�����\\��������܂��B(�s�N�Z�������߂̑���ɂ����ނȂ�)",
		"�����X�v���C�g\n�����X�v���C�g�̗D�摀��𖳌��ɂ��邽�߂Ɏg���܂��B\nCG���ω�����\\��������܂��B",
		"PAL��NTSC�Ƃ��ĕ`�悵�܂��B\nPAL�̃Q�[����240�{�̐�����������ANTSC��224�{����܂��B\nMost �قƂ�ǂ�PAL�Q�[����NTSC�̕ϊ��̂���16�{���g���Ă��܂���B\n���̃I�v�V������L���ɂ��邱�Ƃŉ����̍���������菜�����Ƃ��ł��܂��B",
		"�����Z�[�u�^�C�}�[�ł��B\n����͉��������ɃX�e�[�g�Z�[�u�����Ă����֗��ȋ@�\\�ł��B\n�l��1�`10���ɐݒ�ł��܂��B",
		"SRAM�����Z�[�u\n���̃I�v�V������SRAM���Q�[���ɂ��ύX�����邽�тɕۑ������܂��B\n����͈ꕔ�̃Q�[���ő傫�ȑ��ƒቺ�������N�������Ƃ�����܂��B"
};

static char help_data_fr[HELP_TOTAL_ENTRIES][1024]  __attribute__((aligned(16))) = {
	//french TODO : translation
	  "Selectionne le slot pour charger/sauvegarder (savestate)",
	  "Charger sauvegarde du slot courant\nLa partie en cours sera perdu!",
	  "Sauvegarder dans le slot courant.",
		"Importer une sauvegarde (savestate) d'un autre emulateur.\nuosnes9x et zsnes sont supportes.\n\nCependant l'import peut echouer et le jeu risque de se figer...",
		"Sauvegarder une capture ecran de la partie en cours.\nElle sera utilisee sur l'ecran de selection des ROMS.",
		"Reseter la SNES.\nLa partie en cours sera perdu!",
		"3 modes possibles :\n-off : son non-emule, incompatible avec certains jeux\n-emule/inaudible : mode compatible, pas de son.\n-on : mode compatible avec son (plut lent)",
		"Frequence de mixage du son : \nplus elle est haute, meilleur est la qualite\net plus lente est l'emulation.",		
		"Mode GPUPack.GFX :\n-Approx. software\n-Accurate software mode\nPSP Accelerated\nPSP accel.+accu.Soft. : mixed mode\nPSP accel.+approx.Soft. : mixed mode\nLa PSP ne peut pas gerer tous les modes graphiques de la SNES.\nPour cela les mixed modes ont ete crees.\nIls permettent une selection automatique du meilleur mode,\nen fonction du mode snes actif.\nLes modes approx. sont rapides et parfois loin de l'original\nles modes accurate sont fideles mais plus lent.",
		"Le frameskip est utilise pour accelerer l'emulation.\nA frameskip 0 toutes les images sont calculees et affichees\nA frameskip 1, 1 image est sautee pour une calculee\nA 2, 2 images sont sautees pour une calculee...",
		"Show how much call to rendering function was needed to compute the screen\nThe lowest, the fastest. This is usefull to check the impact of hacks (below)\n",
		"Use SNESAdvance speedhacks if available in the database.\nOnly used at rom loading time.",
		"Ignore Fixed Colour Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (gradient, ...)",
		"Ignore Windows clipping Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (missing area, ...)",
		"Ignore Add/Sub modes Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (pixels being opaque instead of transparent, ...)",
		"Ignore Palette writes Changes.\nSuch changes won't trigger the screen update process.\nGFX may be altered (wrong colours, ...)",
		"Fast mode 7.\nWith this hack some controls aren't done in mode 7.\nGFX may be altered (pixels being opaque instead of transparent, ...)",
		"OBJ On/Off.\nUse this to disactivate(Off) SPRITES drawing.",
		"BG0 On/Off.\nUse this to disactivate(Off) BACKGROUND 0 drawing.",
		"BG1 On/Off.\nUse this to disactivate(Off) BACKGROUND 1 drawing.",
		"BG2 On/Off.\nUse this to disactivate(Off) BACKGROUND 2 drawing.",
		"BG3 On/Off.\nUse this to disactivate(Off) BACKGROUND 3 drawing.",
		"No Transparency.\nUse this to force no transparency rendering.\nGFX may be altered (pixels being opaque instead of transparent, ...)",
		"Fast sprites.\nUse this to disactivate intra-sprites priorities handling.\nGFX may be altered",
		"Render PAL as NTSC.\nPAL games have 240 vertical lines, NTSC 224.\nMost PAL games are NTSC conversion and so the 16 more lines not used.\nEnabling this option will help removing the black border at bottom.",
		"Autosave timer.\nThis usefull feature will create a savestate for you every n minutes.\nn can be choosen between 1 to 10min.",
		"Autosave SRAM.\nThis option will save SRAM after each modification by the game.\nThis can cause big slowdowns in some games."
};
	
