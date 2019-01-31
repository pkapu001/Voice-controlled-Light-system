#define CUSTOM_SETTINGS
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_SLIDER_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_SMS_SHIELD
#define INCLUDE_PHONE_SHIELD
#define INCLUDE_LCD_SHIELD
#define INCLUDE_LIGHT_SENSOR_SHIELD

/*Include 1Sheeld library. */
#include <OneSheeld.h>
#include <TTSShield.h>
#include <SMSShield.h>
#include <PHONEShield.h>
#include <LCDShield.h >



int Wpin = 13;
int Rpin = 12;
int Ypin = 11;
int Bpin = 10;
int Gpin = 9;

boolean whiteOn = false ;
boolean redOn = false ;
boolean yellowOn = false ;
boolean blueOn = false ;
boolean greenOn = false ;



/* Voice commands set by the user. */
const char playCommand[] = "play";
const char pauseCommand[] = "stop";
const char yellowCommand[] = "yellow";
const char greenCommand[] = "green";
const char blueCommand[] = "blue";
const char redCommand[] = "red";
const char whiteCommand[] = "cream";
const char danceCommand[] = "dance";
const char smsCommand[] = "send";
const char phoneCommand[] = "call";
const char party[] = "   PRATY TIME !!!!" ;

String acessnumber = "";
String admin = "" ;


const char password[] = "GetMeAccess007" ;
const char removeme[] = "removeme" ;
const char adminkick[] = "changeadmin" ;
int y = 0;

boolean dancesms = false ;
boolean partystatusoff = true ;
boolean partystarted = false ;

TTSShield text2speech;



void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, INPUT);
  /* Start Communication. */
  OneSheeld.begin();
  /* Error Commands handiling. */
  VoiceRecognition.setOnError(error);

  VoiceRecognition.start();
  LCD.begin();


}



void loop ()
{
  LCD.clear();
//  boolean NewSms = false;

//  if ( SMS.isNewSms()) {
//    NewSms = true ;

    /*  LCD.setCursor(0,0);
      LCD.print("NEW SMS");
      LCD.setCursor(1,0);
      LCD.print("....");
      delay(5000);
    */
  


  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("admin :");





  if (LightSensor.getValue() < 50) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }


  if (digitalRead(5) == HIGH ) {
    digitalWrite(6, HIGH);

  }
  if (digitalRead(5) == LOW ) {
    digitalWrite(6, LOW);
  }




  boolean isMessageSent = false;



  // int x=0 ;
  if (y == 0) {
    //  delay(2000);
    text2speech.say(" Welcome to voice controlled light system");
    delay(3500);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    delay(3000);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);



  }
  y = 5;

  /* Check if new command received.  ||||  */



  if ( (  VoiceRecognition.isNewCommandReceived() || SMS.isNewSms()  ) && ( strcmp(  party, SMS.getSms()) ) )
  {
    /* Compare the play command. */


    if (!strcmp( password , SMS.getSms() ) ) {
      acessnumber = SMS.getNumberAsString() ;
    }
    
    if ( ( !strcmp(removeme , SMS.getSms()  ) && acessnumber.equals(SMS.getNumberAsString() ) ) && acessnumber != "" ) {
      acessnumber = "";
    }
    
    if ( !strcmp(adminkick , SMS.getSms())  ){
      unsigned long timer = 0 ;
      timer = millis();
      while((millis() - timer ) < 10000 ) {
        digitalWrite(6,HIGH);
        if (digitalRead(5) == HIGH) {
        digitalWrite(6, LOW);
        admin = SMS.getNumberAsString()  ;
        break;
         }
      }
      
    }

    if ( ( admin.equals( SMS.getNumberAsString())  ||  acessnumber.equals( SMS.getNumberAsString()) ) ) {




      dancesms = false ;

      partystatusoff = true ;

      if (partystatusoff == true && partystarted == true)
      {
        SMS.send(acessnumber, " PARTY STOPED :'( ");
        partystarted = false ;
      }



      

     
      if (!strcmp(playCommand, VoiceRecognition.getLastCommand()) || !strcmp(playCommand, SMS.getSms()) )
      {
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(11, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(9, HIGH);
         redOn=true;
        blueOn=true;
        whiteOn=true;
        yellowOn=true;
        greenOn=true;
        text2speech.say(" Welcome to the game of lights");
        SMS.send(acessnumber, "HOME LIGHT STATUS : \n ALL LIGHTS ON");
        SMS.send(admin, "HOME LIGHT STATUS : \n ALL LIGHTS ON");
        

      }

      //     Compare the pause command.
      else if (!strcmp(pauseCommand, VoiceRecognition.getLastCommand()) || !strcmp(pauseCommand, SMS.getSms()) )
      {
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        redOn=false;
        blueOn=false;
        whiteOn=false;
        yellowOn=false;
        greenOn=false;
        SMS.send(acessnumber, "HOME LIGHT STATUS : \n ALL LIGHTS OFF");
        SMS.send(admin, "HOME LIGHT STATUS : \n ALL LIGHTS OFF");
        text2speech.say(" going to miss you ");
        delay(3000);
      }
      //     Compare the stop command.
      else if (!strcmp(redCommand, VoiceRecognition.getLastCommand())  || !strcmp(redCommand, SMS.getSms()) )
      {
          rcheck();
        /*  if( !redOn){
            digitalWrite(Rpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS ON");
              text2speech.say(" red is on ");
              delay(1500);
            redOn=true;
            }else{
              digitalWrite(Rpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS OFF");
              text2speech.say(" red is off ");
              delay(1500);              
            redOn=false;
          }
          */

      }
      //     Compare the next command.
      else if (!strcmp(yellowCommand, VoiceRecognition.getLastCommand())  || !strcmp(yellowCommand, SMS.getSms()) )
      {
            ycheck();
        /*  if( !yellowOn){
            digitalWrite(Ypin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS ON");
              text2speech.say(" yellow is on ");
              delay(1500);
            yellowOn=true;
            }else{
              digitalWrite(Ypin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS OFF");
              text2speech.say(" yellow is off ");
              delay(1500);              
            yellowOn=false;
          }
        */

      }
      else if (!strcmp(whiteCommand, VoiceRecognition.getLastCommand())  || !strcmp(whiteCommand, SMS.getSms()) )
      {

        wcheck();
     /*     if( !whiteOn){
            digitalWrite(Wpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS ON");
              text2speech.say(" WHITE is on ");
              delay(1500);
            whiteOn=true;
            }else{
              digitalWrite(Wpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS OFF");
              text2speech.say(" WHITE is off ");
              delay(1500);              
            whiteOn=false;
          }
        */
      }
      else if (!strcmp(blueCommand, VoiceRecognition.getLastCommand())  || !strcmp(blueCommand, SMS.getSms()) )
      {

            bcheck();
      /*    if( !blueOn){
            digitalWrite(Bpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS ON");
              text2speech.say(" blue is on ");
              delay(1500);
            blueOn=true;
            }else{
              digitalWrite(Bpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS OFF");
              text2speech.say(" blue is off ");
              delay(1500);              
            blueOn=false;
          }
        */
      }
      else if (!strcmp(greenCommand, VoiceRecognition.getLastCommand())  || !strcmp(greenCommand, SMS.getSms()) )
      {

              gcheck();
       /*   if( !greenOn){
            digitalWrite(Rpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS ON");
              text2speech.say(" green is on ");
              delay(1500);
            greenOn=true;
            }else{
              digitalWrite(Rpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS OFF");
              text2speech.say(" green is off ");
              delay(1500);              
            greenOn=false;
          }
      */
      }
    
  
    }
}

  

  if ((!strcmp(danceCommand, VoiceRecognition.getLastCommand())  || !strcmp(danceCommand, SMS.getSms()) )  ||  !strcmp(party, SMS.getSms()) )
  {
    if (partystatusoff == true) {
      partystatusoff = false;
      partystarted = true ;
    }
    if (dancesms == false) {
      SMS.send(acessnumber, party);
      SMS.send(admin, party);
      dancesms = true ;
    }

   
    digitalWrite(13, LOW);
    delay(300);

    digitalWrite(12, LOW);
    delay(300);
 
    digitalWrite(11, LOW);
    delay(300);

    digitalWrite(10, LOW);
    delay(300);
    digitalWrite(9, LOW);
    delay(300);


    digitalWrite(13, HIGH);
    delay(280);

    digitalWrite(12, HIGH);
    delay(280);

    digitalWrite(11, HIGH);
    delay(280);

    digitalWrite(10, HIGH);
    delay(280);

    digitalWrite(9, HIGH);
    delay(280);

  }
}



/* Error checking function. */
void error(byte errorData)
{
//   Switch on error and print it on the terminal. 
  switch (errorData)
  {
    case NETWORK_TIMEOUT_ERROR: Terminal.println("Network timeout"); break;
    case NETWORK_ERROR: Terminal.println("Network Error"); break;
    case AUDIO_ERROR: Terminal.println("Audio error"); break;
    case SERVER_ERROR: Terminal.println("No Server"); break;
    case SPEECH_TIMEOUT_ERROR: Terminal.println("Speech timeout"); break;
    case NO_MATCH_ERROR: Terminal.println("No match"); break;
    case RECOGNIZER_BUSY_ERROR: Terminal.println("Busy"); break;
  }
}

void wcheck()
{
            if( !whiteOn){
            digitalWrite(Wpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS ON");
              text2speech.say(" WHITE is on ");
              delay(1500);
            whiteOn=true;
            }else{
              digitalWrite(Wpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR WHITE IS OFF");
              text2speech.say(" WHITE is off ");
              delay(1500);              
            whiteOn=false;
          }
}

void rcheck()
{
            if( !redOn){
            digitalWrite(Rpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS ON");
              text2speech.say(" red is on ");
              delay(1500);
            redOn=true;
            }else{
              digitalWrite(Rpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR RED IS OFF");
              text2speech.say(" red is off ");
              delay(1500);              
            redOn=false;
          }
}

void ycheck()
{
          if( !yellowOn){
            digitalWrite(Ypin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS ON");
              text2speech.say(" yellow is on ");
              delay(1500);
            yellowOn=true;
            }else{
              digitalWrite(Ypin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR YELLOW IS OFF");
              text2speech.say(" yellow is off ");
              delay(1500);              
            yellowOn=false;
          }
  
}

void bcheck()
{
            if( !blueOn){
            digitalWrite(Bpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS ON");
              text2speech.say(" blue is on ");
              delay(1500);
            blueOn=true;
            }else{
              digitalWrite(Bpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR BLUE IS OFF");
              text2speech.say(" blue is off ");
              delay(1500);              
            blueOn=false;
          }

  
}

void gcheck()
{
            if( !greenOn){
            digitalWrite(Gpin,HIGH);
            delay(200);
             SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS ON");
             SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS ON");
              text2speech.say(" green is on ");
              delay(1500);
            greenOn=true;
            }else{
              digitalWrite(Gpin,LOW);
              delay(200);
              SMS.send(acessnumber, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS OFF");
              SMS.send(admin, "HOME LIGHT STATUS : \n LIGHT COLOR GREEN IS OFF");
              text2speech.say(" green is off ");
              delay(1500);              
            greenOn=false;
          }
}

/* boolean numbercheck(String newNumber)
{
  for(int i=0 ; i < 2 ; i++ )
  {
    if(newNumber.equals(homeNumbers[i]))
    {
      return true ;
    }
  }
      return false;
  
}
*/

