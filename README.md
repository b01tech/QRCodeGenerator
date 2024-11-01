# QR Code Display on TFT with Arduino Nano (ATmega328)

Este projeto utiliza um Arduino Nano para exibir QR codes em uma tela TFT ST7735. Os dados de peso são recebidos pela porta serial, processados e exibidos no formato QR code na tela.

## Visão Geral do Projeto

O programa lê dados de peso via comunicação serial, formata os dados, e os exibe em forma de QR code em uma tela TFT ST7735. 
Este código utiliza a biblioteca `Adafruit GFX`, `Adafruit ST7735`, e `QRCode` para renderização e criação do QR code.

### Hardware Utilizado

- **Arduino Nano** (ATmega328)
- **Tela TFT ST7735**
  - Conexões:
    - MOSI: Pino 11
    - SCLK: Pino 13
    - CS: Pino 10
    - DC: Pino 8
    - RST: Pino 9

### Funcionamento do Projeto

1. **Leitura da Porta Serial**: O Arduino lê uma string que contém o peso e o delimita com `0x0D`.
2. **Formatação do Peso**: A string é formatada e preparada para exibição no formato `parceltool`.
3. **Geração do QR Code**: O QR code é gerado com os dados formatados.
4. **Exibição na Tela TFT**: O QR code é renderizado na tela TFT.

## Configuração e Instalação

### Dependências

Este projeto utiliza PlatformIO para gerenciamento de bibliotecas e configuração de ambiente. 
As bibliotecas necessárias são:

- [Adafruit GFX Library](https://platformio.org/lib/show/13/Adafruit%20GFX%20Library) (v1.11.11)
- [Adafruit ST7735 and ST7789 Library](https://platformio.org/lib/show/19/Adafruit%20ST7735%20and%20ST7789%20Library) (v1.10.4)
- [QRCode](https://platformio.org/lib/show/5628/QRCode) (v0.0.1)

### Instalação

1. Clone o repositório:
   ```bash
   git clone https://github.com/seu_usuario/nome_do_projeto.git
Abra o projeto no PlatformIO.
Conecte seu Arduino Nano ao computador.
Compile e faça o upload do código.

### Arquivo de Configuração (PlatformIO)

O arquivo platformio.ini contém as configurações necessárias para o projeto.
