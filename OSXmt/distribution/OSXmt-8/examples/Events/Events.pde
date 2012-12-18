import com.de.kofi.osxmt.*;


float rotation;

void setup() {
  size(400, 400);
  noCursor();
  
  rectMode(CENTER);

  println(OSXmt.getDeviceList());
  OSXmt.init(this, OSXmt.getDeviceList()[0], true, true);
}

void draw() {
  background(0);
  translate(width/2, height/2);
  rotate(rotation);
  rect(0, 0, 200, 200);
}

void mtEvent(HashMap<Integer, TouchPoint> touches) {
}

void mtPress(int id, PVector pos, HashMap<Integer, TouchPoint> touches) {
  println(id + ": press");
}

void mtRelease(int id, PVector pos, HashMap<Integer, TouchPoint> touches) {
  println(id + ": release");	
}

void mtDrag(int id, PVector delta, HashMap<Integer, TouchPoint> touches) {
  println(id + ": drag");
  TouchPoint tP = touches.get(id);
  if (tP.getStartDir().mag() > .05)
    rotation = tP.getStartDirAngle();
}

void mtScroll(int id, ScrollDirection state, float delta, HashMap<Integer, TouchPoint> touches) {
  println(id + ": scroll " + state);
}

void mtTap(int id, PVector pos, HashMap<Integer, TouchPoint> touches) {
  println(id + ": tap");
}

void mtLongPress(int id, PVector pos, HashMap<Integer, TouchPoint> touches) {
  println(id + ": long press");
}

