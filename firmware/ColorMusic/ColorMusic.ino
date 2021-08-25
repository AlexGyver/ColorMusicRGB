#include <GRGB.h>
GRGB led(COMMON_CATHODE, 9, 10, 11);  // RGB на пинах D9,D10,D11

#include "VolAnalyzer.h"
VolAnalyzer analyzer(A7);   // вход звука на А7

#include <EncButton.h>
EncButton<EB_TICK, 3> btn;  // кнопка на D3

void setup() {
  //Serial.begin(9600);
  analogReference(EXTERNAL);  // внешнее опорное

  // разгоняем ШИМ чтобы не стробило на камеру
  // Пины D3 и D11 - 8 кГц
  TCCR2B = 0b00000010;  // x8
  TCCR2A = 0b00000011;  // fast pwm
  
  // Пины D9 и D10 - 7.8 кГц
  TCCR1A = 0b00000001;  // 8bit
  TCCR1B = 0b00001010;  // x8 fast pwm

  analyzer.setVolK(25);     // плавность громкости (0-31)
  analyzer.setTrsh(50);     // порог тишины
  analyzer.setVolMin(10);   // мин. громкость 10
  analyzer.setVolMax(255);  // макс. громкость 255

  analyzer.setPulseTrsh(200);     // верхний порог пульса
  analyzer.setPulseMin(80);       // нижний порог пульса
  analyzer.setPulseTimeout(200);  // таймаут пульсов
}

void loop() {
  // опрос кнопки, смена режимов по клику
  btn.tick();
  static byte mode = 0;
  if (btn.isClick()) {
    if (++mode >= 4) mode = 0;
  }

  // анализ звука
  if (analyzer.tick()) {    
    static byte color = 0;

    // эффекты
    switch (mode) {
      case 0:
        if (analyzer.getPulse()) color += 151;
        led.setWheel8(color, analyzer.getVol());
        break;
      case 1:
        if (analyzer.getPulse()) color += 129;
        led.setWheel8(color, analyzer.getVol());
        break;
      case 2:
        led.setWheel8(color++, analyzer.getVol());
        break;
      case 3:
        led.setHSVfast((analyzer.getVol() - 10) / 6, 255, analyzer.getVol());
        break;
    }

    // дебаг
    //Serial.println(analyzer.getVol());
    /*Serial.print(analyzer.getVol());
    Serial.print(',');
    Serial.print(analyzer.getRaw());
    Serial.print(',');
    Serial.print(analyzer.getMin());
    Serial.print(',');
    Serial.println(analyzer.getMax());*/
  }
}
