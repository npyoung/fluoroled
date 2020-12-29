const int led = 9;
const int potentiometer = A0;
const int dimmerLow = 0.05 * 1023;
const int dimmerHigh = 0.95 * 1023;
const float tauOn = 0.02;
const float tauOff = 0.5;
const float spikeSlow = 0.5;
const float spikeFast = 10.0;
a
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
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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
    
    if (randUniform(1000) < spikeRate * dt) {
      brightness += (1.0 - brightness) / tauOn * dt;
    }
    
    brightness -= brightness / tauOff * dt;
  }
  
  
  
  analogWrite(led, (int) (brightness * 255));
}
