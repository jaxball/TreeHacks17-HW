#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include "Esp8266AWSImplementations.h"
#include "keys.h"

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WAP
  Serial.print("Connecting to ");
  Serial.println(wifiSsid);
  WiFi.begin(wifiSsid, wifiPwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  iotClient.setAWSRegion("us-west-2");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("dynamodb.us-west-2.amazonaws.com");
  iotClient.setAWSPath("my-things/text/shadow");
  iotClient.setAWSKeyID(awsKeyID);
  iotClient.setAWSSecretKey(awsSecKey);
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void loop(){
  char* shadow = "{\"state\":{\"reported\": {\"foobar\": bar""}}";

  char* result = iotClient.update_shadow(shadow, actionError);
  Serial.print(result);

  delay(60000);
}
