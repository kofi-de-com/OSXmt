package com.de.kofi.osxmt;

public enum PointState {
	 PRESSED, RELEASED, HOVER, PRESSING, RELEASING, TAP, UNKNOWN, UNKNOWN_1;
	 
	 public static PointState getFromInt(int stateId) {
		 PointState state;
			switch (stateId) {
				case 1:		state = PointState.UNKNOWN_1; break;
				case 2:		state = PointState.HOVER; break;
				case 3:		state = PointState.TAP; break;
				case 4:		state = PointState.PRESSED; break;
				case 5:		state = PointState.PRESSING; break;
				case 6:		state = PointState.RELEASING; break;
				case 7:		state = PointState.RELEASED; break;
				default:	state = PointState.UNKNOWN; break;
			}
			
			return state;
	 }
}
