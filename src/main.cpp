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

Adafruit_ST7735 displayTFT = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void showQRCode(const char *peso)
{
  displayTFT.fillScreen(ST77XX_WHITE); // Fundo branco

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

String get_peso(String pesoCoded)
{
  String pesoTemp = "";
  for (int i = 0; i < pesoCoded.length(); i++)
  {
    char caractere = pesoCoded.charAt(i);
    if (caractere != ';')
    {
      pesoTemp += caractere;
    }
  }
  String peso = pesoTemp.substring(1, 8);
  return peso;
}

String cal_parceltool(String peso)
{
  String data = "N+";
  data += peso;
  data += String(char(0x0D));
  data.replace('.', ','); // substituir ponto por virgula
  return data;
}

String stProtocol_to_parcel()
{
  String pesoCoded = Serial.readStringUntil(0x0D);
  String peso = get_peso(pesoCoded);
  String parceltool = cal_parceltool(peso);
  return parceltool;
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
    String valor = stProtocol_to_parcel();
    showQRCode(valor.c_str());
  }
}
