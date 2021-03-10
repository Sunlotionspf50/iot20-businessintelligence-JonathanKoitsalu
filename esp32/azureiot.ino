void initDevice(){
  deviceClient = IoTHubClient_LL_CreateFromConnectionString(conn, MQTT_Protocol);

}

void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void *userContextCallback) {
  if(IOTHUB_CLIENT_CONFIRMATION_OK == result) {
    Serial.println("Message sent to Azure Iot Hub - successful");
  }
  messagePending = false; //Väntar på callback för att nollställa messagePending
}

void sendMessage(char *payload){ //payload är meddelandet som ska skickas.
  IOTHUB_MESSAGE_HANDLE message = IoTHubMessage_CreateFromByteArray((const unsigned char *) payload, strlen(payload));

  if(IoTHubClient_LL_SendEventAsync(deviceClient, message, sendCallback, NULL) == IOTHUB_CLIENT_OK) {
    messagePending = true;
  }

  IoTHubMessage_Destroy(message);
}
