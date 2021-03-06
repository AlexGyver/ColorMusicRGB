// Пример с обработчиками

// Опциональные дефайн-настройки (показаны по умолчанию)
//#define EB_FAST 30     // таймаут быстрого поворота, мс
//#define EB_DEB 80      // дебаунс кнопки, мс
//#define EB_HOLD 1000   // таймаут удержания кнопки, мс
//#define EB_STEP 500    // период срабатывания степ, мс
//#define EB_CLICK 400   // таймаут накликивания, мс

// подключение - только PULL-UP, внешний или внутренний!
// для изменения направления энкодера поменяй A и B при инициализации

#include <EncButton.h>
EncButton<EB_CALLBACK, 2, 3, 4> enc;   // энкодер с кнопкой <A, B, KEY>
//EncButton<EB_CALLBACK, 2, 3> enc;    // просто энкодер <A, B>
//EncButton<EB_CALLBACK, 4> enc;       // просто кнопка <KEY>

// по умолчанию пины настроены в INPUT_PULLUP
// Если используется внешняя подтяжка - лучше перевести в INPUT
//EncButton<EB_CALLBACK, 2, 3, 4> enc(INPUT);

void setup() {
  Serial.begin(9600);
  enc.counter = 100;      // изменение счётчика
  //enc.setHoldTimeout(500);  // установка таймаута удержания кнопки
  
  enc.attach(TURN_HANDLER, myTurn);
  enc.attach(RIGHT_HANDLER, myRight);
  enc.attach(CLICK_HANDLER, myClick);
  enc.attach(HOLDED_HANDLER, myHolded);
  enc.attach(STEP_HANDLER, myStep);
  enc.attach(CLICKS_HANDLER, myClicks);
  enc.attachClicks(5, fiveClicks);
}

void myTurn() {
  Serial.print("turn ");
  Serial.println(enc.counter);    // вывод счётчика

  // также можно опросить здесь (isRight, isLeft, isRightH, isLeftH)
  if (enc.isLeft()) {
    if (enc.isFast()) Serial.println("fast left");
    else Serial.println("left");
  }
  if (enc.isLeftH()) {
    if (enc.isFast()) Serial.println("fast left hold");
    else Serial.println("left");
  }
}

void myRight() {
  if (enc.isFast()) Serial.println("fast right");
  else Serial.println("right");
}

void myClick() {
  Serial.println("click");
}
void myHolded() {
  Serial.println("holded");
}
void myStep() {
  Serial.println("step");
}
void myClicks() {
  Serial.println(enc.clicks);
}
void fiveClicks() {
  Serial.println("kek");
}

void loop() {
  enc.tick();   // обработка всё равно здесь
}
