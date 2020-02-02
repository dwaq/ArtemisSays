include <arduino.scad>

// Full nclosure for the Artemis Says project

// model of the board
//arduino(MEGA);

// case
translate([0, 0, -8.3]) {
	enclosure(MEGA, offset=2, heightExtension=3);
}

/*
// lid
translate([0, 0, 14.6]) {
	enclosureLid(MEGA2560);
}
*/
