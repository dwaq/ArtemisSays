include <arduino.scad>

// Full nclosure for the Artemis Says project

// model of the board
//arduino(MEGA);

// case
translate([7.5, 5, -14.6-8.3-3]) {
	//enclosure(MEGA, offset=2, heightExtension=3);
}

// size & position of display
display_size_x = 20;
display_size_y = 25;
display_pos_x = 25;
display_pos_y = 45;

// size & position of mounting screws for display
display_screw_size_rad = 1;
display_screw_offset_pos_x = 5;
display_screw_offset_pos_y = 5;

// size & position of reset button
button_size_rad = 2;
button_pos_x = 10;
button_pos_y = 10;

// size & position of buzzer
buzzer_size_rad = 7.5;
buzzer_pos_x = 20;
buzzer_pos_y = 95;

// size & position of microphone
mic_size_rad = 0.5;
mic_pos_x = 50;
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

	// left screw hole
	// TODO: adjust Z offset so it doesn't go completely through lid
	translate([-display_screw_offset_pos_x, display_size_y+display_screw_offset_pos_y, 0]) {
		cylinder(r=display_screw_size_rad, h=40, center=true, $fn=30);
	}

	// right screw hole
	// TODO: adjust Z offset so it doesn't go completely through lid
	translate([display_size_x+display_screw_offset_pos_x, display_size_y+display_screw_offset_pos_y, 0]) {
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
	arrange(spacing=2, n=5) {
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
		cylinder(r=mic_size_rad, h=40, center=true, $fn=30);
	}
}

}