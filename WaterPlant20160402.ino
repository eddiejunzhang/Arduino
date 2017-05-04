//户外，电池供电，液位/湿度传感，继电器控制自动浇花控制
//2016-4-1，Eddie Zhang, Beijing
//==============================================
#define HumidityPin1 8 //湿度传感器信号取自第8针脚
#define HumidityPin2 9 //湿度传感器信号取自第9针脚
#define analogPin 1 //水位传感器信号取自模拟口第1针脚
#define RelayPin 13 //设定控制继电器的数字IO脚
#define ledPin 12 //设定控制指示二极管的数字IO脚

int WaterTime = 2; //浇花时间，单位分钟
int IdealTime = 120; //两次浇花之间间隔时间，单位分钟，必须大于浇花时间
int TimeLeft = 0; //剩余时间变量，分钟
int val = 0; //定义变量 val 初值为 0，用于保存液位模拟量

void setup() {
  Serial.begin(9600);
  pinMode(HumidityPin1, INPUT); //定义湿度传感器针脚
  pinMode(HumidityPin2, INPUT); //定义湿度传感器针脚
  pinMode(RelayPin, OUTPUT); //定义继电器针脚
  pinMode(ledPin, OUTPUT); //定义发光二极管针脚
  Serial.flush();
}

void loop() {
  byte Humidity1;
  byte Humidity2;
  unsigned char i;
  int j;
  //采集湿度计1的值
  Humidity1 = digitalRead(HumidityPin1); //采集湿度值，湿为0，干为1
  Serial.print("Hum1=");
  Serial.println(Humidity1);
  //采集湿度计2的值
  Humidity2 = digitalRead(HumidityPin2); //采集湿度值，湿为0，干为1
  Serial.print("Hum2=");
  Serial.println(Humidity2);
  //采集水位传感器的值
  val = analogRead(analogPin); //读取模拟值送给变量 val
  Serial.print("val=");
  Serial.println(val);
  //如果湿度计1为高电平（1）或湿度计2为高电平（1），则
  if (Humidity1 == 1 || Humidity2 == 1)
  {
    //如果水位值大于700(有水)，则
    if (1 == 1)
    {
      //继电器控制电平为高
      digitalWrite(RelayPin, HIGH); //设定PIN13脚为HIGH = 5V左右
      //延时5分钟
      for (j = 1; j <= WaterTime * 60; j++)
      {
        delay(950); //设定延时时间，950 = 0.95秒
        digitalWrite(ledPin, HIGH); //设定PIN12脚为HIGH = 5V左右,每秒钟快闪一次
        delay(50); //设定延时时间，50 = 0.05秒
        digitalWrite(ledPin, LOW); //设定PIN12脚为LOW = 0V
        //Serial.print(" pum run(sec)=");
        //Serial.println(j);
      }
      //继电器控制电平为低
      //启动继电器打开，水泵不工作
      digitalWrite(RelayPin, LOW); //设定PIN13脚为LOW = 0V
    }
  }
  //延时6小时
  TimeLeft = IdealTime - WaterTime;
  do  //开始倒计时
  {
    //Serial.print("TimeLeft(min)=");
    //Serial.println(TimeLeft);
    for (i = 1; i <= 59; i++)
    {
      delay(1000); //设定延时时间，1000 = 1秒
      //Serial.print(" TimeLeft(sec)=");
      //Serial.println(i);
    }
    //每60秒闪一秒
    digitalWrite(ledPin, HIGH); //设定PIN12脚为HIGH = 5V左右,快闪一次
    delay(1000); //设定延时时间，50 = 0.05秒
    digitalWrite(ledPin, LOW); //设定PIN12脚为LOW = 0V
    TimeLeft--;
  }
  while (TimeLeft > 0);
  Humidity1 = 0;
  Humidity2 = 0;
}

