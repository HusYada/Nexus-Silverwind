class collision {
	public:
	bool overlap(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {  
	if (x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2) { return true; }
	else { return false; }
	}
	int distx(int x1, int x2) {
	int d = bn::abs((x2-x1)^2);
	return d;
	}
	// LINE/LINE by Jeffrey Thompson
	// https://www.jeffreythompson.org/collision-detection/line-line.php
	bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
  	// calculate the distance to intersection point
  	float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  	float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  	// if uA and uB are between 0-1, lines are colliding
  	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) { return true; } return false; }
  	// LINE/RECTANGLE by Jeffrey Thompson
  	// https://www.jeffreythompson.org/collision-detection/line-rect.php
	bool lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {
	  // check if the line has hit any of the rectangle's sides
	  bool left =   lineLine(x1,y1,x2,y2, rx,ry,rx, ry+rh);
	  bool right =  lineLine(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
	  bool top =    lineLine(x1,y1,x2,y2, rx,ry, rx+rw,ry);
	  bool bottom = lineLine(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);
	  // if ANY of the above are true, the line
	  // has hit the rectangle
	  if (left || right || top || bottom) { return true; } return false; }
};