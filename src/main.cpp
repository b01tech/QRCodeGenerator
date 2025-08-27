#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <qrcode.h>

#define TFT_MOSI 11
#define TFT_SCLK 13
#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9
#define TAMANHO_QRCODE 100
#define QRCODE_VERSION 3

Adafruit_ST7735 displayTFT = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void showQRCode(const char *peso)
{
  displayTFT.fillScreen(ST77XX_WHITE); 

  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  QRCode qrcode;

  qrcode_initText(&qrcode, qrcodeData, 3, 0, peso);

  int tamanhoQrcode = TAMANHO_QRCODE / qrcode.size;

  for (int y = 0; y < qrcode.size; y++)
  {
    for (int x = 0; x < qrcode.size; x++)
    {
      if (qrcode_getModule(&qrcode, x, y))
      {
        displayTFT.fillRect(x * tamanhoQrcode + 20, y * tamanhoQrcode + 20, tamanhoQrcode, tamanhoQrcode, ST77XX_BLACK); // Módulos do QR Code em preto
      }
      else
      {
        displayTFT.fillRect(x * tamanhoQrcode + 20, y * tamanhoQrcode + 20, tamanhoQrcode, tamanhoQrcode, ST77XX_WHITE); // Espaços vazios em branco
      }
    }
  }
}

String getValue()
{
  String data = Serial.readStringUntil('\r'); 
  if (data.length() >= 8) 
  {
    String value = data.substring(1, 8); 
    value.replace('.', ','); 
    return value;
  }
  return ""; 
}

void setup()
{
  Serial.begin(9600);
  displayTFT.initR(INITR_REDTAB);
  displayTFT.setRotation(1);
  displayTFT.fillScreen(ST77XX_BLACK);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String data = getValue();
    showQRCode(data.c_str());
  }
}
