#pragma once
// commands

#define WAKE_CMD_NOPE ((uint8_t)0x00)
#define WAKE_CMD_SET ((uint8_t)0x01)
#define WAKE_CMD_GET ((uint8_t)0x02)
#define WAKE_CMD_GET_STATUS ((uint8_t)0x03)
#define WAKE_CMD_RESET ((uint8_t)0x04)
#define WAKE_CMD_GET_VERSION ((uint8_t)0x05)
#define WAKE_CMD_GET_ID ((uint8_t)0x06)
#define WAKE_CMD_SET_SETTINGS ((uint8_t)0x07)
#define WAKE_CMD_GET_SETTINGS ((uint8_t)0x08)

static const char* const str_WAKE_CMD_list[] = { "Nope", "Set", "Get", "Get status", "Reset", "Get version", "Get ID", "Set settings", "Get settings" };


// answer
#define WAKE_ANSW_SUCCESS ((uint8_t)0x00)
#define WAKE_ANSW_INVALID_PARAMETER ((uint8_t)0xE1)
#define WAKE_ANSW_ERROR_CODE ((uint8_t)0xE2)

static const char* const str_WAKE_ANSW_list[] = { "Success", "Invalid parameter", "Error code" };

// devices
//платы
#define WAKE_DEV_ALL ((uint8_t)0x00)
#define WAKE_DEV_PKK ((uint8_t)0x01)
#define WAKE_DEV_IM ((uint8_t)0x02)
#define WAKE_DEV_PKS ((uint8_t)0x03)

#define WAKE_DEV_MB ((uint8_t)0x04)
#define WAKE_DEV_SB1 ((uint8_t)0x05)
#define WAKE_DEV_SB2 ((uint8_t)0x06)
#define WAKE_DEV_RIFLE ((uint8_t)0x07)
#define WAKE_DEV_MAPLE ((uint8_t)0x08)
#define WAKE_SOFT_STAND_RIFLE ((uint8_t)0x09)
#define WAKE_DEV_ROTATOR ((uint8_t)0x0A)
#define WAKE_DEV_IFACEBOARD ((uint8_t)0x0B)

static const char* const str_WAKE_dev_list[] = { "All", "PKK", "IM", "PKS", "MB", "SB1", "SB2", "Rifle", "Maple",
                                                 "Rotator", "Interface board", "Rifle 2"
                                               };

// subdevices
#define WAKE_SUBDEV_ALL ((uint8_t)0x00)

// for  PKK
#define WAKE_DEV_PKK_GPIB ((uint8_t)0x01)
#define WAKE_DEV_PKK_SW1 ((uint8_t)0x02)
#define WAKE_DEV_PKK_SW2 ((uint8_t)0x03)
#define WAKE_DEV_PKK_SW3 ((uint8_t)0x04)
#define WAKE_DEV_PKK_SW4 ((uint8_t)0x05)
#define WAKE_DEV_PKK_ATT1 ((uint8_t)0x06)
#define WAKE_DEV_PKK_ATT2 ((uint8_t)0x07)
#define WAKE_DEV_PKK_ATT3 ((uint8_t)0x08)
#define WAKE_DEV_PKK_ATT4 ((uint8_t)0x09)

static const char* const str_WAKE_SubDev_PKK_list[] = { "All", "GPIB", "SW1", "SW2", "SW3", "SW4", "ATT1", "ATT2",
                                                        "ATT3", "ATT4"
                                                      };

// for IM
#define WAKE_DEV_IM_PD ((uint8_t)0x01)
#define WAKE_DEV_IM_P ((uint8_t)0x02)
#define WAKE_DEV_IM_ATT ((uint8_t)0x03)

static const char* const str_WAKE_SubDev_IM_list[] = { "All", "PD", "P", "ATT" };

// for PKS
// ...
static const char* const str_WAKE_SubDev_PKS_list[] = { "All", "SBR_1_O", "SBR_2_O", "TAKT_2_O", "TAKT_1_O", "K1_0",
                                                        "K2_0", "UPR1_0", "UPR2_O", "Vykl_1_O", "Vykl_2_O", "SCK2_MP", "SDI2_MP", "VKL_VYH_B", "VKL_VYH_V", "VKL_Kontr_B",
                                                        "VKL_Kontr_V", "SCK2", "SDI2", "PRM_1", "PRM_2", "PRM_3", "PRM_4", "PRM_5", "PRM_6", "PRM_7", "PRM_8", "VKL_PPS_B",
                                                        "VKL_ZPS_B", "VKL_PPS_Bk", "VKL_ZPS_Bk", "VKL_PPS_V", "VKL_ZPS_V", "VKL_PPS_Vk", "VKL_ZPS_Vk", "AEHR_VYH_B",
                                                        "AEHR_VYH_V", "PRD_1", "PRD_2", "PRD_3", "PRD_4", "PRD_5", "PRD_6", "PRD_7", "PRD_8", "Goden_139_1", "SAP_Avton_1",
                                                        "Goden_139_2", "SAP_Avton_2", "RK_27_VYH3", "RK_27_VYH4", "Goden_139_3", "M1_Kontrol", "M1_Strob", "RK5_VYH3",
                                                        "RK5_VYH4", "Strob_1", "Strob_2", "DG_8B", "DG_8V", "LDG1", "LDG2", "LDG3", "LDG4", "LDG5", "LDG6", "LDG7", "LDG8",
                                                        "SHassi_1", "BR_1", "Kontrol_1", "SHassi_2", "BR_2", "RK_27_VH3", "Kontrol_2", "PPS", "ZPS", "Vysota", "RK_27_VH8",
                                                        "M1_Ispravnost", "RK5_VH2", "Blank_1", "Blank_2"

                                                      };

enum WAKE_SINGLE_COMMAND_GET_PIN {
    SBR_1_O = 1,
    SBR_2_O = 2,
    TAKT_2_O = 3,
    TAKT_1_O = 4,
    K1_0 = 5,
    K2_0 = 6,
    UPR1_0 = 7,
    UPR2_O = 8,
    Vykl_1_O = 9,
    Vykl_2_O = 10,
    SCK2_MP = 11,
    SDI2_MP = 12,
    VKL_VYH_B = 13,
    VKL_VYH_V = 14,
    VKL_Kontr_B = 15,
    VKL_Kontr_V = 16,
    SCK2 = 17,
    SDI2 = 18,
    PRM_1 = 19,
    PRM_2 = 20,
    PRM_3 = 21,
    PRM_4 = 22,
    PRM_5 = 23,
    PRM_6 = 24,
    PRM_7 = 25,
    PRM_8 = 26,
    VKL_PPS_B = 27,
    VKL_ZPS_B = 28,
    VKL_PPS_Bk = 29,
    VKL_ZPS_Bk = 30,
    VKL_PPS_V = 31,
    VKL_ZPS_V = 32,
    VKL_PPS_Vk = 33,
    VKL_ZPS_Vk = 34,
    AEHR_VYH_B = 35,
    AEHR_VYH_V = 36,
    PRD_1 = 37,
    PRD_2 = 38,
    PRD_3 = 39,
    PRD_4 = 40,
    PRD_5 = 41,
    PRD_6 = 42,
    PRD_7 = 43,
    PRD_8 = 44,
    Goden_139_1 = 45,
    SAP_Avton_1 = 46,
    Goden_139_2 = 47,
    SAP_Avton_2 = 48,
    RK_27_VYH3 = 49,
    RK_27_VYH4 = 50,
    Goden_139_3 = 51,
    M1_Kontrol = 52,
    M1_Strob = 53,
    RK5_VYH3 = 54,
    RK5_VYH4 = 55,
    Strob_1 = 56,
    Strob_2 = 57
};

enum WAKE_SINGLE_COMMAND_SET_PIN {
    DG_8B = 100,
    DG_8V = 101,
    LDG1 = 102,
    LDG2 = 103,
    LDG3 = 104,
    LDG4 = 105,
    LDG5 = 106,
    LDG6 = 107,
    LDG7 = 108,
    LDG8 = 109,
    SHassi_1 = 110,
    BR_1 = 111,
    Kontrol_1 = 112,
    SHassi_2 = 113,
    BR_2 = 114,
    RK_27_VH3 = 115,
    Kontrol_2 = 116,
    PPS = 117,
    ZPS = 118,
    Vysota = 119,
    RK_27_VH8 = 120,
    M1_Ispravnost = 121,
    RK5_VH2 = 122,
    Blank_1 = 123,
    Blank_2 = 124
};

// for MB
#define WAKE_DEV_MB_CURRENT ((uint8_t)0x01)
#define WAKE_DEV_MB_POLARITY ((uint8_t)0x02)

static const char* const str_WAKE_SubDev_MB_list[] = { "All", "Current", "Polarity" };

// for SB1
#define WAKE_DEV_SB1_S   ((uint8_t)0x01)
#define WAKE_DEV_SB1_ATT ((uint8_t)0x02)
#define WAKE_DEV_SB1_SW1 ((uint8_t)0x03)
#define WAKE_DEV_SB1_SW2 ((uint8_t)0x04)

static const char* const str_WAKE_SubDev_SB1_list[] = { "All", "Synthesizer", "ATT", "SW1", "SW2" };

// for SB2
#define WAKE_DEV_SB2_SYNTH  ((uint8_t)0x01)
#define WAKE_DEV_SB2_ATT    ((uint8_t)0x02)
#define WAKE_DEV_SB2_SW     ((uint8_t)0x03)
#define WAKE_DEV_SB2_EEPROM ((uint8_t)0x04)

static const char* const str_WAKE_SubDev_SB2_list[] = { "All", "Synthesizer", "Switches", "Att", "EEPROM" };

// for rifle
#define WAKE_DEV_RIFLE_SW1        ((uint8_t)0x01)
#define WAKE_DEV_RIFLE_SW2        ((uint8_t)0x02)
#define WAKE_DEV_RIFLE_SW3        ((uint8_t)0x03)
#define WAKE_DEV_RIFLE_SW4        ((uint8_t)0x04)
#define WAKE_DEV_RIFLE_SW5        ((uint8_t)0x05)
#define WAKE_DEV_RIFLE_LED1       ((uint8_t)0x06)
#define WAKE_DEV_RIFLE_LED2       ((uint8_t)0x07)
#define WAKE_DEV_RIFLE_LED3       ((uint8_t)0x08)
#define WAKE_DEV_RIFLE_LED4       ((uint8_t)0x09)
#define WAKE_DEV_RIFLE_LED5       ((uint8_t)0x0A)
#define WAKE_DEV_RIFLE_ADC        ((uint8_t)0x0B)
#define WAKE_DEV_RIFLE_EEPROM     ((uint8_t)0x0C)
#define WAKE_DEV_RIFLE_SW        ((uint8_t)0x0D)
#define WAKE_DEV_RIFLE_BAT_LED   ((uint8_t)0x0E)
#define WAKE_DEV_RIFLE_RF_LED    ((uint8_t)0x0F)
#define WAKE_DEV_RIFLE_SPI       ((uint8_t)0x10)

// for rifle


static const char* const str_WAKE_SubDev_Rifle2_list[] = { "All"};



static const char* const str_WAKE_SubDev_Rifle_list[] = { "All", "SW1", "SW2", "SW3", "SW4", "SW5", "LED1", "LED2",
                                                          "LED3", "LED4", "LED5", "ADC", "EEPROM", "SW","LED_BAT","LED_RF", "SPI" 
                                                        };

// for maple
#define WAKE_DEV_MAPLE_PRD         ((uint8_t)0x01)
#define WAKE_DEV_MAPLE_PRM         ((uint8_t)0x02)
#define WAKE_DEV_MAPLE_KUVSK       ((uint8_t)0x03)
#define WAKE_DEV_MAPLE_MAK         ((uint8_t)0x04)
#define WAKE_DEV_MAPLE_MAK_ATT     ((uint8_t)0x05)
#define WAKE_DEV_MAPLE_PRCH_N      ((uint8_t)0x06)
#define WAKE_DEV_MAPLE_PRCH_V      ((uint8_t)0x07)
#define WAKE_DEV_MAPLE_PRCH_N_ATT  ((uint8_t)0x08)
#define WAKE_DEV_MAPLE_PRCH_V_ATT  ((uint8_t)0x09)
#define WAKE_DEV_MAPLE_POWER       ((uint8_t)0x0A)
#define WAKE_DEV_MAPLE_DSP         ((uint8_t)0x0B)
#define WAKE_DEV_MAPLE_SYNTH       ((uint8_t)0x0C)


static const char* const str_WAKE_SubDev_Maple_list[] = {  "All",
                                                           "PRD",
                                                           "PRM",
                                                           "KUVSK",
                                                           "MAK",
                                                           "MAK_ATT",
                                                           "PRCH_N",
                                                           "PRCH_V",
                                                           "PRCH_N_ATT",
                                                           "PRCH_V_ATT",
                                                           "POWER",
                                                           "DSP",
                                                           "SYNTH"
                                                        };

#define WAKE_SOFT_STAND_RIFLE ((uint8_t)0x09)

// for maple
#define WAKE_SOFT_STAND_RIFLE_MICROWAVE ((uint8_t)0x01)
#define WAKE_SOFT_STAND_RIFLE_ROTATOR ((uint8_t)0x02)

static const char* const str_WAKE_SubDev_Stand_Rifle_list[] = { "All", "Microwave", "Rotator" };


// for rotator
#define WAKE_DEV_ROTATOR_SPEED         ((uint8_t)0x01)
#define WAKE_DEV_ROTATOR_DIR           ((uint8_t)0x02)
#define WAKE_DEV_ROTATOR_STEP          ((uint8_t)0x03)
#define WAKE_DEV_ROTATOR_INITIAL_SPEED ((uint8_t)0x04)
#define WAKE_DEV_ROTATOR_CHANNEL       ((uint8_t)0x05)

#define WAKE_DEV_ROTATOR_GEAR          ((uint8_t)0x06)
#define WAKE_DEV_ROTATOR_ANGLE         ((uint8_t)0x07)
#define WAKE_DEV_ROTATOR_POLARITY      ((uint8_t)0x08)

static const char* const str_WAKE_SubDev_Rotator_list[] = { "All", "Speed", "Direction", "Step", "Start speed", "Channel", "Gear", "Angle", "Polarity"};



// for interface board
#define WAKE_DEV_IFACEBOARD_TWI        ((uint8_t)0x01)
#define WAKE_DEV_IFACEBOARD_SPI        ((uint8_t)0x02)
#define WAKE_DEV_IFACEBOARD_CAN        ((uint8_t)0x03)
#define WAKE_DEV_IFACEBOARD_UART       ((uint8_t)0x04)
#define WAKE_DEV_IFACEBOARD_LED        ((uint8_t)0x05)

static const char* const str_WAKE_SubDev_IfaceBoard_list[] = { "All", "TWI", "SPI", "CAN", "UART", "LED"};

