//Made by Elton Lin 5/28/2018 for Senior Capstone at Hun 

//References are https://github.com/kosme/arduinoFFT
//and https://www.norwegiancreations.com/2017/08/what-is-fft-and-how-can-you-implement-it-on-an-arduino/

#include "arduinoFFT.h"

//Must be a power of 2
#define SAMPLES 128             
//Hz, must be less than 10000 due to ADC, and the maximum range it 
//will detect is half of the rate, in this case: 1500/2 = 750Hz
#define SAMPLING_FREQUENCY 1500 
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];

//Pins for motor
const int in1Pin=2;
const int in2Pin=3;
const int in3Pin=4;
const int in4Pin=5;

const int thresold = 2;

//counters for less sensitive mode(requires multiple matching freq to act)

int counter_forward = 0;
int counter_back = 0;
int counter_right = 0;
int counter_left = 0;
int counter_pause = 0;


void setup() 
{ 
  Serial.begin(9600);
  //10^6 microseconds = 1 second 
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

  //Be aware that motors produce sound when spinning, make sure to avoid
  //The notes and ranges: 
  Serial.println("C (465 - 480): forward");  
  Serial.println("C# (490 - 510): pause");
  Serial.println("D (525 - 545): pause");   
  Serial.println("E (590 - 610): turn left");  
  Serial.println("F (625 - 645): backward");
  Serial.println("G (705 - 725): turn right");
   
} 
void loop() 
{
  /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros(); //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(0);
        vImag[i] = 0;
        
        //helping continueing?
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    
    /*PRINT RESULTS*/
    Serial.println(peak);     //Print out what frequency is the most dominant.
    
    //Ranges of frequencies corresponding to actions/motions
    //Should be costomized based on the instrument, sopranos saxophone
    //is used in this case
    if(peak >= 490 && peak <= 510)
    {
       //emergency stop
       pause();
    }
    else if(peak >= 465 && peak <= 480)
    {
      counter_forward ++;
    }
    else if(peak >= 525 && peak <= 545)
    {
    }
    
    else if(peak >= 625 && peak <= 645)
    {
      counter_back ++;
    }
    else if(peak >= 590 && peak <= 610)
    {
      counter_left ++;
    }
    else if(peak >= 705 && peak <= 720)
    {
      counter_right ++;
    }
    else
    {
      //pause();
    }
    

    /*Based on the counter, perform corresponding action when 
    frequency is in range twice in a row to confirm.*/
    //the larger thresold, the more accurate but slower reaction
    if(counter_forward >= thresold)
    {
      forward();
    }
    else if(counter_back >= thresold)
    {
      back();
    }
    else if(counter_left >= thresold)
    {
      left();
    }
    else if(counter_right >= thresold)
    {
      right();
    }
    
}


//Delay time could be ajusted based on length of notes for smoothness
void forward()
{
    analogWrite(in1Pin,0);
    analogWrite(in2Pin,255); 
    analogWrite(in3Pin,255);
    analogWrite(in4Pin,0);
    delay(500);
    pause();
    resetCounters();
}   
void back()
{
    analogWrite(in1Pin,255);
    analogWrite(in2Pin,0); 
    analogWrite(in3Pin,0);
    analogWrite(in4Pin,255); 
    delay(500);
    pause();
    resetCounters();
}
void pause()
{
    analogWrite(in1Pin,0);
    analogWrite(in2Pin,0); 
    analogWrite(in3Pin,0);
    analogWrite(in4Pin,0); 
    resetCounters();
}
//Delay for turning depends on the friction of the floor and 
//what angle you want to turn
void left()
{
    analogWrite(in1Pin,0);
    analogWrite(in2Pin,0); 
    analogWrite(in3Pin,255);
    analogWrite(in4Pin,0); 
    delay(200);
    pause();
    resetCounters();
}
void right()
{
    analogWrite(in1Pin,0);
    analogWrite(in2Pin,255); 
    analogWrite(in3Pin,0);
    analogWrite(in4Pin,0);
    delay(200);
    pause();
    resetCounters();
}

//reset all counters

void resetCounters()
{
    counter_pause = 0;
    counter_forward = 0; 
    counter_back = 0;
    counter_left = 0;
    counter_right = 0; 
}
