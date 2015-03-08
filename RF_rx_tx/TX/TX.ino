//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>
char *controller;

int buttonStateA = 0;
int oldButtonState = 0;
String msg1 = "PumpIsON";
String msg2 = "PumpIsOFF";

void setup() {
      Serial.begin(9600);
      vw_set_ptt_inverted(true); //
      vw_set_tx_pin(8);
      vw_set_rx_pin(12);
      vw_setup(500);// speed of data transfer Kbps
      // Trasmettitore
      pinMode(13,OUTPUT);
      pinMode(7,OUTPUT);
      digitalWrite(13,LOW);
      digitalWrite(7,LOW);
      
      vw_rx_start();
}

void loop(){    
    // uint8_t buf[VW_MAX_MESSAGE_LEN];
    // uint8_t buflen = VW_MAX_MESSAGE_LEN;
      
     buttonStateA = digitalRead(2);
     
     if (oldButtonState!=buttonStateA)
     {
       
       int var =1;
       int res=0;
       unsigned long TimerA ;//   "ALWAYS use unsigned long for timers..."       
                             
       while(var < 10){
         
         // Trasmettitore
         if(buttonStateA == LOW)
         {
             sendSgn_0(); 
             TimerA= millis();
             while(millis()-TimerA <= 5000UL && var < 10)
             {
               if (ricevi(msg2)==1)
                 var=100; 
             }          
         }
         if(buttonStateA == HIGH)
         {
             sendSgn_1();
             TimerA= millis();
             while(millis()-TimerA <= 5000UL && var < 10)
             {
               if (ricevi(msg1)==1)
                 var=100; 
             }   
         } 
         var ++;
                    
       }
       
     }
     oldButtonState = buttonStateA;

    // Ricevitore
        
    //ricevi(msg1);
      
//----------------------
     delay(2000);
}
int ricevi(String retMsg)
{
  
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
   
   int res =0;  
   if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      Serial.print("RX: ");
      String rx = String("");      
      for (int i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido   
            rx +=String((char)buf[i]);                          
      Serial.println(rx);
      if (msg1.equals(rx)) {
         digitalWrite(7,1);
      } 
      if (msg2.equals(rx)){  
         digitalWrite(7,0);
      } 
      if (retMsg.equals(rx)){           
         res =1;
      }     
  } 
  
  return res;
}
void sendSgn(String msg)
{
  vw_rx_stop();
  strcpy(controller,msg.c_str());
  //controller=(char*) msg  ;
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole message is gone
	digitalWrite(13,1);
        delay(500);
        digitalWrite(13,0);
        delay(500);
        digitalWrite(13,1);        
        delay(500);
        digitalWrite(13,0);
  vw_rx_start();      
   //-----View Signal in Serial Monitor 
   Serial.println( msg);
//   for(int i=0; i<strlen(controller); i=i+1){       
//       Serial.print(controller[i]);       
//   }
}
void sendSgn_1()
{
  vw_rx_stop();
  controller="SetPumpON"  ;
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole message is gone
	digitalWrite(13,1);
        delay(500);
        digitalWrite(13,0);
        delay(500);
        digitalWrite(13,1);        
        delay(500);
        digitalWrite(13,0);
        vw_rx_start();
   //-----View Signal in Serial Monitor 
   Serial.println("SetPumpON");
//   for(int i=0; i<strlen(controller); i=i+1){       
//       Serial.print(controller[i]);       
//   }
}
void sendSgn_0()
{
  vw_rx_stop();
  controller="SetPumpOFF"  ;
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole message is gone
	digitalWrite(13,1);
        delay(500);
        digitalWrite(13,0);
        delay(500);
        digitalWrite(13,1);        
        delay(500);
        digitalWrite(13,0);
   vw_rx_start();
   //-----View Signal in Serial Monitor 
   Serial.println("SetPumpOFF");
//   for(int i=0; i<strlen(controller); i=i+1){
//       Serial.print(controller[i]);       
//   }  
}
