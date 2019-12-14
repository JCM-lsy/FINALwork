/*****************************************
音乐播放头文件部分
**********************************************/
#include "arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

//#define AUDIO_PORT  Serial1    //Core+
#define AUDIO_PORT mySerial  //Core,CoreUSB

byte sn_reset[4] =
{
  0x7E, 0x02, 0x0C, 0xEF
};

byte sn_choose[6] =
{
  0x7E, 0x04, 0x03, 0x00, 0x01, 0xEF
};

byte sn_vol[5] =
{
  0x7E, 0x03, 0x06, 0x18, 0xEF
};

byte sn_device[5] =
{
  0x7E, 0x03, 0x09, 0x01, 0xEF
};

byte sn_pause[4] =
{
  0x7E, 0x02, 0x0E, 0xEF
};

byte sn_play[4] =
{
  0x7E, 0x02, 0x0D, 0xEF
};

byte sn_mode[5] =
{
  0x7E, 0x03, 0x11, 0x00, 0xEF
};

byte sn_down[4] =
{
  0x7E, 0x02, 0x01, 0xEF
};

byte sn_up[4] =
{
  0x7E, 0x02, 0x02, 0xEF
};

byte sn_eq[5] =
{
  0x7E, 0x03, 0x07, 0x01, 0xEF
};

//-----------------------------
void audio_pause()
{
  AUDIO_PORT.write(sn_pause, 4);
  delay(50);
}

void audio_play()
{
  AUDIO_PORT.write(sn_play, 4);
  delay(50);
}

//play eq    (Normal/Pop/Rock/Jazz/Classic/Base)  0-5
void audio_eq(byte _audio_eq)
{
  sn_mode[3] = _audio_eq;
  AUDIO_PORT.write(sn_eq, 5);
  delay(100);
}

#define MODE_loopAll 0
#define MODE_loopOne 1
#define MODE_One_STOP 2
#define MODE_One_END  4
//play mode    (ALL/FOL/ONE/RAM/ONE_STOP)  0-4
void audio_mode(byte _audio_mode)
{
  sn_mode[3] = _audio_mode;
  AUDIO_PORT.write(sn_mode, 5);
  delay(100);
}

#define DEVICE_Flash  5
#define DEVICE_TF  1
//device select    (U/TF/AUX/SLEEP/FLASH)  0-4
void audio_device(byte _audio_device)
{
  sn_device[3] = _audio_device;
  AUDIO_PORT.write(sn_device, 5);
  delay(1500);
}

void audio_down()
{
  AUDIO_PORT.write(sn_down, 4);
  delay(500);
}

void audio_up()
{
  AUDIO_PORT.write(sn_up, 4);
  delay(500);
}

void audio_vol(byte _audio_vol)
{
  sn_vol[3] = _audio_vol;
  AUDIO_PORT.write(sn_vol, 5);
  delay(50);
}

void audio_choose(byte _audio_choose)
{
  sn_choose[4] = _audio_choose;
  AUDIO_PORT.write(sn_choose, 6);
  delay(100);
}

void audio_reset()
{
  AUDIO_PORT.write(sn_reset, 4);
  delay(500);
}

void audio_init(int _audio_init_device, int _audio_init_mode, int _audio_init_vol)
{
  AUDIO_PORT.begin(9600);
  delay(500);
  audio_reset();
  audio_device(_audio_init_device);
  audio_mode(_audio_init_mode);
  audio_vol(_audio_init_vol);
  //audio_choose(1);
  //audio_pause();
}

/*****************************************
音乐播放头文件部分
**********************************************/
//A lot of include............
/**
 * 需要做替换的部分!!!!!!!!!
 *
*/
//传感器*********************************************************
#define SSID        "ABCD" //改为你的热点名称, 不要有中文
#define PASSWORD    "12345678"//改为你的WiFi密码Wi-Fi密码
#define DEVICEID    "561895938" //OneNet上的设备ID
String apiKey = "01He8LGRFa8U5ML6qMvdN3jspn8=";//与你的设备绑定的APIKey

/***/
#define HOST_NAME   "api.heclouds.com"
#define HOST_PORT   (80)
#define INTERVAL_SENSOR   5000             //定义传感器采样时间间隔  597000
#define INTERVAL_NET      5000             //定义发送时间
//传感器部分================================   
#include <Wire.h>                                  //调用库  
#include <ESP8266.h>
#include <I2Cdev.h>                                //调用库  
/*******温湿度*******/
#include <Microduino_SHT2x.h>
/*******光照*******/
#define  sensorPin_1  A0
#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                   // received before closing the connection.  If you know the server
                   // you're accessing is quick to respond, you can reduce this value.
//传感器*********************************************************
//睡眠中断************************************
#include <avr/sleep.h>
#include <avr/power.h>
#include <IRremote.h>
#include <U8glib.h>
//睡眠中断************************************
//彩灯********************************
#include <Microduino_ColorLED.h> //引用彩灯库
#define PIN D8        //彩灯引脚D8
#define Light_PIN A0  //光照传感器接AO引脚
#define NUM 1
#define Light_value1 400
//光强预设值
////彩灯********************************
//音乐******************************************************************
#include <SoftwareSerial.h>
#include <Wire.h>
#include <EEPROM.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
#include <ESP8266.h>
#ifdef ESP32
#error "Error"
#endif
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define EspSerial Serial1
#define UARTSPEED  115200
#endif
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#define EspSerial mySerial
#define UARTSPEED  9600
/**
 * 需要做替换的部分!!!!!!!!!
 *
*/
#endif
#define SSID        F("ABCD")//热点名称
#define PASSWORD    F("12345678")//热点密码
#define HOST_NAME   F("api.heclouds.com")
#define HOST_PORT   (80)
//The pattern of http request text Cost much of my time ?_?
//Yes,Http message...
static const byte  GETDATA[]  PROGMEM = {
  "GET https://api.heclouds.com/devices/576408525/datapoints?datastream_id=id,status,vol&limit=1 HTTP/1.1\r\napi-key: 9OM8o=CfJXkpc0KSwCLlCOsSx90=\r\nHost: api.heclouds.com\r\nConnection: close\r\n\r\n"
};//"57...25"数字部分换成自己的apiID,NAPI-KEY:换成自己的API-KEY
ESP8266 wifi(&EspSerial);
//define two variables...
int rollCount = 0, rollRoomMembers = 0;
//define another three variables...
bool volChange = false, statusChange = false, idChange = false;
int music_status = 0, temp_music_status = 0;
int music_vol = 10, temp_music_vol = 10;
int music_num_MAX = 9;
int current_music = 1, temp_current_music = 1;
char* names[] = { "china ","opera ","romance ","love ","the moon ","you ","home ","red ","motherland " };//更换歌曲名称
//I'm lazy,don't know the method of calc the length of char* 
//int name_length[]={22,27,19,14,21,20,18,29,23};
bool isConnected = false;
bool bottomBar = true;
bool canPlay = false;
//音乐******************************************************************
//传感器*********************************************************

//WEBSITE     
char buf[10];

#define INTERVAL_sensor 2000
unsigned long sensorlastTime = millis();

float tempOLED, humiOLED, lightnessOLED;

#define INTERVAL_OLED 1000

String mCottenData;
String jsonToSend;

//3,传感器值的设置 
float sensor_tem, sensor_hum, sensor_lux;                    //传感器温度、湿度、光照   
char  sensor_tem_c[7], sensor_hum_c[7], sensor_lux_c[7];    //换成char数组传输
#include <SoftwareSerial.h>
#define EspSerial mySerial
#define UARTSPEED  9600
SoftwareSerial mmmmmySerial(2, 3); /* RX:D3, TX:D2 */
//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象
unsigned long net_time1 = millis();                          //数据上传服务器时间
unsigned long sensor_time = millis();                        //传感器采样时间计时器

//int SensorData;                                   //用于存储传感器数据
String postString;                                //用于存储发送数据的字符串
//String jsonToSend;                                //用于存储发送的json格式参数

Tem_Hum_S2 TempMonitor;
//传感器*********************************************************
//彩灯********************************
int sensorValueLIGHT;
ColorLED strip = ColorLED(NUM, PIN);  //第一个参数表示最大级联ColorLED个数，第二个参数表示使用的端口。
//彩灯********************************
//睡眠中断************************************
int RECV_PIN = 10;
long interval = 3600000;           // 闪烁的时间间隔（毫秒）一分钟
IRrecv irrecv(RECV_PIN);
long previousMillis = 0;        // 存储LED最后一次的更新
decode_results results;
unsigned long currentMillis = 0;
int pin2 = 2;//触摸开关接D2
//睡眠中断************************************
/*睡眠中断************************************
 *  函数名:        pin2Interrupt
 *  返回值:     Nothing.
 *  参数值:  None.
 *  释义: 服务pin2中断请求
*睡眠中断************************************/
void pin2Interrupt(void) {
  //睡眠中断************************************ 
    /*当中断引脚为低电平时关闭中断*/
  Serial.println("wake up!!!");
  detachInterrupt(0);
  //睡眠中断************************************
}

/*睡眠中断************************************
 *  Name:        enterSleep
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: 进入睡眠模式.
 ***************************************************/
void enterSleep(void) {
  attachInterrupt(0, pin2Interrupt, LOW);
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);//控制处理器进入睡眠模式
  sleep_enable();
  sleep_mode();
  sleep_disable();
}
//睡眠中断************************************
//音乐******************************************************************
void drawTitle() {
  //Roll The Name of songs~~
  //Point is one thing that unsafe.
  //Array in C++ is not as easy as it is in java...
  u8g.setPrintPos(4, 48);
  /*
    for(int i=0;i<name_length[current_music];i++){
    if(rollCount+i<name_length[current_music]){
      u8g.print(*(names[current_music]+rollCount+i));
    }else{
      u8g.print(*(names[current_music]+rollCount+i-name_length[current_music]));
    }
    }
    */
  for (int i = 0; i < strlen(names[current_music]); i++) {
    if (rollCount + i < strlen(names[current_music])) {
      u8g.print(*(names[current_music] + rollCount + i));
    }
    else
    {
      u8g.print(*(names[current_music] + rollCount + i - strlen(names[current_music])));
    }

  }
  u8g.print("...");
}
//音乐******************************************************************
//音乐******************************************************************
void drawNotConnected() {
  //it will draw like this:? (NO BORDER!!)
  u8g.drawTriangle(64, 4, 32, 48, 96, 48);
  u8g.drawTriangle(64, 60, 32, 16, 96, 16);
}
//音乐******************************************************************

//音乐******************************************************************
bool networkHandle() {
  //do something with net work ,include handle response message.
  canPlay = true;
  uint8_t buffer[415] = { 0 };
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 2000);
  if (len > 0) {
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
  }
  //the ram of the device is too limited,so i enhered the length of response message,at specific index,there are nessicity value.
  //  272，273 vol
  //344 id
  //414 status
  temp_music_vol = ((int)buffer[272] - 48) * 10 + ((int)buffer[273] - 48) - 10;
  temp_current_music = (int)buffer[344] - 48;
  temp_music_status = (int)buffer[414] - 48;
  Serial.println(temp_music_vol);
  Serial.println(temp_current_music);
  Serial.println(temp_music_status);
  wifi.releaseTCP();
}
//音乐******************************************************************
//音乐******************************************************************
void mp3Handle() {
  //Handle play things.
  if (canPlay) {
    if (current_music != temp_current_music) {
      idChange = true;
      current_music = temp_current_music;
    }
    if (music_vol != temp_music_vol) {
      volChange = true;
      music_vol = temp_music_vol;
    }
    if (music_status != temp_music_status) {
      statusChange = true;
      music_status = temp_music_status;
    }
    if (statusChange) {
      if (music_status == 1) {
        audio_play();
      }
      else {
        audio_pause();
      }
    }
    if (volChange) {
      audio_vol(music_vol);
    }
    if (idChange) {
      audio_choose(current_music + 1);
      audio_play();
    }
    volChange = false;
    idChange = false;
    statusChange = false;
  }
}
//音乐******************************************************************
/***************************************************
 *  Name:        setup
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Setup for the Arduino.
 ***************************************************/
void setup(void)
{//音乐******************************************************************
  Serial.begin(115200);
  //I don't konw....
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println(F("WIFI start"));
  delay(100);
  WifiInit(EspSerial, UARTSPEED);
  wifi.setOprToStationSoftAP();
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.println(F("WIFI Connect!"));
    isConnected = true;
  }
  else {
    isConnected = false;
    Serial.println(F("NO WIFI"));
  }
  //what's MUX??
  wifi.disableMUX();
  //initialize  audio module 
  audio_init(DEVICE_TF, MODE_One_END, music_vol);
  //音乐******************************************************************
  //彩灯********************************
  Serial.begin(9600);
  pinMode(Light_PIN, INPUT);
  strip.begin();                 //彩灯初始化
  strip.setBrightness(60);       //设置彩灯亮度
  //彩灯********************************
  //睡眠中断************************************
  Serial.begin(9600);//初始化串口
  /* Setup the pin direction. */
  pinMode(pin2, INPUT);//设置端口模式为输入
  irrecv.enableIRIn(); // 启动红外解码
  Serial.println("Initialisation complete.");
  //睡眠中断************************************

  //传感器*********************************************************

    //初始化串口波特率  
  Wire.begin();
  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.print(F("setup begin\r\n"));
  delay(100);
  pinMode(sensorPin_1, INPUT);

  WifiInit(EspSerial, UARTSPEED);

  Serial.print(F("FW Version:"));
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print(F("to station + softap ok\r\n"));
  }
  else {
    Serial.print(F("to station + softap err\r\n"));
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print(F("Join AP success\r\n"));

    Serial.print(F("IP:"));
    Serial.println(wifi.getLocalIP().c_str());
  }
  else {
    Serial.print(F("Join AP failure\r\n"));
  }

  if (wifi.disableMUX()) {
    Serial.print(F("single ok\r\n"));
  }
  else {
    Serial.print(F("single err\r\n"));
  }

  Serial.print(F("setup end\r\n"));

  //传感器*********************************************************8

}
//传感器*********************************************************8

void getSensorData() {
  sensor_tem = TempMonitor.getTemperature();
  sensor_hum = TempMonitor.getHumidity();
  //获取光照
  sensor_lux = analogRead(A0);
  delay(1000);
  dtostrf(sensor_tem, 2, 1, sensor_tem_c);
  dtostrf(sensor_hum, 2, 1, sensor_hum_c);
  dtostrf(sensor_lux, 3, 1, sensor_lux_c);
}
void updateSensorData() {
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据
    Serial.print("create tcp ok\r\n");

    jsonToSend = "{\"Temperature\":";
    dtostrf(sensor_tem, 1, 2, buf);
    jsonToSend += "\"" + String(buf) + "\"";
    jsonToSend += ",\"Humidity\":";
    dtostrf(sensor_hum, 1, 2, buf);
    jsonToSend += "\"" + String(buf) + "\"";
    jsonToSend += ",\"Light\":";
    dtostrf(sensor_lux, 1, 2, buf);
    jsonToSend += "\"" + String(buf) + "\"";
    jsonToSend += "}";



    postString = "POST /devices/";
    postString += DEVICEID;
    postString += "/datapoints?type=3 HTTP/1.1";
    postString += "\r\n";
    postString += "api-key:";
    postString += apiKey;
    postString += "\r\n";
    postString += "Host:api.heclouds.com\r\n";
    postString += "Connection:close\r\n";
    postString += "Content-Length:";
    postString += jsonToSend.length();
    postString += "\r\n";
    postString += "\r\n";
    postString += jsonToSend;
    postString += "\r\n";
    postString += "\r\n";
    postString += "\r\n";

    const char *postArray = postString.c_str();                 //将str转化为char数组
    Serial.println(postArray);
    wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)
    Serial.println("send success");
    if (wifi.releaseTCP()) {                                 //释放TCP连接
      Serial.print("release tcp ok\r\n");
    }
    else {
      Serial.print("release tcp err\r\n");
    }
    postArray = NULL;                                       //清空数组，等待下次传输数据

  }
  else {
    Serial.print("create tcp err\r\n");
  }
}
//传感器*********************************************************8


//音乐******************************************************************
void drawPlay() {
  u8g.drawBox(4, 4, 8, 16);
  u8g.drawBox(20, 4, 8, 16);
  u8g.setPrintPos(32, 16);
  u8g.print("Playing");
}
//音乐******************************************************************
//音乐******************************************************************
void drawPause() {
  u8g.drawTriangle(4, 4, 30, 8, 4, 16);
  u8g.setPrintPos(32, 16);
  u8g.print("Paused");
}
//音乐******************************************************************
//音乐******************************************************************
void drawVol() {
  u8g.drawLine(4, 35, 4 + 30 * 4, 35);
  u8g.drawLine(4 + 30 * 4, 35, 4 + 30 * 4, 35 - 30 * 0.6);
  u8g.drawLine(4, 35, 4 + 30 * 4, 35 - 30 * 0.6);
  u8g.drawTriangle(4, 35, 4 + music_vol * 4, 35, 4 + music_vol * 4, 35 - music_vol * 0.6);
}
//音乐******************************************************************
//音乐******************************************************************
void drawBottom() {
  u8g.setPrintPos(4, 16 * 4);
  switch (rollRoomMembers) {//更换寝室号、姓名、学号
  case 0:
    u8g.print("****ROOM 512****");
    break;
  case 1:
    u8g.print("TIAN: 2019210692");
    break;
  case 2:
    u8g.print("LI:2019210666");
    break;
  case 3:
    u8g.print("ZHANG:2019210664");
    break;
  case 4:
    u8g.print("YANG:2018210662");
    break;
  }
}
//音乐******************************************************************
//音乐******************************************************************
void drawAll() {
  u8g.setFont(u8g_font_7x13);
  if (music_status == 0) {
    drawPause();
  }
  else {
    drawPlay();
  }
  drawVol();
  drawTitle();
  drawBottom();
}
//音乐******************************************************************
//音乐******************************************************************
/***************************************************
 *  Name:        loop
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Main application loop.
 ***************************************************/
void loop(void)
{
  //音乐******************************************************************
  if (isConnected) {
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
      Serial.print(F("TCP\n"));
      isConnected = true;
    }
    else {
      Serial.print(F("No TCP\n"));
      isConnected = true;
    }
    wifi.sendFromFlash(GETDATA, sizeof(GETDATA));
    networkHandle();
    mp3Handle();
    u8g.firstPage();
    do {
      drawAll();
    } while (u8g.nextPage());
  }
  else
  {
    u8g.firstPage();
    do {
      drawNotConnected();
    } while (u8g.nextPage());
    delay(5000);
    setup();
  }
  rollCount++;
  rollCount = rollCount % strlen(names[current_music]);
  //show ata lower speed than the name of song.
  if (bottomBar) {
    bottomBar = false;
    rollRoomMembers = rollRoomMembers + 1;
    rollRoomMembers = rollRoomMembers % 4;
  }
  else {
    bottomBar = true;
  }
//音乐******************************************************
  //彩灯********************************
  sensorValueLIGHT = analogRead(Light_PIN);//光检测
  Serial.println(sensorValueLIGHT);//彩色led灯根据光强调节颜色和亮度
  if (sensorValueLIGHT < Light_value1)
  {//若光强小于500
    strip.setAllLED(600, 600, 600);
    strip.show();
  }

  else if (sensorValueLIGHT >= Light_value1)//光照大于500灯光自动熄灭
  {
    strip.setAllLED(0, 0, 0);
    strip.show();
  }
  //彩灯********************************
  //睡眠中断************************************
  currentMillis = millis();//读取系统计时器
  Serial.print("Awake for ");
  Serial.print(currentMillis - previousMillis, DEC);//计算清醒时间
  Serial.println(" second");
  delay(1000);

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);//串口打印接收的红外信息
    irrecv.resume(); // 接收下一个值
    previousMillis = currentMillis;//存储本次循环结束时的时间点
  }

  if (currentMillis - previousMillis > interval) {//如果清醒时间大于了设置的时间
    previousMillis = currentMillis; //清零清醒时间
    Serial.println("Entering sleep");
    enterSleep();//进入睡眠
  }
  if (currentMillis < previousMillis)
    previousMillis = currentMillis = 0; //如果系统计时器清0，则清0 所有计时器相关的变量。
  //睡眠中断************************************

  //传感器*********************************************************8

  if (sensor_time > millis())  sensor_time = millis();

  if (millis() - sensor_time > INTERVAL_SENSOR)              //传感器采样时间间隔  
  {
    getSensorData();                                        //读串口中的传感器数据
    sensor_time = millis();
  }


  if (net_time1 > millis())  net_time1 = millis();

  if (millis() - net_time1 > INTERVAL_NET)                  //发送数据时间间隔
  {
    updateSensorData();                                     //将数据上传到服务器的函数
    net_time1 = millis();
  }
  //传感器*********************************************************8
}

