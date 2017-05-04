//湿度传感器基本程序
//2016-3-24
#define Wet_in 8 //传感器信号取自第8针脚

void setup() {
  Serial.begin(9600);
  pinMode(Wet_in, INPUT); //定义湿度传感器针脚
  Serial.flush();
}

void loop() {
  byte Wet;
  Wet = digitalRead(Wet_in); //采集湿度值，湿为0，干为1
  Serial.println(Wet);  //串口监视
  delay(5000);  //间隔5秒取一个值
}
