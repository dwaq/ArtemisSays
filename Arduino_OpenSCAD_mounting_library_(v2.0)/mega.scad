include <arduino.scad>

//Arduino boards
//You can create a boxed out version of a variety of boards by calling the arduino() module
//The default board for all functions is the Uno

//Board mockups
//arduino(MEGA);

// this is just the board
//boardShape(MEGA);
/*
// can be used to remove parts of the Arduino in the render
difference() {
    arduino(MEGA);
    components(MEGA, USB);
}
*/
/*
translate([0, 0, -150]) {
	enclosure(MEGA);
}
*/

// connect a bumper to the bottom of the board
translate([0, 0, -2]) {
	bumper(MEGA);
}

// puts a flat bottom under the bumper
translate([0,0, -3.7]) {
    boardShape(MEGA, offset=1.4);
}

/*
translate([0, 0, 40]) {
	enclosureLid(MEGA);
}*/
