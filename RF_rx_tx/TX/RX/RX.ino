#include <VirtualWire.h>

//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................

int statoPmp =0;
char *controller;
String msg1 = "SetPumpON";
String msg2 = "SetPumpOFF";
void setup()
{
    Serial.begin(9600);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_set_tx_pin(8);
    vw_setup(500);  // Bits per sec
    pinMode(13, OUTPUT);  // RX
    pinMode(7, OUTPUT);  // TX
    //pinMode(4, OUTPUT);  // RELE
    digitalWrite(13,LOW);
    digitalWrite(7,LOW);
    digitalWrite(4,LOW);  
    
    vw_rx_start();       // Start the receiver PLL running
    
    checkStatus();
}
    void loop()
{
//  if(vx_tx_active())
//    Serial.println(":)");
 
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
//---
//sendSgn_0();
//--
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      Serial.println("RX");
      String rx = String("");      
      for (int i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido   
            rx +=String((char)buf[i]);          
                
      Serial.print(rx);
      int var=1;
      if (msg1.equals(rx)) {
         vw_rx_stop(); 
         digitalWrite(7,1); 
         Serial.println("-Done");
           //sendSgn_1(); 
      } 
      if (msg2.equals(rx)){
        vw_rx_stop();         
        digitalWrite(7,0);        
        Serial.println("-Done");
           //sendSgn_0();       
      }   
       int i = 0;
       while (i<5)
       {      
         checkStatus();
         i++;
       }
      //delay(5000);
      vw_rx_start();     
    }    
}
void checkStatus()
{
  
  int state = digitalRead(4);
  if (state == HIGH)
    sendSgn_1();
  if (state == LOW)
    sendSgn_0();
  
}

void sendSgn_0()
{
  controller="PumpIsOFF"  ;
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole message is gone
	digitalWrite(13,1);
        delay(500);
        digitalWrite(13,0);
        delay(500);
        digitalWrite(13,1);        
        delay(500);
        digitalWrite(13,0);        
   //-----View Signal in Serial Monitor 
   Serial.println("PumpIsOFF");
}
void sendSgn_1()
{
  controller="PumpIsON"  ;
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole message is gone
	digitalWrite(13,1);
        delay(500);
        digitalWrite(13,0);
        delay(500);
        digitalWrite(13,1);        
        delay(500);
        digitalWrite(13,0);        
   //-----View Signal in Serial Monitor 
   Serial.println("PumpIsON");
}

