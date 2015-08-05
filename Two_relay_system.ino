// Relay system
//
// It allows for relay interaction in the case whereby 2 or more relay sets are present.
// The relays have to be assigned in a systematic order to make full use of this code.
//
// By: Bryan Wong
// Date: 4/8/2015

String instruction = "";
// Number of relay slots in the first relay set
int firstRelaySlots = 8;
int numberOfRelays = 13;

void setup() {
  Serial.begin(9600);
  for (int i = numberOfRelays; i < numberOfRelays + 1; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  char input = Serial.read();
  instruction.concat(input);
  
  // Assigns right pin in the String instructions
  instruction = identify(instruction);
  
  // ON or OFF the right relays or use the OFF command
  if (instruction.length() == 5){
    relaySetOne(instruction);
  }
  if (instruction == "OFF"){
  for (int i = numberOfRelays; i < numberOfRelays + 1; i++){
    digitalWrite(i, LOW);
    }
  }
  
}

String identify(String instruction){
  // If the target is relay set 2, configure the pin number to the right one 
  if (instruction.substring(1,1) == "2"){
    int relaySwitch = instruction.substring(1,1).toInt() + firstRelaySlots;
    instruction = instruction.substring(0,3) + String(relaySwitch);
  }
  return instruction;
}

String relaySetOne(String instruction){
  // The instructions should be in the form RX_XX
  // Where by X is the number set for the relay and identity\
  int relaySwitch;
  String info = instruction.substring(3);
/////////////////////////////////////////////////////////////////////////////
  // Finds the identity of the relay
  if (info.substring(3,3) != "0" || info.substring(4,4)!= "0"){
    relaySwitch = info.toInt();
  }
  
  else if (info.substring(4,4) != 0){
    info = info.substring(1);
    relaySwitch = info.toInt();
  }
  else{
    return "ERROR";
  }
/////////////////////////////////////////////////////////////////////////////
  // On and off switch based on current status of relaySwitch
  if (digitalRead(relaySwitch) == LOW){
      digitalWrite(relaySwitch,HIGH);
  }
  else{
      digitalWrite(relaySwitch,LOW);
  }
}

