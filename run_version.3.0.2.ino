#define trigAhead 9
#define echoAhead 8
#define trigRight 7
#define echoRight 6
#define trigLeft 4
#define echoLeft 2
#define enA 5
#define enB 3
#define IN1 13
#define IN2 12
#define IN3 11
#define IN4 10
#define distanceCompare 30
#define timeDelay 100
#define timeDelayTurn 2500 //Canh thời gian để rẻ 1 góc 90 độ

char data;
int xMaxMinus = 0;
int xMaxPlus = 0;
int yMaxMinus = 0;
int yMaxPlus = 0;
int direc = 0;
int xCar = 0;
int yCar = 0;
//int distanceGoDown = 0;
int checkDescreaseAcreage = 0;
boolean isFirstRound = true;
boolean isRunAhead = false;
boolean isRunDown = false;
boolean isTurnRight = false;
boolean isTurnLeft = false;
boolean isAuto = false;
boolean isFindTheWall = true;
//Second Algor
boolean isRight = true;
void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
    pinMode(trigAhead,OUTPUT);
    pinMode(echoAhead,INPUT);
    pinMode(trigRight,OUTPUT);
    pinMode(echoRight,INPUT);
    pinMode(trigLeft,OUTPUT);
    pinMode(echoLeft,INPUT);
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);
}

//void checkCamBien()
//{
//  Serial.print(getDistanceRight());
//  Serial.println("++++++++++++++");
//  delay(5000);
//  Serial.print(getDistanceLeft());
//  Serial.println("              ");
//  delay(5000);
//  Serial.print(getDistanceAhead());
//  Serial.println("--------------");
//  delay(5000);  
//}

void checkBanhXe()
{
//  goAhead();
//  delay(5000);
//  goDown();
//  delay(5000);
  turnRight();
  delay(5000);
  turnLeft();
  delay(5000); 
}

void loop() {
	
	if(isRunAhead && getDistanceAhead() < 15)
	{
		stopCar();
	}
	
	if(Serial.available() > 0)
	{
		
		delay(300);
		data=Serial.read();
		isAuto = false;
		//Serial.print(data);
		if(data == 'a')
		{
			if(getDistanceAhead() > 60)
			{
				stopCar();
        delay(500); 
				goAhead();
			}
			
		}
		else if(data == 'b')
		{
			stopCar();
      delay(500); 
			goDown();
		}
		else if(data == 'c')
		{
			if(getDistanceLeft() > 30)
			{
				stopCar(); 
				turnLeft();
				delay(timeDelayTurn);
			  stopCar(); 
			}
			if(getDistanceAhead() > 60)
			{
				goAhead();
			}
		}
		else if(data == 'd')
		{
			if(getDistanceLeft() > 30)
			{
				stopCar(); 
				turnRight();
				delay(timeDelayTurn);           
			  stopCar();
			}
			if(getDistanceAhead() > 60)
			{ 
				goAhead();
			}
		}
		else if(data == 'e' || data == 'g')
		{
			stopCar();		
		}
		else if(data == 'f')
		{
			isAuto = true;
			isFindTheWall = true;
			isFirstRound = true;
			xMaxMinus = 0;
			xMaxPlus = 0;
			yMaxMinus = 0;
			yMaxPlus = 0;
			direc = 0;
			xCar = 0;
			yCar = 0;
		}
	}
 
	if(isFindTheWall && isAuto)
	{
		findTheWall();
	}
 
	if(isFirstRound && isAuto)
	{
		runCarFirstRound();
	}
		
	if(!isFirstRound && isAuto)
	{
		runCarOtherRound();
	} 
}

int getDistance(int trig, int echo)
{
  // put your main code here, to run repeatedly:
  unsigned long duration; // biến đo thời gian
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig,0);   // tắt chân trig
        
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration = pulseIn(echo,HIGH);  
  // Tính khoảng cách đến vật.
  return int(duration/2/29.412);
}

int getDistanceAhead()
{
  return getDistance(trigAhead, echoAhead);
}

int getDistanceRight()
{
  return getDistance(trigRight, echoRight);
}

int getDistanceLeft()
{
  return getDistance(trigLeft, echoLeft);
}

void goAhead()
{
	if(!isRunAhead)
	{
		digitalWrite(IN1,LOW);
		digitalWrite(IN2,HIGH);
		digitalWrite(IN3,HIGH);
		digitalWrite(IN4,LOW);
		analogWrite(enB,151);
		analogWrite(enA,160);
		isRunAhead = true;
		isRunDown = false;
		isTurnLeft = false;
		isTurnRight = false;
	}
}

void goDown()
{
	if(!isRunDown)
	{
		digitalWrite(IN1,HIGH);
		digitalWrite(IN2,LOW);
		digitalWrite(IN3,LOW);
		digitalWrite(IN4,HIGH);
		analogWrite(enB,152);
		analogWrite(enA,155);
		isRunDown = true;
		isRunAhead = false;
		isTurnLeft = false;
		isTurnRight = false;
	}
}  

void stopCar()
{
	if(isRunAhead || isRunDown || isTurnLeft || isTurnRight)
	{
		digitalWrite(IN1,LOW);
		digitalWrite(IN2,LOW);
		digitalWrite(IN3,LOW);
		digitalWrite(IN4,LOW);
		isRunAhead = false;
		isRunDown = false;
		isTurnLeft = false;
		isTurnRight = false;
	}
	delay(700);
}

void turnRight()
{
	if(!isTurnRight)
	{
		digitalWrite(IN1,LOW);
		digitalWrite(IN2,LOW);
		digitalWrite(IN3,HIGH);
		digitalWrite(IN4,LOW);
		analogWrite(enB,147);
		analogWrite(enA,160);
		isRunAhead = false;
		isRunDown = false;
		isTurnLeft = false;
		isTurnRight = true;
	}
}

void turnLeft()
{
	if(!isTurnLeft)
	{
		digitalWrite(IN1,LOW);
		digitalWrite(IN2,HIGH);
		digitalWrite(IN3,LOW);
		digitalWrite(IN4,LOW);
		analogWrite(enB,147);
		analogWrite(enA,160);		
		isRunAhead = false;
		isRunDown = false;
		isTurnLeft = true;
		isTurnRight = false;
	}
}

void excuteGoAhead()
{
	//Hướng xe là hướng thẳng so với ban đầu
    if(direc == 0)
    {
		xCar++;
        //distanceGoDown++;
        if((xCar > xMaxPlus) && isFirstRound)
        {
          xMaxPlus = xCar;    
		    }
	  }
	//Hướng xe là chạy lui so với ban đầu
	else if(direc == 2 || direc == -2)
	{
		xCar--;
		if((xCar < xMaxMinus) && isFirstRound)
		{
			xMaxMinus = xCar;
		}
	}
	//Hướng xe là bên phải so với ban đầu
	else if(direc == 1 || direc == -3)
	{
		yCar--;
		if((yCar < yMaxMinus) && isFirstRound)
		{
			yMaxMinus = yCar;  
		}
	}
	//Hướng xe là bên trái so với ban đầu
	else if(direc == -1 || direc == 3)
	{
		yCar++;
		if((yCar > yMaxPlus) && isFirstRound)
		{
			yMaxPlus = yCar;  
		}		
	}
    
  goAhead();
  //Delay 1s, lưu tọa độ
  delay(timeDelay);
}

void excuteTurnLeft()
{
	turnLeft();
    //Delay để quay 1 gócc 90 độ
    delay(timeDelayTurn);
	//Giảm direc đi 1 khi rẻ trái
    direc--; // direc = --direc % 4;
	if(direc == -4) direc = 0;
    
    stopCar();
	//yCar++;
}

void excuteTurnRight()
{
	turnRight();
	//Delay để quay 1 góc 90 độ
    delay(timeDelayTurn);
    //Tăng direc lên 1 khi rẻ phải
    direc++; // direc = ++direc % 4;
	if(direc == 4) direc = 0;
	
	stopCar();
    //yCar--;
}

void excuteGoDown()
{
	//for(int i = 0 ; i < distanceGoDown ; i++)
    do
	{
      goDown();
      //Delay 0.5s, lưu tọa độ
      delay(timeDelay);
      //Hướng xe là hướng lui so với ban đầu
      if(direc == 2 || direc == -2)
      {
        xCar++;//Xe chạy lui
      }
      //Hướng xe là chạy thẳng so với ban đầu
      else if(direc == 0)
      {
        xCar--;//Xe chạy lui
      }
	  //Hướng xe là bên phải so với ban đầu
	  else if(direc == 1 || direc == -3)
	  {
		yCar++;
	  }
	  //Hướng xe là bên trái so với ban đầu
	  else if(direc == -1 || direc == 3)
	  {
		yCar--;		
	  }      
    }while(getDistanceLeft() < distanceCompare && getDistanceRight() < distanceCompare);
	
	//Quay đầu tìm lối ra khi vào ngõ cụt
	do
	{
		excuteTurnLeft();	
	}while(getDistanceAhead() < distanceCompare);
}

//Tìm tường trước khi bắt đầu
void findTheWall()
{
	bool isVoice = false;
	if(getDistanceRight() > distanceCompare)
	{
		//Rẻ phải
		turnRight();
		delay(timeDelayTurn);
		while(getDistanceAhead() >= distanceCompare)
		{
		  if(Serial.available() > 0)
		  {
			isVoice = true;
			isAuto = false;
			break;
		  }
			//Chạy thẳng đến bức tường
			goAhead();
			delay(timeDelay);
		}

		if(!isVoice)
		{
		  //Rẻ trái để đi song song với tường, bắt đầu thuật toán
		  turnLeft();
		  delay(timeDelayTurn);
		}
	}
	isFindTheWall = false;
}


//Tọa độ x+ là hướng thẳng ban đầu, y+ là hướng ngang bên trái ban đầu
void runCarFirstRound()
{
  int distanceRight = getDistanceRight();
  int distanceAhead = getDistanceAhead();
  int distanceLeft = getDistanceLeft();

  //Xe xuất phát ở góc tường bên phải
  //Xa chạy thẳng, tường bên phải
  if( distanceRight < distanceCompare && distanceAhead >= distanceCompare)
  {
     excuteGoAhead();
  }
  
  //Xe rẻ phải
  else if(distanceRight >= distanceCompare && distanceAhead >= distanceCompare)
  {
    excuteTurnRight();
	
	while(getDistanceRight() >= distanceCompare && getDistanceAhead() >= distanceCompare)
	{
		if(Serial.available() > 0)
		{
			isAuto = false;
			break;
		}
		excuteGoAhead();
	}
  }

  //Xe rẻ trái
  //else if(distanceAhead < distanceCompare && distanceLeft >= distanceCompare && distanceRight < distanceCompare)
  else if(distanceAhead < distanceCompare && distanceLeft >= distanceCompare)
  {
    excuteTurnLeft();
  }
  
  //Xe tông vào tường
  //else if(distanceAhead < distanceCompare && distanceLeft >= distanceCompare && distanceRight >= distanceCompare)
  //{
	  
  //}

  //Xe chạy lui - ngõ cụt
  else if(distanceRight < distanceCompare && distanceAhead < distanceCompare && distanceLeft < distanceCompare)
  {
    excuteGoDown();
  }
  //Lỗi - phương án 2
  else
  {
	  stopCar();
	  delay(5000);
	  secondPlan();
  }
  
  //Xe chạy xong 1 vòng trở về toạn độ 0 0
  if(xCar == 0 && yCar == 0)
  {
	isFirstRound = false;
	//Xe đang ở tia Ox
	checkDescreaseAcreage = 3;
  }
}

void runCarOtherRound()
{
  int distanceRigt = getDistanceRight();
  int distanceAhead = getDistanceAhead();
  int distanceLeft = getDistanceLeft();

  //Cách xe chạy khi nằm ở trong diện tích ảo giống như chạy vòng 1
  if(xCar < xMaxPlus && yCar < yMaxPlus && xCar > xMaxMinus && yCar > yMaxMinus)
  {
	  //Xa chạy thẳng, tường bên phải
  	if( distanceRigt < distanceCompare && distanceAhead >= distanceCompare)
  	{
  		excuteGoAhead();
  	}
    
  	//Xe rẻ phải
  	else if(distanceRigt >= distanceCompare && distanceAhead >= distanceCompare)
  	{
  		excuteTurnRight();
  		
  		while(getDistanceRight() >= distanceCompare && (xCar < xMaxPlus && yCar < yMaxPlus && xCar > xMaxMinus && yCar > yMaxMinus) && getDistanceAhead() >= distanceCompare)
  		{
			if(Serial.available() > 0)
			{	
				isAuto = false;
				break;
			}
  			excuteGoAhead();
  		}
  	}
  	//Xe rẻ trái
  	else if(distanceAhead < distanceCompare && distanceLeft >= distanceCompare)
  	{
  		excuteTurnLeft();
  	}
  	//Xe chạy lui
  	else if(distanceRigt < distanceCompare && distanceAhead < distanceCompare && distanceLeft < distanceCompare)
  	{
  		excuteGoDown();
  	}
  	//Lỗi - phương án 2
  	else
  	{
  	  stopCar();
  	  delay(5000);
  	  secondPlan();
  	}
  }
  //Xe chạy trên đường có tọa độ Max
  else if(xCar == xMaxMinus || xCar == xMaxPlus || yCar == yMaxMinus || yCar == yMaxPlus)
  {
	  //Check giảm kích thước phòng
	  if(xCar == xMaxPlus && checkDescreaseAcreage == 1)
	  {
		  xMaxMinus++;
		  checkDescreaseAcreage = 2;
	  }
	  
	  if(yCar == yMaxPlus && checkDescreaseAcreage == 2)
	  {
		yMaxMinus++;
		checkDescreaseAcreage = 3;
	  }
	  
	  if(xCar == xMaxMinus && checkDescreaseAcreage == 3)
	  {
		  xMaxPlus--;
		  checkDescreaseAcreage = 4;
	  }
	  
	  if(xCar == yMaxMinus && checkDescreaseAcreage == 4)
	  {
		  yMaxPlus--;
		  checkDescreaseAcreage = 1;
	  }
	  
	  //Rẻ trái khi xe có hướng đâm tới các tọa độ max
	  if((xCar == xMaxPlus && direc == 0)	
        || (xCar == xMaxMinus && (direc == -2 || direc == 2))	
        || (yCar == yMaxPlus && (direc == -1 || direc == 3))	
        || (yCar == yMaxMinus && (direc == -3 || direc == 1))	
		|| (distanceAhead < distanceCompare && distanceLeft >= distanceCompare))
	  {
		  excuteTurnLeft();
	  }
	  else if(distanceAhead < distanceCompare && distanceLeft < distanceCompare)
	  {
		  excuteGoDown();
	  }
	  else
	  {
		  excuteGoAhead();
	  }
  }
  //Bó tay- dùng phương án dự phòng
  else
  {
	  stopCar();
	  delay(5000);
	  secondPlan();
  }
}

void secondPlan()
{
	int distanceRight = 0;
	int distanceAhead = 0;
	int distanceLeft = 0;
	int distanceAheadTemp = 0;
	
	while(true)
	{
		distanceRight = getDistanceRight();
		distanceAhead = getDistanceAhead();
		distanceLeft = getDistanceLeft();
		
		if(Serial.available() > 0)
		{	
			isAuto = false;
			break;
	    }
			
		if(distanceAhead > distanceCompare)
		{
			goAhead();
			delay(timeDelay);
		}
		else if(isRight && (distanceRight >= distanceCompare))
		{
			turnRight();
			delay(2*timeDelayTurn);
			isRight = false;
		}
		else if(isRight && ((distanceRight < distanceCompare)))
		{
			turnLeft();
			delay(2*timeDelayTurn);
		}
		else if(!isRight && (distanceLeft > distanceCompare))
		{
			turnLeft();
			delay(2*timeDelayTurn);
			isRight = true;
		}
		else if(!isRight && (distanceLeft < distanceCompare))
		{
			turnRight();
			delay(2*timeDelayTurn);
		}
		
		// Xe không di chuyển
		distanceAheadTemp = getDistanceAhead();
		if(distanceAheadTemp < (distanceAhead + 2) && distanceAheadTemp > (distanceAhead - 2))
		{
			goDown();
			delay(3000);
		}
	}
}
