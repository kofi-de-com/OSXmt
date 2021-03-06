//  Copyright 2009 Wayne Keenan
//  Copyright ##copyright## ##author##
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  This is a MODIFIED version of Finger.java
//  Created by Wayne Keenan on 30/05/2009.
//  wayne.keenan@gmail.com
//
//	added scroll dir calculation and changed function names
//

package com.de.kofi.osxmt;

import processing.core.PVector;

public class TouchPoint {
	private int frame, id;
	private float touchPointSize, x, y, xStart, yStart, startDirX, startDirY, vx, vy, dx, dy, absMovementX = 0, absMovementY = 0, lerpDirX, lerpDirY, touchPointAngle, touchPointMajorAxis, touchPointMinorAxis;
	private PointState state;
	private long timestamp, startTimestamp;
	private boolean longPress;
	private ScrollDirection scrollState = ScrollDirection.UNDEFINED;


	public TouchPoint(int _frame, double _timestamp, int _id, int _state, float _touchPointSize, float _x, float _y, float _vx, float _vy, float _touchPointAngle, float _touchPointMajorAxis, float _touchPointMinorAxis) {
		this(_frame, (long) (_timestamp*1000), _id, PointState.getFromInt(_state), _touchPointSize, _x, _y, _vx, _vy, _touchPointAngle, _touchPointMajorAxis, _touchPointMinorAxis);
	}
	
	public TouchPoint(int _frame, long _timestamp, int _id, PointState _state, float _touchPointSize, float _x, float _y, float _vx, float _vy, float _touchPointAngle, float _touchPointMajorAxis, float _touchPointMinorAxis) {
		frame = _frame;
		startTimestamp = timestamp = _timestamp;
		state = _state;
		id = _id;
		x = xStart = _x;
		y = yStart = 1-_y;
		vx = _vx;
		vy = -_vy;
		touchPointSize = _touchPointSize;
		touchPointAngle = _touchPointAngle;
		touchPointMajorAxis = _touchPointMajorAxis;
		touchPointMinorAxis = _touchPointMinorAxis;	
	}

	public void update(TouchPoint tp) {
		lerpDirX = lerpDirX * .95f + (tp.getX()-x) * .05f;
		lerpDirY = lerpDirY * .95f + (tp.getY()-y) * .05f;

		frame = tp.getFrame();
		timestamp = tp.getTimestamp();
		id = tp.getId();
		
		state = tp.getState();

		if(state != PointState.RELEASED) {
			dx = tp.getX()-x;
			dy = tp.getY()-y;
			vx = tp.getVelocityX();
			vy = tp.getVelocityY();
		}

		x = tp.getX();
		y = tp.getY();
		startDirX = x-xStart;
		startDirY = y-yStart;
		
		absMovementX += Math.abs(dx);
		absMovementY += Math.abs(dy);

		touchPointSize = tp.getTouchPointSize();
		touchPointAngle = tp.getTouchPointAngle();
		touchPointMajorAxis = tp.getTouchPointMajorAxis();
		touchPointMinorAxis = tp.getTouchPointMinorAxis();
	}

	public int getFrame() {
		return frame;
	}

	public int getId() {
		return id;
	}

	public PointState getState() {
		return state;
	}

	public void setScrollState(ScrollDirection state) {
		scrollState = state;
	}

	public ScrollDirection getScrollState() {
		return scrollState;
	}

	public void setLongPress() {
		longPress = true;
	}

	public boolean isLongPress() {
		return longPress;
	}

	public long getTimestamp() {
		return timestamp;
	}

	public long getLifetime() {
		return timestamp-startTimestamp;
	}

	public float getX() {
		return x;
	}

	public float getY() {
		return y;
	}

	public float getDX() {
		return dx;
	}

	public float getDY() {
		return dy;
	}

	public float getVelocityX() {
		return vx;
	}

	public float getVelocityY() {
		return vy;
	}

	public float getStartDirX() {
		return startDirX;
	}

	public float getStartDirY() {
		return startDirY;
	}

	public PVector getStartDir() {
		return new PVector(startDirX, startDirY);
	}

	public float getStartDirAngle() {
		PVector dir =  getStartDir();
		dir.normalize();
		float angle = (float) Math.atan2(dir.x, -dir.y);
		if(angle < 0)
			angle = (float) (Math.PI*2 + angle);
		return angle;
	}

	public PVector getLerpDir() {
		return new PVector(lerpDirX, lerpDirY);
	}

	public float getAbsMovement() {
		return (float) Math.sqrt(absMovementX*absMovementX+absMovementY*absMovementY);
	}

	public float getTouchPointSize() {
		return touchPointSize;
	}

	public float getTouchPointAngle() {
		return touchPointAngle;
	}

	public float getTouchPointMajorAxis() {
		return touchPointMajorAxis;
	}

	public float getTouchPointMinorAxis() {
		return touchPointMinorAxis;
	}
}
