#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "ChinaNet-3F2AAF";    //你的网络名称
const char *password = "hkfx3394"; //你的网络密码

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
#define JSON_DOCSIZE 512
StaticJsonDocument<JSON_DOCSIZE> rest_json_doc;
const char* url = "http://117.50.173.6:5000/web_interaction";
const char* userId = "18602860044";
const char* userName = "Sibo";
const char* roleName = "Jifeifei";
const char* languageMode = "ZH";
const bool soulModeToggle = true;

void loop()
{
  HTTPClient http; // 声明HTTPClient对象
  // curl -X POST -H "Content-Type: application/json"  
  // -d "{\"user_id\": \"18602860044\", \"user_name\": \"Sibo\", \"role_name\": \"Jifeifei\", 
  // \"language_mode\": \"ZH\", \"soul_mode_toggle\": \"True\", 
  // \"input\": \"你好呀鸡 飞飞，可以介绍一下你自己吗？\", \"introQuestion\": \"\"} " 
  // http://117.50.173.6:5000/web_interaction

  // url.concat('?');
  // url.concat("user_id=18602860044");
  // url.concat('&');
  // url.concat("user_name=Sibo");
  // url.concat('&');
  // url.concat("role_name=Jifeifei");
  // url.concat('&');
  // url.concat("language_mode=ZH");
  // url.concat('&');
  // url.concat("soul_mode_toggle=True");
  // url.concat('&');
  // url.concat("input=你好呀鸡 飞飞，可以介绍一下你自己吗？");
  // url.concat('&');
  // url.concat("introQuestion= ");
  // Serial.println(url);
  String input = "Hello, who are you?";

  http.begin(url); // 准备启用连接
  http.addHeader("Content-Type", "application/json");

  // String requestData = "user_id=" + String(userId) + "&" +"user_name=" + String(userName) + "role_name=" + String(roleName) +
  //                       "&" + "language_mode=" + String(languageMode) + "&" + "soul_mode_toggle=" + String(soulModeToggle) +
  //                       "&" + "input=" + input + "&" + "introQuestion=";
  String requestData = String("{\"user_id\": \"18602860044\", \"user_name\": \"Sibo\", \"role_name\": \"Jifeifei\", \"language_mode\": \"ZH\", \"soul_mode_toggle\": \"True\", \"input\": \"你好呀鸡飞飞，可以介绍一下你自己吗？\", \"introQuestion\": \"\"}");

  int code = http.POST(requestData);
  Serial.print(code);

  String response = http.getString();
  Serial.print('1');
  Serial.println(response);

  deserializeJson(rest_json_doc, response);

  String err_msg = rest_json_doc["err_msg"].as<String>();

  if (err_msg.indexOf("success") != -1) {
      JsonArray result = rest_json_doc["result"].as<JsonArray>();
      if (result.isNull()) {
         Serial.print('2');
          Serial.println("isempty");
      }
      Serial.print('3');
      Serial.println(result[0].as<String>());
  } else {
      Serial.print('4');
      Serial.println(err_msg);
  }


  // int httpCode = http.GET(); // 发起GET请求
  // Serial.print(httpCode);



  http.end(); // 结束当前连接

  delay(10000);
}
