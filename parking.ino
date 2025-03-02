#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 6
#define LED_PIN 5

long duration;
int distance;
int grade;

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // Send ultrasonic pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo response
    duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout for long distances
    distance = duration * 0.034 / 2; // Convert to cm

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm  ->  ");

    // Assign grades based on 40 cm intervals (10 grades, 0-400 cm)
    grade = constrain((distance / 40) + 1, 1, 10);

    Serial.print("Grade: ");
    Serial.println(grade);

    // Set beep & blink speed based on grade (closer = faster)
    int beepSpeed = map(grade, 1, 10, 100, 1000); // Adjust timing
    beepSpeed = constrain(beepSpeed, 100, 1000);

    // Beep and Blink synchronized
    digitalWrite(LED_PIN, HIGH);  // LED ON
    tone(BUZZER_PIN, 1000);       // Buzzer ON
    delay(100);                   // Short beep duration

    digitalWrite(LED_PIN, LOW);   // LED OFF
    noTone(BUZZER_PIN);           // Buzzer OFF
    delay(beepSpeed);             // Pause before next beep/blink
}