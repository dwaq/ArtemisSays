include <arduino.scad>

// Enclosure for the Artemis Says project

// model of the board
//arduino(MEGA);

// lid
translate([0, 0, -75]) {
	enclosure(MEGA);
}

// case
translate([0, 0, 75]) {
	enclosureLid(MEGA);
}
