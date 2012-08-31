package com.de.kofi.osxmt;

import java.util.HashMap;

import processing.core.PVector;

public interface TouchListener {
	public void mtEvent(HashMap<Integer, TouchPoint> touches);

	public void mtPress(int id, PVector pos, HashMap<Integer, TouchPoint> touches);

	public void mtRelease(int id, PVector pos, HashMap<Integer, TouchPoint> touches);

	public void mtDrag(int id, PVector delta, HashMap<Integer, TouchPoint> touches);

	public void mtScroll(int id, ScrollDirection state, float delta, HashMap<Integer, TouchPoint> touches);

	public void mtTap(int id, PVector pos, HashMap<Integer, TouchPoint> touches);

	public void mtLongPress(int id, PVector pos, HashMap<Integer, TouchPoint> touches);
}
