/**************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier(Sound locator with 3 mic and 3 led)
**************/
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz) örneklemeyi 50mS ile yani 20Hz ile yapıyoruz
unsigned int sample0;
unsigned int sample1;
unsigned int sample2;

 
void setup() 
{
   Serial.begin(9600);
   pinMode(8, OUTPUT);
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
}
 
 
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak[3] = {0,0,0};   // peak-to-peak level
   double volts[3]={0.0,0.0,0.0};
 
   unsigned int signalMax[3] = {0,0,0};
   unsigned int signalMin[3] = {1024,1024,1024};
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample2 = analogRead(2);
      sample1=analogRead(1);
      sample0=analogRead(0);
      if (sample0 < 1024)  // parazit verilerden kurtarmak için
      {
         if (sample0 > signalMax[0])
         {
            signalMax[0] = sample0;  // max seviyeyi kaydeder
         }
         else if (sample0 < signalMin[0])
         {
            signalMin[0] = sample0;  // min seviyeyi kaydedr
         }
      }
      if (sample1 < 1024)  // parazit verilerden kurtarmak için
      {
         if (sample1 > signalMax[1])
         {
            signalMax[1] = sample1;  // max seviyeyi kaydeder
         }
         else if (sample1 < signalMin[1])
         {
            signalMin[1] = sample1;  // min seviyeyi kaydedr
         }
      }
      if (sample2 < 1024)  // 
      {
         if (sample2 > signalMax[2])
         {
            signalMax[2] = sample2;  //
         }
         else if (sample2 < signalMin[2])
         {
            signalMin[2] = sample2;  // 
         }
      }
   }
   for(int i=0;i<3;i++)
   {
    peakToPeak[i] = signalMax[i] - signalMin[i];  // max - min = peak-peak genligi
    volts[i] = (peakToPeak[i] * 5.0) / 1024;  // volt a donusum
    
    Serial.println(String(i)+". mikrofon çıkışı==> "+volts[i]);
    }
    Serial.println();
    if(peakToPeak[0]>0.50&&peakToPeak[0]>peakToPeak[1]&&peakToPeak[0]>peakToPeak[2]){
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      }
       else if(peakToPeak[1]>0.50&&peakToPeak[1]>peakToPeak[0]&&peakToPeak[1]>peakToPeak[2]){
      digitalWrite(9, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(10, LOW);
      }
       else if(peakToPeak[2]>0.50&&peakToPeak[2]>peakToPeak[1]&&peakToPeak[2]>peakToPeak[0]){
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      }
      else
      {
        
   digitalWrite(10, LOW);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
        }
   
   
 
   
   delay(500);
}
