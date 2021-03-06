// Пример с прямой работой библиотеки

// Опциональные дефайн-настройки (показаны по умолчанию)
//#define EB_FAST 30     // таймаут быстрого поворота, мс
//#define EB_DEB 80      // дебаунс кнопки, мс
//#define EB_HOLD 1000   // таймаут удержания кнопки, мс
//#define EB_STEP 500    // период срабатывания степ, мс
//#define EB_CLICK 400   // таймаут накликивания, мс

// подключение - только PULL-UP, внешний или внутренний!
// для изменения направления энкодера поменяй A и B при инициализации

#include <EncButton.h>
EncButton<EB_TICK, 2, 3, 4> enc;  // энкодер с кнопкой <A, B, KEY>
//EncButton<EB_TICK, 2, 3> enc;     // просто энкодер <A, B>
//EncButton<EB_TICK, 4> enc;        // просто кнопка <KEY>

// по умолчанию пины настроены в INPUT_PULLUP
// Если используется внешняя подтяжка - лучше перевести в INPUT
//EncButton<EB_TICK, 2, 3, 4> enc(INPUT);

void setup() {
  Serial.begin(9600);
  enc.counter = 100;      // изменение счётчика
  //enc.setHoldTimeout(500);  // установка таймаута удержания кнопки
}

void loop() {
  enc.tick();

  if (enc.isTurn()) {               // любой поворот
    Serial.print("turn ");
    Serial.println(enc.counter);    // вывод счётчика
  }

  if (enc.isLeft()) {
    if (enc.isFast()) Serial.println("fast left");
    else Serial.println("left");
  }

  if (enc.isRight()) {
    if (enc.isFast()) Serial.println("fast right");
    else Serial.println("right");
  }

  if (enc.isLeftH()) Serial.println("leftH");
  if (enc.isRightH()) Serial.println("rightH");
  if (enc.isClick()) Serial.println("click");
  if (enc.isHolded()) Serial.println("holded");
  if (enc.isStep()) Serial.println("step");

  if (enc.isPress()) Serial.println("press");
  if (enc.isClick()) Serial.println("click");
  if (enc.isRelease()) Serial.println("release");

  if (enc.hasClicks(1)) Serial.println("1 click");
  if (enc.hasClicks(2)) Serial.println("2 click");
  if (enc.hasClicks(3)) Serial.println("3 click");
  if (enc.hasClicks(5)) Serial.println("5 click");

  if (enc.hasClicks()) Serial.println(enc.clicks);
  //if (enc.isHold()) Serial.println("hold");
}
