const int led = 9;                  // LED pwm pin
const int potentiometer = A0;       // Potentiometer analog in pin
const int dimmerLow = 0.05 * 1023;  // "off" potentiometer level
const int dimmerHigh = 0.95 * 1023; // "always on" potentiometer level
const float tauOn = 0.02;           // on time constant (ms)
const float tauOff = 0.5;           // off time constant (ms)
const float spikeSlow = 0.5;        // lowest spike rate (1/s)
const float spikeFast = 10.0;       // highest spike rate (1/s)

int dimmerRaw = 0;
int t0 = millis();
int t1 = 0;
float dt = 0;
float brightness = 1.0;
float spikeRate = 0.0;

float randUniform(float resolution) {
  // get a random float between 0 and 1.0
  int x = random(resolution);
  return (float) x / resolution;
}

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  // get time since last update
  t1 = millis();
  dt = (float) (t1 - t0) / 1000;
  t0 = t1;

  dimmerRaw = analogRead(potentiometer);

  if (dimmerRaw > dimmerHigh) {
    brightness = 1.0;
    
  } else if (dimmerRaw < dimmerLow) {
    brightness = 0.0;
    
  } else {
    spikeRate = map(dimmerRaw, dimmerLow, dimmerHigh, spikeSlow, spikeFast);

    // take an Euler step
    if (randUniform(1000) < spikeRate * dt) {
      brightness += (1.0 - brightness) / tauOn * dt;
    }
    
    brightness -= brightness / tauOff * dt;
  }
  
  analogWrite(led, (int) (brightness * 255));
}
