#include <stdlib.h>
#include <stdint.h>
#include "st7789.h"
#include <ASTIdef.h>
#include "fonts.h"
#include "icon.h"
// *** Define Name of Color
//#define BLACK   0x0000
//#define WHITE   0xFFFF
//#define RED     0xF800
//#define GREEN   0x07E0
//#define BLUE    0x001F
//#define CYAN    0x07FF
//#define MAGENTA 0xF81F
//#define YELLOW  0xFFE0
//#define GREY    0x2108

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

#define U1_ITEM_COLOR_CLEAR           ((uint8_t)0)      // 0 (表示中の画??値 OFF)
#define U1_ITEM_COLOR_SET             ((uint8_t)1)      // 1 (表示中の画??値 ON)

#define U1_INDEX_TEXT_TOTAL_NUM           (U1)29
#define U1_INDEX_BOX_TOTAL_NUM            (U1)15
#define U1_INDEX_ICON_TOTAL_NUM           (U1)6

#define U1_INDEX_TEXT_SHIP_RPM_LABEL                0
#define U1_INDEX_TEXT_SHIP_RPM_VALUE                1
#define U1_INDEX_TEXT_SHIP_OPERHOUR_LABEL           2
#define U1_INDEX_TEXT_SHIP_OPERHOUR_VALUE           3
#define U1_INDEX_TEXT_SHIP_PRESSURE_LABEL           4
#define U1_INDEX_TEXT_SHIP_PRESSURE_VALUE           5
#define U1_INDEX_TEXT_SHIP_TEMPERATURE_LABEL        6
#define U1_INDEX_TEXT_SHIP_TEMPERATURE_VALUE        7
#define U1_INDEX_TEXT_SHIP_BATTERY_LABEL            8
#define U1_INDEX_TEXT_SHIP_BATTERY_VALUE            9
#define U1_INDEX_TEXT_ENV_FEEL_LABEL                10
#define U1_INDEX_TEXT_ENV_FEEL_VALUE                11
#define U1_INDEX_TEXT_ENV_HUMIDITY_LABEL            12
#define U1_INDEX_TEXT_ENV_HUMIDITY_VALUE            13
#define U1_INDEX_TEXT_ENV_WIND_LABEL                14
#define U1_INDEX_TEXT_ENV_WIND_VALUE                15
#define U1_INDEX_TEXT_ENV_VISIBILITY_LABEL          16
#define U1_INDEX_TEXT_ENV_VISIBILITY_VALUE          17
#define U1_INDEX_TEXT_ENV_PRESSURE_LABEL            18
#define U1_INDEX_TEXT_ENV_PRESSURE_VALUE            19
#define U1_INDEX_TEXT_ENV_UVINDEX_LABEL             20
#define U1_INDEX_TEXT_ENV_UVINDEX_VALUE             21
#define U1_INDEX_TEXT_ENV_LOCATION_VALUE            22
#define U1_INDEX_TEXT_ENV_TIME_LABEL                23
#define U1_INDEX_TEXT_ENV_TIME_PERIOD               24
#define U1_INDEX_TEXT_ENV_TIME_HOUR                 25
#define U1_INDEX_TEXT_ENV_TIME_MINUTE               26
#define U1_INDEX_TEXT_ENV_TEMPERATURE_LABEL         27
#define U1_INDEX_TEXT_ENV_TEMPERATURE_VALUE         28
#define U1_INDEX_TEXT_SIM_CONNECTING_LABEL          29
#define U1_INDEX_TEXT_SIM_CONNECTING_VALUE          30
#define U1_INDEX_TEXT_SIM_CONNECT_FAILED_LABEL      31
#define U1_INDEX_TEXT_SIM_CANT_CONNECT              32
#define U1_INDEX_TEXT_SIM_NO_INTERNET               33

#define U1_INDEX_ICON_SHIP_PRESSURE_VALUE            0
#define U1_INDEX_ICON_SHIP_TEMPERATURE_VALUE         1
#define U1_INDEX_ICON_SHIP_BATTERY_VALUE             2

#define U1_SHIP_RPM_DIGITS                            ((U1)4)
#define U1_SHIP_OPERHOUR_DIGITS                       ((U1)7)
#define U1_SHIP_PRESSURE_DIGITS                       ((U1)4)
#define U1_SHIP_TEMPERATURE_DIGITS                    ((U1)3)
#define U1_SHIP_BATTERY_DIGITS                        ((U1)4)
#define U1_ENV_FEEL_DIGITS                            ((U1)3)
#define U1_ENV_HUMIDITY_DIGITS                        ((U1)3)
#define U1_ENV_WIND_DIGITS                            ((U1)3)
#define U1_ENV_VISIBILITY_DIGITS                      ((U1)3)
#define U1_ENV_PRESSURE_DIGITS                        ((U1)3)
#define U1_ENV_UVINDEX_DIGITS                         ((U1)4)
#define U1_ENV_TEMPERATURE_DIGITS                     ((U1)2)
#define U1_ENV_HOUR_DIGITS                            ((U1)2)
#define U1_ENV_MINUTE_DIGITS                          ((U1)2)
#define U1_ENV_PERIOD_DIGITS                          ((U1)2)

U1 au1_ShipRPM          			[U1_SHIP_RPM_DIGITS+1];
U1 au1_ShipOperHour     			[U1_SHIP_OPERHOUR_DIGITS+1];
U1 au1_ShipPressure    				[U1_SHIP_PRESSURE_DIGITS+1];
U1 au1_ShipTemperature  			[U1_SHIP_TEMPERATURE_DIGITS+1];
U1 au1_ShipBattery      			[U1_SHIP_BATTERY_DIGITS+1];
U1 au1_EnvFeel          			[U1_ENV_FEEL_DIGITS+1];
U1 au1_EnvHumidity      			[U1_ENV_HUMIDITY_DIGITS+1];
U1 au1_EnvWind          			[U1_ENV_WIND_DIGITS+1];
U1 au1_EnvVisibility    			[U1_ENV_VISIBILITY_DIGITS+1];
U1 au1_EnvPressure      			[U1_ENV_PRESSURE_DIGITS+1];
U1 au1_EnvUVIndex       			[U1_ENV_UVINDEX_DIGITS+1];
U1 au1_EnvTemperature   			[U1_ENV_TEMPERATURE_DIGITS+1];
U1 au1_EnvHour          			[U1_ENV_HOUR_DIGITS+1];
U1 au1_EnvMinute        			[U1_ENV_MINUTE_DIGITS+1];
U1 au1_EnvPeriod        			[U1_ENV_PERIOD_DIGITS+1];

typedef float F4;

typedef struct
{
  uint16_t            int_X;          // 描画開始X座??
  uint16_t            int_Y;          // 描画開始Y座??
  uint16_t            int_W;          // width
  uint16_t            int_H;          // Height
  uint16_t             u1_Color;       // 描画色
} ST_LCD_BOX_INFO;

typedef struct {
  ST_LCD_BOX_INFO     st_Box;
  uint16_t            int_X;          // 描画開始X座??
  uint16_t            int_Y;          // 描画開始Y座??
  uint16_t             u1_Color;       // 描画色
  const char*         pc_TextDefault;     // Text Default
  FontDef*            pc_Font;       // size
} ST_LCD_TEXT_INFO;

typedef struct {
  ST_LCD_BOX_INFO     st_Box;
  uint16_t            int_X;          // 描画開始X座??
  uint16_t            int_Y;          // 描画開始Y座??
  uint16_t*     pcs_icon;       // font
} ST_LCD_ICON_INFO;

const ST_LCD_ICON_INFO cst_Icon [] =
{
  {
    .st_Box=
    {
      .int_X = 165,
      .int_Y = 200,
      .int_W = 24,
      .int_H = 30,
      .u1_Color = BLACK,
    },
    .int_X = 165,
    .int_Y = 200,
    .pcs_icon = (uint16_t*) iconPressure,
  },
  {
    .st_Box=
    {
      .int_X = 230,
      .int_Y = 205,
      .int_W = 22,
      .int_H = 22,
      .u1_Color = BLACK,
    },
    .int_X = 230,
    .int_Y = 205,
    .pcs_icon = (uint16_t*) iconTemperature,
  },
  {
    .st_Box=
    {
      .int_X = 296,
      .int_Y = 210,
      .int_W = 24,
      .int_H = 17,
      .u1_Color = BLACK,
    },
    .int_X = 296,
    .int_Y = 210,
    .pcs_icon = (uint16_t*) iconBattery,
  },
  {
    .st_Box=
	{
      .int_X = 0,
      .int_Y = 122,
      .int_W = 18,
      .int_H = 17,
      .u1_Color = BLACK,
    },
	.int_X = 0,
	.int_Y = 122,
	.pcs_icon = (uint16_t*) iconShip,
  },
  {
    .st_Box=
  	{
      .int_X = 0,
      .int_Y = 222,
      .int_W = 8,
      .int_H = 14,
      .u1_Color = BLACK,
    },
  	.int_X = 0,
  	.int_Y = 222,
  	.pcs_icon = (uint16_t*) iconTimelife,
  },
  {
    .st_Box=
    {
    .int_X = 20,
    .int_Y = 140,
    .int_W =114,
    .int_H = 61,
    .u1_Color = BLACK,
    },
    .int_X = 20,
    .int_Y = 140,
    .pcs_icon = (uint16_t*) rpmLevel0,
  }
};

const ST_LCD_BOX_INFO cst_Box [] =
{
  {//Value Pressure
    .int_X = 145,
    .int_Y = 145,
    .int_W = 15,
    .int_H = 80,
    .u1_Color = BLACK,
  },
  {//Value Pressure
    .int_X = 210,
    .int_Y = 145,
    .int_W = 15,
    .int_H = 80,
    .u1_Color = BLACK,
  },
  {//Value Pressure
    .int_X = 275,
    .int_Y = 145,
    .int_W = 15,
    .int_H = 80,
    .u1_Color = BLACK,
  },
};

const ST_LCD_TEXT_INFO cst_Text [] =
{
  {//Label RPM
    .st_Box =
      {
        .int_X      = 80,
        .int_Y      = 202,
        .int_W      = 11 * 3,
        .int_H      = 18,
        .u1_Color   = YELLOW
      },
    .int_X          = 80,
    .int_Y          = 202,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "RPM"                 //0 RPM Label
  },
  {//Value RPM
    .st_Box =
      {
        .int_X      = 0+11*3,
        .int_Y      = 202,
        .int_W      = 11 * 8,
        .int_H      = 18,
        .u1_Color   = BLACK
      },
    .int_X          = 0+11*3,
    .int_Y          = 202,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "   0"                //1 RPM Value
  },
  {//Label Operating Hour
    .st_Box =
      {
        .int_X      = 80,
        .int_Y      = 221,
        .int_W      = 11*4,
        .int_H      = 18,
        .u1_Color   = YELLOW
      },
    .int_X          = 80,
    .int_Y          = 221,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Hour"                //2 Hour Label
  },
  {//Value Operating Hour
    .st_Box =
      {
        .int_X      = 0,
        .int_Y      = 221,
        .int_W      = 11*7,
        .int_H      = 18,
        .u1_Color   = BLACK
      },
    .int_X          = 0,
    .int_Y          = 221,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "      0"                //3 Hour Value
  },
  {//Label Pressure
    .st_Box =
      {
        .int_X      = 170,
        .int_Y      = 125,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = 170,
    .int_Y          = 125,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Bar"                 //4 Pressure Label
  },
  {//Value Pressure
    .st_Box =
      {
        .int_X      = 150,
        .int_Y      = 230,
        .int_W      = 7*5,
        .int_H      = 10,
        .u1_Color   = BLACK
      },
    .int_X          = 150,
    .int_Y          = 230,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "   0"                //5 Pressure Value
  },
  {//Name Temperature
    .st_Box =
      {
        .int_X      = 220,
        .int_Y      = 125,
        .int_W      = 7*2,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = 220,
    .int_Y          = 125,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "'C"                  //6 Temperature Label
  },
  {//Value Temperature
    .st_Box =
      {
        .int_X      = 240,
        .int_Y      = 230,
        .int_W      = 7*4,
        .int_H      = 10,
        .u1_Color   = BLACK
      },
    .int_X          = 240,
    .int_Y          = 230,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "  0 "                //7 Temperature Value
  },
  {//Name Voltage
    .st_Box =
      {
        .int_X      = 290,
        .int_Y      = 125,
        .int_W      = 7*1,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = 290,
    .int_Y          = 125,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "V"                   //8 Battery Label
  },
  {//Value Voltage
    .st_Box =
      {
        .int_X      = 265,
        .int_Y      = 230,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = BLACK
      },
    .int_X          = 265,
    .int_Y          = 230,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "   0"                //9 Battery Value
  },
  {//Name Feel
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*19,
        .int_Y      = 12*0,
        .int_W      = 7*19,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = ST7789_WIDTH-7*19,
    .int_Y          = 12*0,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Feels like:    'C"    //10 Feel Label
  },
  {//Value Feel
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*8-1,
        .int_Y      = 12*0,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = RED
      },
    .int_X          = ST7789_WIDTH-7*8-1,
    .int_Y          = 12*0,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                  //11 Feel value
  },
  {//Name Humidity
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*19-1,
        .int_Y      = 12*1,
        .int_W      = 7*19,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = ST7789_WIDTH-7*19-1,
    .int_Y          = 12*1,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Humidity  :    %"     //12 Humidity Label
  },
  {//Value Humidity
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*8-1,
        .int_Y      = 12*1,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = RED
      },
    .int_X          = ST7789_WIDTH-7*8-1,
    .int_Y          = 12*1,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                //13 Humidity value
  },
  {//Name Wind
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*19-1,
        .int_Y      = 12*2,
        .int_W      = 7*19,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = ST7789_WIDTH-7*19-1,
    .int_Y          = 12*2,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Wind      :    km/h"     //14 Wind Label
  },
  {//Value Wind
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*8-1,
        .int_Y      = 12*2,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = RED
      },
    .int_X          = ST7789_WIDTH-7*8-1,
    .int_Y          = 12*2,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                //15 Wind value
  },
  {//Name Visibility
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*19-1,
        .int_Y      = 12*3,
        .int_W      = 7*19,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = ST7789_WIDTH-7*19-1,
    .int_Y          = 12*3,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Visibility:    km"     //16 Visibility Label
  },
  {//Value Visibility
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*8-1,
        .int_Y      = 12*3,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = RED
      },
    .int_X          = ST7789_WIDTH-7*8-1,
    .int_Y          = 12*3,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                //17 Visibility value
  },
  {//Name Pressure
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*19-1,
        .int_Y      = 12*4,
        .int_W      = 7*19,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = ST7789_WIDTH-7*19-1,
    .int_Y          = 12*4,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Pressure  :    hPa"     //18 Pressure Label
  },
  {//Value Pressure
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*8-1,
        .int_Y      = 12*4,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = RED
      },
    .int_X          = ST7789_WIDTH-7*8-1,
    .int_Y          = 12*4,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                //19 Pressure Value
  },
  {//Name UVIndex
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*19-1,
        .int_Y      = 12*5,
        .int_W      = 7*19,
        .int_H      = 10,
        .u1_Color   = YELLOW
      },
    .int_X          = ST7789_WIDTH-7*19-1,
    .int_Y          = 12*5,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "UV Index  :    hPa"     //20 UVIndex Label
  },
  {//Value UVIndex
    .st_Box =
      {
        .int_X      = ST7789_WIDTH-7*8-1,
        .int_Y      = 12*5,
        .int_W      = 7*3,
        .int_H      = 10,
        .u1_Color   = RED
      },
    .int_X          = ST7789_WIDTH-7*8-1,
    .int_Y          = 12*5,
    .pc_Font        = &Font_7x10,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                //21 UVIndex Value
  },
  {//Value Location
    .st_Box =
      {
        .int_X      = 5,
        .int_Y      = 0,
        .int_W      = 11*10,
        .int_H      = 18,
        .u1_Color   = RED
      },
    .int_X          = 5,
    .int_Y          = 0,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Nowhere"             //22 Location
  },
  {//Name Time
    .st_Box =
      {
        .int_X      = 42,
        .int_Y      = 20,
        .int_W      = 11*7,
        .int_H      = 18,
        .u1_Color   = YELLOW
      },
    .int_X          = 42,
    .int_Y          = 20,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "  :     "            //23 Time Label
  },
  {//Value Period
    .st_Box =
      {
        .int_X      = 42+11*5,
        .int_Y      = 20,
        .int_W      = 11*2,
        .int_H      = 18,
        .u1_Color   = RED
      },
    .int_X          = 42+11*5,
    .int_Y          = 20,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "AM"                  //24 Period Value
  },
  {//Value Hour
    .st_Box =
      {
        .int_X      = 42,
        .int_Y      = 20,
        .int_W      = 11*2,
        .int_H      = 18,
        .u1_Color   = RED
      },
    .int_X          = 42,
    .int_Y          = 20,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                  //25 Hour Value
  },
  {//Value Minute
    .st_Box =
      {
        .int_X      = 42+11*3,
        .int_Y      = 20,
        .int_W      = 11*2,
        .int_H      = 18,
        .u1_Color   = RED
      },
    .int_X          = 42+11*3,
    .int_Y          = 20,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                  //26 Minute Value
  },
  {//Value Temperature
    .st_Box =
      {
        .int_X      = 158,
        .int_Y      = 60,
        .int_W      = 11*2,
        .int_H      = 18,
        .u1_Color   = YELLOW
      },
    .int_X          = 158,
    .int_Y          = 60,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "'C"                  //27 Temperature Label
  },
  {//Name Temperature
    .st_Box =
      {
        .int_X      = 123,
        .int_Y      = 60,
        .int_W      = 16*2,
        .int_H      = 26,
        .u1_Color   = RED
      },
    .int_X          = 123,
    .int_Y          = 60,
    .pc_Font        = &Font_16x26,
    .u1_Color       = WHITE,
    .pc_TextDefault = "99"                  //28 Temperature Value
  },
  {//Name Connecting
    .st_Box =
      {
        .int_X      = 42,
        .int_Y      = 0,
        .int_W      = 48,
        .int_H      = 17,
        .u1_Color   = BLACK
      },
    .int_X          = 42,
    .int_Y          = 17,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "% Connecting"        //29 Connecting Label
  },
  {//Value Connecting
    .st_Box =
      {
        .int_X      = 42,
        .int_Y      = 0,
        .int_W      = 48,
        .int_H      = 17,
        .u1_Color   = BLACK
      },
    .int_X          = 42,
    .int_Y          = 17,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "00"                  //30 Connecting Value
  },
  {//Value Connect failed
    .st_Box =
      {
        .int_X      = 42,
        .int_Y      = 0,
        .int_W      = 48,
        .int_H      = 17,
        .u1_Color   = BLACK
      },
    .int_X          = 42,
    .int_Y          = 17,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Connection to server failed"                  //31 Connect failed Label
  },
  {//Value Cant connect to SIM!
    .st_Box =
      {
        .int_X      = 42,
        .int_Y      = 0,
        .int_W      = 48,
        .int_H      = 17,
        .u1_Color   = BLACK
      },
    .int_X          = 42,
    .int_Y          = 17,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "Can't connect to SIM!"                  //32 Cant connect to SIM! Label
  },
  {//Value Connect failed
    .st_Box =
      {
        .int_X      = 42,
        .int_Y      = 0,
        .int_W      = 48,
        .int_H      = 17,
        .u1_Color   = BLACK
      },
    .int_X          = 42,
    .int_Y          = 17,
    .pc_Font        = &Font_11x18,
    .u1_Color       = WHITE,
    .pc_TextDefault = "No internet!"                       //33 Connect failed Label
  },
};

void DrawBox(const ST_LCD_BOX_INFO ast_Box)
{
	ST7789_DrawFilledRectangle(ast_Box.int_X, ast_Box.int_Y, ast_Box.int_W, ast_Box.int_H, ast_Box.u1_Color);
}

void DrawText(const ST_LCD_TEXT_INFO ast_Text, const char* apu1_Char)
{
//  const char * apu1_Dest;
//  DrawBox(ast_Text.st_Box);
  if (apu1_Char == NULL)
  {
    // tft.print(ast_Text.pc_TextDefault);
    // ST7789_WriteString(ast_Text.pc_TextDefault, ast_Text.int_X, ast_Text.int_Y, COLOR_BLACK, ast_Text.u1_Color, ast_Text.pcs_size);
    ST7789_WriteString(ast_Text.int_X, ast_Text.int_Y, ast_Text.pc_TextDefault, ast_Text.pc_Font, WHITE, BLACK);
  }
  else
  {
    // ST7789_WriteString(apu1_Char,               ast_Text.int_X, ast_Text.int_Y, COLOR_BLACK, ast_Text.u1_Color, ast_Text.pcs_size);
    ST7789_WriteString(ast_Text.int_X, ast_Text.int_Y, apu1_Char              , ast_Text.pc_Font, WHITE, BLACK);
  }
}

void DrawIcon(const ST_LCD_ICON_INFO ast_Icon)
{
	DrawBox(ast_Icon.st_Box);
	ST7789_DrawImage(ast_Icon.int_X, ast_Icon.int_Y, ast_Icon.st_Box.int_W, ast_Icon.st_Box.int_H, ast_Icon.pcs_icon);
}

U2 au2_Div;
S1 S1_IntToASCII(S4 as4_Int, U1 *apu1_Str, U1 au1_Num, U1 au1_Mode)
{
  S1 as1_Sign;
  U1 au1_Cnt;
  U1 au1_Radix;
  U1 au1_NoSpace = U1FALSE;
  //U2 au2_Div;
  S4 *aps4_Table;
  S4 as4_Table[2][8] = {
    {1L, 10L, 100L, 1000L, 10000L, 100000L, 1000000L,  10000000L }, // Mode = 0 10進
    {1L, 16L, 256L, 4096L, 65536L, 1048576L, 16777216L, 268435456L}, // Mode = 1 16進
  };

  // 基数設??
  au1_Radix = au1_Mode & 0x01;  // Mode = 2の場合???10進数とする

  // 数値→ASCII??字???変換
  if (as4_Int < 0) {
    as4_Int *= (S4) - 1;
    as1_Sign = (S1) - 1;
  } else if ( as4_Int > 0) {
    as1_Sign = (S1)1;
  } else {
    as1_Sign = 0;
  }
  for (au1_Cnt = au1_Num; au1_Cnt > 0; au1_Cnt--, apu1_Str++) {
    aps4_Table = &as4_Table[au1_Radix][au1_Cnt - 1];

    if (as4_Int != 0) {
      au2_Div = (U2)(as4_Int / (S4) * aps4_Table);
      if ( au2_Div < 10 ) {
        *apu1_Str = (U1)(au2_Div + '0');
      } else {
        *apu1_Str = (U1)(au2_Div + 'A' - 10);
      }
      as4_Int %= *aps4_Table;
    } else {
      *apu1_Str = '0';
    }
    // Mode=2 '0'→スペ???ス変換
    if ( au1_Mode == 2 ) {
      if ( ( au1_Cnt > 1 )
           && ( *apu1_Str == '0' )
           && ( au1_NoSpace == U1FALSE ) ) {
        // 10進数で上位桁が'0'の場合???スペ???スへ変換
        *apu1_Str = 0x20;
      } else {
        au1_NoSpace = U1TRUE;
      }
    }
  }

  return as1_Sign;
}

static void DisplayPressure(const U2 au2_Pressure)
{
    U1 au1_ShipPressure[U1_SHIP_PRESSURE_DIGITS+1];
    F4 af4_pressure;
    S4 s4_val;

    af4_pressure = ((F4)au2_Pressure*100)/((F4)100000);

    if(af4_pressure > 10)
    {
        af4_pressure = 10;
    }

    U1 dispPressureBar = af4_pressure * cst_Box[0].int_H / 10.0;
    if(af4_pressure <= 0.7f)
    {
    	ST7789_DrawFilledRectangle(cst_Box[0].int_X, cst_Box[0].int_Y, cst_Box[0].int_W, cst_Box[0].int_H-dispPressureBar, cst_Box[0].u1_Color);
    	ST7789_DrawFilledRectangle(cst_Box[0].int_X, cst_Box[0].int_Y + cst_Box[0].int_H-dispPressureBar, cst_Box[0].int_W, dispPressureBar, RED);
    }
    else
    {
    	ST7789_DrawFilledRectangle(cst_Box[0].int_X, cst_Box[0].int_Y, cst_Box[0].int_W, cst_Box[0].int_H-dispPressureBar, cst_Box[0].u1_Color);
    	ST7789_DrawFilledRectangle(cst_Box[0].int_X, cst_Box[0].int_Y + cst_Box[0].int_H-dispPressureBar, cst_Box[0].int_W, dispPressureBar, GREEN);
    }
    // 少数点第一位まで表示
    s4_val = af4_pressure * 100;

    // 数値をASCII文字に変換
    (void)S1_IntToASCII(s4_val, au1_ShipPressure,U1_SHIP_PRESSURE_DIGITS,2);
    // |1|0|0|0|/0| => |1|0|.|0|/0|
    // | | |7|0|/0| => | |0|.|7|/0|
    // | | | |0|/0| => | |0|.|0|/0|
    // 0補正
    if(au1_ShipPressure[U1_SHIP_PRESSURE_DIGITS - 3]== ' ')
    {
        au1_ShipPressure[U1_SHIP_PRESSURE_DIGITS - 3]= '0';
    }

    au1_ShipPressure[U1_SHIP_PRESSURE_DIGITS - 1] = au1_ShipPressure[U1_SHIP_PRESSURE_DIGITS - 2];
    au1_ShipPressure[U1_SHIP_PRESSURE_DIGITS - 2] = '.';
    au1_ShipPressure[U1_SHIP_PRESSURE_DIGITS] = '\0';
    // 数値を表示
    DrawText(cst_Text[U1_INDEX_TEXT_SHIP_PRESSURE_VALUE], (char *)au1_ShipPressure);
}
    F4 af4_Temp;
//    U1 au1_ShipTemperature[U1_SHIP_TEMPERATURE_DIGITS+1];

static void DisplayTemperature(const U2 au2_Temp)
{
    S4 s4_val;
    for (U1 au1_ForC = 0; au1_ForC <= U1_SHIP_TEMPERATURE_DIGITS; au1_ForC++)
    {
        au1_ShipTemperature[au1_ForC] = U1MIN;
    }


    af4_Temp = ((F4)au2_Temp/100)-273;

    if(af4_Temp > 120.0f){
        af4_Temp = 120.0f;
    } else if(af4_Temp < 0){
        af4_Temp = 0;
    }

    //++++++++++++++++++++++++++++++++++
    // 少数点第一位は切り捨て
    if(af4_Temp >= 96.0f) {
        //  temperature highを表示
        // DrawText(cst_Text[U1_INDEX_TEXT_TEMP_STATUS], PU1_TEXT_MSG_HIGH);
    }
    else
    {
        // DrawText(cst_Text[U1_INDEX_TEXT_TEMP_STATUS], PU1_TEXT_MSG_DF);
    }

    U1 dispTemperatureBar = af4_Temp * cst_Box[1].int_H / 120.0;

    if(af4_Temp >= 96.0f)
    {
    	ST7789_DrawFilledRectangle(cst_Box[1].int_X, cst_Box[1].int_Y, cst_Box[1].int_W, cst_Box[1].int_H-dispTemperatureBar, cst_Box[1].u1_Color);
    	ST7789_DrawFilledRectangle(cst_Box[1].int_X, cst_Box[1].int_Y + cst_Box[1].int_H-dispTemperatureBar, cst_Box[1].int_W, dispTemperatureBar, RED);
    }
    else
    {
    	ST7789_DrawFilledRectangle(cst_Box[1].int_X, cst_Box[1].int_Y, cst_Box[1].int_W, cst_Box[1].int_H-dispTemperatureBar, cst_Box[1].u1_Color);
    	ST7789_DrawFilledRectangle(cst_Box[1].int_X, cst_Box[1].int_Y + cst_Box[1].int_H-dispTemperatureBar, cst_Box[1].int_W, dispTemperatureBar, GREEN);
    }

    // s4_val = af4_Temp * 10;
    s4_val = af4_Temp;
    // 数値をASCII文字に変換
    (void)S1_IntToASCII(s4_val, au1_ShipTemperature,U1_SHIP_TEMPERATURE_DIGITS,2);
    // if(au1_Temp[U1_OIL_PRESSURE_DIGITS - 3] == ' ')
    // {
    //     au1_Temp[U1_TEMP_DIGITS - 3]='0';
    // }
    // au1_Temp[U1_TEMP_DIGITS - 1] = au1_Temp[U1_TEMP_DIGITS - 2];
    // au1_Temp[U1_TEMP_DIGITS - 2] = '.';
    au1_ShipTemperature[U1_SHIP_TEMPERATURE_DIGITS] = '\0';
    // 数値を表示
    DrawText(cst_Text[U1_INDEX_TEXT_SHIP_TEMPERATURE_VALUE], (char *)au1_ShipTemperature);
}

static void DisplayBattery(const U2 au2_Battery)
{
    U1 au1_ShipBattery[U1_SHIP_BATTERY_DIGITS+1];
    F4 af4_Battery;
    S4 s4_val;
//    const ST_LCDITEMDATA *acpst_ItemData = &cs_LCD_ItemData_Msg[U1_LCD_MSG003];

    af4_Battery = (F4)au2_Battery / (F4)100;
    if((af4_Battery < 8.1f) ||
        (af4_Battery > 300.1f))
    {
        af4_Battery = 0.0;
    }

    U1 dispBatteryBar = af4_Battery * cst_Box[2].int_H / 120.0;
    if(af4_Battery < 11.5f)
    {
        ST7789_DrawFilledRectangle(cst_Box[2].int_X, cst_Box[2].int_Y, cst_Box[2].int_W, cst_Box[2].int_H-dispBatteryBar, cst_Box[2].u1_Color);
    	ST7789_DrawFilledRectangle(cst_Box[2].int_X, cst_Box[2].int_Y + cst_Box[2].int_H-dispBatteryBar, cst_Box[2].int_W, dispBatteryBar, RED);
    }
    else
    {
        ST7789_DrawFilledRectangle(cst_Box[2].int_X, cst_Box[2].int_Y, cst_Box[2].int_W, cst_Box[2].int_H-dispBatteryBar, cst_Box[2].u1_Color);
    	ST7789_DrawFilledRectangle(cst_Box[2].int_X, cst_Box[2].int_Y + cst_Box[2].int_H-dispBatteryBar, cst_Box[2].int_W, dispBatteryBar, GREEN);
    }
    // 少数点第一位まで表示
    s4_val = af4_Battery * 100;
    // 数値をASCII文字に変換
    (void)S1_IntToASCII(s4_val, &au1_ShipBattery[0],U1_SHIP_BATTERY_DIGITS,2);
    // 0補正
    // |1|2|1|0|/0|
    // |1|2|.|1|/0|
    // | | | |0|/0|
    // | |0|.|0|/0|
    if(au1_ShipBattery[U1_SHIP_BATTERY_DIGITS - 3]== ' ')
    {
        au1_ShipBattery[U1_SHIP_BATTERY_DIGITS - 3]= '0';
    }
    au1_ShipBattery[U1_SHIP_BATTERY_DIGITS - 1] = au1_ShipBattery[U1_SHIP_BATTERY_DIGITS - 2];
    au1_ShipBattery[U1_SHIP_BATTERY_DIGITS - 2] = '.';
    au1_ShipBattery[U1_SHIP_BATTERY_DIGITS] = '\0';

    // 数値を表示
    DrawText(cst_Text[U1_INDEX_TEXT_SHIP_BATTERY_VALUE], (char *)au1_ShipBattery);
}


static void DisplayOperatingHour(const U8 au4_OperatingHour)
{
	U1 au1_ShipOperHour[U1_SHIP_OPERHOUR_DIGITS+1];
    F4 af4_OperatingHour;
	S4 s4_val;

    af4_OperatingHour = (F4)au4_OperatingHour/3600;
    if(af4_OperatingHour > 9999.9f)
    {
        af4_OperatingHour = 9999.9f;
    }
    // 少数点第一位まで表示
    s4_val = af4_OperatingHour * 10;

    // 数値をASCII文字に変換
    (void)S1_IntToASCII(s4_val, &au1_ShipOperHour[0],U1_SHIP_OPERHOUR_DIGITS - 1,2);
    // 0補正
    if(au1_ShipOperHour[U1_SHIP_OPERHOUR_DIGITS - 3]== ' ')
    {
        au1_ShipOperHour[U1_SHIP_OPERHOUR_DIGITS - 3]= '0';
    }
    au1_ShipOperHour[U1_SHIP_OPERHOUR_DIGITS - 1] = au1_ShipOperHour[U1_SHIP_OPERHOUR_DIGITS - 2];
    au1_ShipOperHour[U1_SHIP_OPERHOUR_DIGITS - 2] = '.';
    au1_ShipOperHour[U1_SHIP_OPERHOUR_DIGITS] = '\0';
    // 数値を表示
    DrawText(cst_Text[U1_INDEX_TEXT_SHIP_OPERHOUR_VALUE], (char *)au1_ShipOperHour);
}

static void DisplayRPM(const U2 au2_speed)
{
    U1 au1_ShipRPM[U1_SHIP_RPM_DIGITS+1];
    U2 au2_rpm;

    au2_rpm = au2_speed * 0.25;

//    if(au2_rpm > U2_RPM)
//    {
//        au2_rpm = U2_RPM;
//    }

    // 数値をASCII文字に変換
    (void)S1_IntToASCII((S4)au2_rpm, &au1_ShipRPM[0],U1_SHIP_RPM_DIGITS,2);
    au1_ShipRPM[U1_SHIP_RPM_DIGITS] = '\0';
    // 数値を表示
    DrawText(cst_Text[U1_INDEX_TEXT_SHIP_RPM_VALUE], (char *)au1_ShipRPM);

}

static void DisplayUVIndex(const U2 au2_UVIndex)
{
    U1 au1_ShipUVIndex[U1_ENV_UVINDEX_DIGITS+1];

    F4 af4_UVIndex;
    S4 s4_val;
//    const ST_LCDITEMDATA *acpst_ItemData = &cs_LCD_ItemData_Msg[U1_LCD_MSG003];

    af4_UVIndex = (F4)au2_UVIndex / (F4)100;
    if((af4_UVIndex < 8.1f) ||
        (af4_UVIndex > 300.1f))
    {
        af4_UVIndex = 0.0;
    }

    if(af4_UVIndex < 11.5f)
    {
        // Battery lowを表示
        // DrawText(cst_Text[U1_INDEX_TEXT_BATTERY_STATUS], PU1_TEXT_MSG_LOW);
    }
    else
    {
        // DrawText(cst_Text[U1_INDEX_TEXT_BATTERY_STATUS], PU1_TEXT_MSG_DF);
    }
    // 少数点第一位まで表示
    s4_val = af4_UVIndex * 100;
    // 数値をASCII文字に変換
    (void)S1_IntToASCII(s4_val, &au1_ShipUVIndex[0],U1_ENV_UVINDEX_DIGITS,2);
    // 0補正
    // |1|2|1|0|/0|
    // |1|2|.|1|/0|
    // | | | |0|/0|
    // | |0|.|0|/0|
    if(au1_ShipUVIndex[U1_ENV_UVINDEX_DIGITS - 3]== ' ')
    {
        au1_ShipUVIndex[U1_ENV_UVINDEX_DIGITS - 3]= '0';
    }
    au1_ShipUVIndex[U1_ENV_UVINDEX_DIGITS - 1] = au1_ShipUVIndex[U1_ENV_UVINDEX_DIGITS - 2];
    au1_ShipUVIndex[U1_ENV_UVINDEX_DIGITS - 2] = '.';
    au1_ShipUVIndex[U1_ENV_UVINDEX_DIGITS] = '\0';

    // 数値を表示
    DrawText(cst_Text[U1_INDEX_TEXT_ENV_UVINDEX_VALUE], (char *)au1_ShipUVIndex);
}

static void DisplayBackground(void)
{
    U1 au1_ForC;
    #if 1        // DEBUG
    ST7789_DrawFilledRectangle(0, ST7789_HEIGHT/2-3, ST7789_WIDTH, 3, YELLOW);
//    for (au1_ForC = U1MIN; au1_ForC < U1_INDEX_BOX_TOTAL_NUM; au1_ForC++)
//    {
//        DrawBox(cst_Box[au1_ForC]);
//    }
    for (au1_ForC = U1MIN; au1_ForC < U1_INDEX_TEXT_TOTAL_NUM; au1_ForC++)
    {
        DrawText(cst_Text[au1_ForC], NULL);
    }

//    ST7789_DrawImage(165, 200, 24, 30, (uint16_t *)iconPressure);
//    ST7789_DrawImage(230, 205, 22, 22, (uint16_t *)iconTemperature);
//    ST7789_DrawImage(296, 210, 24, 17, (uint16_t *)iconBattery);
     for (au1_ForC = U1MIN; au1_ForC < U1_INDEX_ICON_TOTAL_NUM; au1_ForC++)
     {
         DrawIcon(cst_Icon[au1_ForC]);
     }
    #endif
}

void DisplayTFT(void)
{
    U1 au1_Status;
    au1_Status = U1FALSE;
    // if(PreSpeed != speed)
    {
//        DisplayRPM(speed);
        // PreSpeed = speed;
        au1_Status = U1TRUE;
    }
    // if(PreTotalEnginHours != totalenginehours)
    {

//        DisplayOperatingHour(totalenginehours);
        // PreTotalEnginHours = totalenginehours;
        au1_Status = U1TRUE;
    }
    // if(PreOilpressure != oilpressure)
    {
//        DisplayPressure(oilpressure);
        // PreOilpressure = oilpressure;
        au1_Status = U1TRUE;
    }
    // if(PreTemperture != temperature)
    {
//        DisplayTemp(temperature);
        // PreTemperture=temperature;
        au1_Status = U1TRUE;
    }
    // if(PreAlternatorpotential != alternatorpotential)
    {
//        DisplayBattery(alternatorpotential);
        // PreAlternatorpotential = alternatorpotential;
        au1_Status = U1TRUE;
    }

    if (au1_Status == U1TRUE)
    {
    }
}
