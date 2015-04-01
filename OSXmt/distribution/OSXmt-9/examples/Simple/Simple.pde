import com.de.kofi.osxmt.*;


HashMap<Integer, TouchPoint> touchPoints;

void setup() {
  size(400, 300);
  noCursor();

  noStroke();
  ellipseMode(CENTER);
  textAlign(CENTER);

  //println(OSXmt.getDeviceList());
  //OSXmt.init(this, OSXmt.getDeviceList()[1], true, true);
  OSXmt.init(this, 0, true, true);
}

void draw() {
  background(0);

  if (touchPoints != null) {
    Integer[] tids = touchPoints.keySet().toArray(new Integer[touchPoints.size()]);
    for (Integer tid:tids) {
      TouchPoint touchPoint = touchPoints.get(tid);
      if (touchPoint != null) {
        float x = touchPoint.getX()*width;
        float y = touchPoint.getY()*height;
        float w = touchPoint.getTouchPointMinorAxis()*4;
        float h = touchPoint.getTouchPointMajorAxis()*4;
        fill(255);
        ellipse(x, y, w, h);
        
        fill(64);
        text(touchPoint.getId(), x, y+5);
      }
    }
  }
}

void mtEvent(HashMap<Integer, TouchPoint> _touchPoints) {
  touchPoints = _touchPoints;
}
