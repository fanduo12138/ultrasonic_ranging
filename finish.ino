int latchPin = 8;
int clockPin = 12;
int dataPin = 11; //这里定义了那三个脚

const int TrigPin=13;
const int EchoPin=10;
float dis;

void setup ()
{
   pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT); //让三个脚都是输出状态

  pinMode(4,OUTPUT);             //数码管的GND
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

float once()
{
  float a;
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(12);
  digitalWrite(TrigPin,LOW);
  a=pulseIn(EchoPin,HIGH)/58.00;
  return a;
}

int Get()
{
  float m=(once()+once()+once())/3.00;
  int n=(int)m;
  return n;
}


void Dis(int n)
{
  int num[10]={215,20,205,93,30,91,219,21,223,95};
   digitalWrite(latchPin,LOW); //将ST_CP口上面加低电平让芯片准备好接收数据
   shiftOut(dataPin,clockPin,LSBFIRST,num[n]);
    /*这个就是用MSBFIRST参数让0-7个针脚以高电平输出（LSBFIRST 低电平）是dataPin的参数，
     clockPin的参数是变量a，前面我们说了这个变量会一次从1+1+到256，是个十进制数，
     输入到芯片后会产生8个二进制数，达到开关的作用*/
   digitalWrite(latchPin,HIGH); //将ST_CP这个针脚恢复到高电平
}

void number(int n)
{
    int x,y,z,w;
    w=n%10;
    z=(n/10)%10;
    y=(n/100)%10;
    x=(n/1000)%10;

    for(int i=20;i>0;i--){
    digitalWrite(4,LOW);
    Dis(x);
    delay(10);
    digitalWrite(4,HIGH);
    
    digitalWrite(5,LOW);
    Dis(y);
    delay(10);
    digitalWrite(5,HIGH);

    
    digitalWrite(6,LOW);
    Dis(z);
    delay(10);
    digitalWrite(6,HIGH);

    
    digitalWrite(7,LOW);
    Dis(w);
    delay(10);
    digitalWrite(7,HIGH);
    }
  
}


void loop()
{
   int n;
   n=Get();
   number(n);
}

