# Hun Capstone Introduction
The Capstone Experience is an independent project completed by all Hun Seniors and PGs. It provides opportunities for students to complete in-depth studies or explorations of things that are meaningful to them. 
## Mini Car 
Peter and I decided to build a mini car using Arduino that its motion is controlled by the music(notes/ frequencies) played by his soprano saxophone. The main algorithm we used was the FFT(Fast Fourier Transform), which computes the DFT(Discrete Fourier Transform).

![img_1934](https://user-images.githubusercontent.com/33791310/40880253-333bca82-667b-11e8-8c39-77aeb965393d.jpg)


Youtube link to see actual running:
https://youtu.be/tLRhheRjBR8
## Hardware Components
Arduino Uno board  
Electret Microphone Amplifier - MAX4466  
FA-130 Motors  
L9910 Motor Dual-Channel H-Bridge Motor Driver Module  
Plastic Chassis and wheels  

## References and library
This arduinoFFT library is suitable for our purpose with great consistency and accurarcy -- 
https://github.com/kosme/arduinoFFT

And some helpful articles throughout the building proccess:

Example code and graphs to show results --  
https://www.norwegiancreations.com/2017/08/what-is-fft-and-how-can-you-implement-it-on-an-arduino/

Very good explaination of the FFT and DFT although it is in Matlab --  
https://www.gaussianwaves.com/2015/11/interpreting-fft-results-complex-dft-frequency-bins-and-fftshift/
