include <arduino.scad>

// Full nclosure for the Artemis Says project

// model of the board
//arduino(MEGA);

// case
translate([7.5, 5, -14.6-8.3-3]) {
	enclosure(MEGA, offset=2, heightExtension=3);
}

// lid
translate([7.5, 5, -3]) {
	enclosureLid(MEGA2560, offset=2);
}
