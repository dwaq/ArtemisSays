include <arduino.scad>

// Full nclosure for the Artemis Says project

// model of the board
//arduino(MEGA);

// case
translate([7.5, 5, -14.6-8.3-3]) {
	//enclosure(MEGA, offset=2, heightExtension=3);
}

// total width
enclosure_width = 68.34;
enclosure_height = 111.6;
// including tabs
enclosure_depth = 13;

// make display smaller in the Y direction
display_y_difference = 1;

// size & position of display
display_size_x = 19.2;
display_size_y = 21.1-display_y_difference;
// center X
display_pos_x = (enclosure_width-display_size_x)/2;
display_pos_y = 54+display_y_difference;

// cable on display assembly
display_cable_y = 7;

// size & position of mounting screws for display
display_screw_size_rad = 2.1/2;
display_screw_offset_pos_x = 2.2-display_screw_size_rad;
display_screw_offset_pos_y = 2.2+display_screw_size_rad;

// size & position of reset button
button_size_rad = 4.5/2;
button_pos_x = 12;
button_pos_y = 9.2;

// size & position of buzzer
buzzer_size_rad = 12/2;
buzzer_pos_x = 17;
buzzer_pos_y = 99;

// size & position of microphone
mic_size_rad = 1;
mic_pos_x = 46;
mic_pos_y = 95;

// Arrange its children in a regular rectangular array
//      spacing - the space between children origins
//      n       - the number of children along x axis
module arrange(spacing=50, n=5) {
    nparts = $children;
    for(i=[0:1:n-1], j=[0:nparts/n])
        if (i+n*j < nparts)
            translate([spacing*(i+1), spacing*j, 0]) 
                children(i+n*j);
}

// subtract openings from lid
difference() {

// lid
translate([7.5, 5, -3]) {
	enclosureLid(MEGA2560, offset=2);
}

// hole for display
translate([display_pos_x, display_pos_y, -10]) {
	cube([display_size_x, display_size_y, 20]);

    // Z offset here of -14.5 reaches the bottom
    // and Z offset of -10 reaches the top
    // so make a 3.5mm deep hole from the bottom
    screw_offset = -14.5 + 3.5;

    // display cable
    translate([0, -display_cable_y, screw_offset]) {
		cube([display_size_x, display_cable_y, 20]);
	}

	// left screw hole
	translate([-display_screw_offset_pos_x, display_size_y+display_screw_offset_pos_y, screw_offset]) {
		cylinder(r=display_screw_size_rad, h=40, center=true, $fn=30);
	}

	// right screw hole
	translate([display_size_x+display_screw_offset_pos_x, display_size_y+display_screw_offset_pos_y, screw_offset]) {
		cylinder(r=display_screw_size_rad, h=40, center=true, $fn=30);
	}
}

// hole for reset button
translate([button_pos_x, button_pos_y, -10]) {
	cylinder(r=button_size_rad, h=40, center=true, $fn=30);
}

// hole for buzzer
translate([buzzer_pos_x, buzzer_pos_y, -10]) {
	cylinder(r=buzzer_size_rad, h=40, center=true, $fn=30);
}

// hole for microphone
translate([mic_pos_x, mic_pos_y, -10]) {
	arrange(spacing=3, n=1) {
        hull() {
            cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            translate([10,0,0]) {
                cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            }
        }
        hull() {
            cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            translate([10,0,0]) {
                cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            }
        }
        hull() {
            cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            translate([10,0,0]) {
                cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            }
        }
        hull() {
            cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            translate([10,0,0]) {
                cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
            }
        }
	}
}

}