void turnOnFans(FAN_PINS fan_pins) {
    analogWrite(fan_pins.CONTROL, 255);
    analogWrite(fan_pins.LED, 255);
}

void turnOffFans(FAN_PINS fan_pins) {
    analogWrite(fan_pins.CONTROL, 0);
    analogWrite(fan_pins.LED, 0);
}