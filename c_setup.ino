void setup()
{
  pinMode(8, INPUT); //ppm input

  setup_timer1();

  Serial.begin(9600);  // RDF was 115200
}
