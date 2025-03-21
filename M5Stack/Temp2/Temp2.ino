#include <ArduinoJson.h>
#include <driver/i2s.h>
#include <M5Atom.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <base64.h>

// const char *WifiSSID = "ChinaNet-3F2AAF";
// const char *WifiPWD  = "hkfx3394";
const char *WifiSSID = "TP-LINK_7955";
const char *WifiPWD  = "15080122376";
const char* url = "http://117.50.173.6:5000/web_interaction";
const char* userId = "18602860044";
const char* userName = "Sibo";
const char* roleName = "Jifeifei";
const char* languageMode = "ZH";
const bool soulModeToggle = true;

#define JSON_DOCSIZE 512
StaticJsonDocument<JSON_DOCSIZE> rest_json_doc;

#define CONFIG_I2S_BCK_PIN     19
#define CONFIG_I2S_LRCK_PIN    33
#define CONFIG_I2S_DATA_PIN    22
#define CONFIG_I2S_DATA_IN_PIN 23

#define SPEAKER_I2S_NUMBER I2S_NUM_0

#define MODE_MIC  0
#define MODE_SPK  1
#define DATA_SIZE 1024

uint8_t microphonedata0[1024 * 70];
size_t byte_read = 0;
int16_t *buffptr;
uint32_t data_offset = 0;

void InitI2SSpeakerOrMic(int mode) {
    esp_err_t err = ESP_OK;

    i2s_driver_uninstall(SPEAKER_I2S_NUMBER);
    i2s_config_t i2s_config = {
        .mode        = (i2s_mode_t)(I2S_MODE_MASTER),
        .sample_rate = 16000,
        .bits_per_sample =
            I2S_BITS_PER_SAMPLE_16BIT,  // is fixed at 12bit, stereo, MSB
        .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
#if ESP_IDF_VERSION > ESP_IDF_VERSION_VAL(4, 1, 0)
        .communication_format =
            I2S_COMM_FORMAT_STAND_I2S,  // Set the format of the communication.
#else                                   // 设置通讯格式
        .communication_format = I2S_COMM_FORMAT_I2S,
#endif
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count    = 6,
        .dma_buf_len      = 60,
    };
    if (mode == MODE_MIC) {
        i2s_config.mode =
            (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM);
    } else {
        i2s_config.mode     = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
        i2s_config.use_apll = false;
        i2s_config.tx_desc_auto_clear = true;
    }

    err += i2s_driver_install(SPEAKER_I2S_NUMBER, &i2s_config, 0, NULL);
    i2s_pin_config_t tx_pin_config;

#if (ESP_IDF_VERSION > ESP_IDF_VERSION_VAL(4, 3, 0))
    tx_pin_config.mck_io_num = I2S_PIN_NO_CHANGE;
#endif
    tx_pin_config.bck_io_num   = CONFIG_I2S_BCK_PIN;
    tx_pin_config.ws_io_num    = CONFIG_I2S_LRCK_PIN;
    tx_pin_config.data_out_num = CONFIG_I2S_DATA_PIN;
    tx_pin_config.data_in_num  = CONFIG_I2S_DATA_IN_PIN;

    // Serial.println("Init i2s_set_pin");
    err += i2s_set_pin(SPEAKER_I2S_NUMBER, &tx_pin_config);
    // Serial.println("Init i2s_set_clk");
    err += i2s_set_clk(SPEAKER_I2S_NUMBER, 16000, I2S_BITS_PER_SAMPLE_16BIT,
                       I2S_CHANNEL_MONO);
}

void setup() {
    // put your setup code here, to run once:
    M5.begin(true, false, true);
    M5.dis.clear();

    Serial.println("Init......");
    M5.dis.drawpix(0, CRGB(128, 128, 0));
    delay(200);

    Serial.println("Connecting WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.begin(WifiSSID, WifiPWD);

    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print('.');
    }

    Serial.println("Connected!");

}

void loop() {
  // put your main code here, to run repeatedly:
    if(M5.Btn.isPressed()){
        data_offset = 0;
        InitI2SSpeakerOrMic(MODE_MIC);
        M5.dis.drawpix(0, CRGB(128, 128, 0));
        size_t byte_read;

        while(1){
              i2s_read(SPEAKER_I2S_NUMBER,
                     (char *)(microphonedata0 + data_offset), DATA_SIZE,
                     &byte_read, (100 / portTICK_RATE_MS));
              data_offset += 1024;
              M5.update();
              if (M5.Btn.isReleased() || data_offset >= 81919) break;
              // delay(60);
        }
        Serial.println("end speak");

        size_t bytes_written;
        InitI2SSpeakerOrMic(MODE_SPK);
        i2s_write(SPEAKER_I2S_NUMBER, microphonedata0, data_offset,
                  &bytes_written, portMAX_DELAY);
        
        // String(microphonedata0);
        // String micro_base64 = base64::encode(microphonedata0);

        //send to llm
        HTTPClient http;
        // String apiurl = "http://";
        // apiurl.concat(url);
        // apiurl.concat('?');
        // apiurl.concat("user_id=18602860044");
        // apiurl.concat('&');
        // apiurl.concat("user_name=Sibo");
        // apiurl.concat('&');
        // apiurl.concat("role_name=Jifeifei");
        // apiurl.concat('&');
        // apiurl.concat("language_mode=ZH");
        // apiurl.concat('&');
        // apiurl.concat("soul_mode_toggle=True");
        // apiurl.concat('&');
        // apiurl.concat("introQuestion= ");

        http.begin(url); // 准备启用连接
        http.addHeader("Content-Type", "application/json");
        // String requestData = "user_id=" + String(userId) + "&" +"user_name=" + String(userName) + "role_name=" + String(roleName) +
        //                 "&" + "language_mode=" + String(languageMode) + "&" + "soul_mode_toggle=" + String(soulModeToggle) +
        //                 "&" + "input=" + String(microphonedata0) + "&" + "introQuestion=";

        // String requestData = String("{\"user_id\": \"18602860044\", \"user_name\": \"Sibo\", \"role_name\": \"Jifeifei\", \"language_mode\": \"ZH\", \"soul_mode_toggle\": \"True\", \"input\": \") + micro_base64 + String(\", \"introQuestion\": \"\"}");
        String requestData = String("{\"user_id\": \"18602860044\", \"user_name\": \"Sibo\", \"role_name\": \"Jifeifei\", \"language_mode\": \"ZH\", \"soul_mode_toggle\": \"True\", \"input\": \") + String(microphonedata0) + String(\", \"introQuestion\": \"\"}");



        int code = http.POST(requestData);
        Serial.print(code);
        String response = http.getString();
        // Serial.print('1');
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
        
        http.end();
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wifi reconnect");
        WiFi.reconnect();
        while (WiFi.status() != WL_CONNECTED) {
            delay(100);
        }
    }
    M5.update();
    delay(100);
}
