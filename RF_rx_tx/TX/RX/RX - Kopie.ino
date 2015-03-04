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
    vw_set_tx_pin(2);
    vw_setup(500);  // Bits per sec
    pinMode(13, OUTPUT);  // RX
    pinMode(7, OUTPUT);  // TX
    
    vw_rx_start();       // Start the receiver PLL running
}
    void loop()
{
  if(vx_tx_active())
    Serial.println(":)");
 
    
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      Serial.println("RX");
      String rx = String("");      
      for (int i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido   
            rx +=String((char)buf[i]);          
                
      Serial.print(rx);

      if (msg1.equals(rx)) {
         digitalWrite(13,1); 
         Serial.println("-Done");    
         sendSgn_1();    
      } 
      if (msg2.equals(rx)){  
         digitalWrite(13,0);
         Serial.println("-Done");
         sendSgn_2();         
      }       
    }
    //----------------
    // Send feedback
    
}
void sendSgn_1()
{
        controller="1"  ;
	if(vw_send((uint8_t *)controller, strlen(controller)))
          Serial.println("send");;
	vw_wait_tx(); // Wait until the whole message is gone
        if(vx_tx_active())
          Serial.println("vx_tx_active");

	digitalWrite(7,1);
        delay(500);
        digitalWrite(7,0);
        delay(500);
        digitalWrite(7,1);        
        delay(500);
        digitalWrite(7,0);

       Serial.println("PumpIsON");
}
void sendSgn_2()
{
        controller="0"  ;
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole message is gone
        
          	
        digitalWrite(7,1);
        delay(500);
        digitalWrite(7,0);
        delay(500);
        digitalWrite(7,1);        
        delay(500);
        digitalWrite(7,0);

       Serial.println("PumpIsOFF");
}
