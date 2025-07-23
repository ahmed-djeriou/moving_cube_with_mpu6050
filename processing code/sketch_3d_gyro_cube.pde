import processing.opengl.*;
import processing.serial.*;
Serial Port;


float[] vals = new float[4]; //array of values

void setup() {
  frameRate(60);
  size (700, 700, P3D);
  stroke(1);
  String portN = Serial.list()[0];
  Port = new Serial(this, portN, 115200);
  Port.bufferUntil('\n');
}
void draw() {

  background(255, 185, 99);
  lights();
  pushMatrix();
  translate(350, 350);
  Rotation();
  box(100, 100, 100);
  popMatrix();
}
void Rotation() {
  
  float angle = 2 * acos(vals[0]);
  float x = vals[1] / sqrt(1-vals[0]*vals[0]);
  float y = vals[2] / sqrt(1-vals[0]*vals[0]);
  float z = vals[3] / sqrt(1-vals[0]*vals[0]);
  
  
  rotate(angle, -x, y, z); 
}
void serialEvent(Serial Port) {
  String data =Port.readString().trim();
  if(data != null && data.startsWith("A")){
    String[] val = split(data.substring(1), ",");
     if (val.length == 4) {
      vals[0] = float(val[0]); // w
      vals[1] = float(val[1]); // x
      vals[2] = float(val[2]); // y
      vals[3] = float(val[3]); // z
    }
  
  
  }
}
