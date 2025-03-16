include <case-common.scad>

body_h=25.5;

pcb_standoff_o_d=5;
pcb_standoff_i_d=2.2;
pcb_standoff_i_h=14;
pcb_standoff_base_h=17;

display_size=64.7;
display_pos_y=5.5;

in_big_button_size=12.5;
in_big_button_r=0.5;
in_big_button_base=[20.5, 85.0];
in_big_buttons=[
    [5*2.54, 0],
    [0, 5*2.54],
    [10*2.54, 5*2.54],
    [5*2.54, 10*2.54],
    [21*2.54, 2.54],
    [19*2.54, 9*2.54],
];

in_small_button_size=5.1;
in_small_button_r=0.1;
in_small_button_base=[19.25, 79.75];
in_small_buttons=[
    [13*2.54, 0],
    [16*2.54, 0],
];

power_sw_pos_y=41.5;
power_sw_pos_z=3.5;
power_sw_size=[9, 4];
power_sw_r=0.7;

charge_conn_pos_y=22.5;
charge_conn_pos_z=2.75;
charge_conn_size=[10, 5];
charge_conn_r=2.0;

include <BOSL2/std.scad>

difference() {
    difference() {
	cuboid(
	    [body_w, body_l, body_h],
	    anchor=BOTTOM,
	    rounding=body_r,
	    except=TOP,
	    $fn=32*body_t
	);

	up(body_h+ol)
	    cuboid(
		[
		    body_w-body_t+2*case_joiner_tolerance,
		    body_l-body_t+2*case_joiner_tolerance,
		    case_joiner_h+ol
		],
		anchor=TOP,
		rounding=body_r,
		edges="Z",
		$fn=32*body_t
	    );

	up(body_t)
	    difference() {
		cuboid(
		    [body_w-2*body_t, body_l-2*body_t, body_h-body_t+2*ol],
		    anchor=BOTTOM,
		    rounding=body_r,
		    except=TOP,
		    $fn=32*body_t
		);

		xflip_copy()
		    difference() {
			union() {
			    left(body_w/2-body_t+ol)
				ycopies(spacing=pcb_hole_sp_y, n=2)
				    cuboid(
					[
					    (body_w-pcb_hole_sp_x)/2-body_t+pcb_standoff_o_d/2,
					    pcb_standoff_o_d,
					    pcb_standoff_base_h
					],
					anchor=BOTTOM+LEFT,
					rounding=pcb_standoff_o_d/2,
					edges="Z",
					except=LEFT,
					$fn=16*pcb_standoff_o_d
				    );
			    left(pcb_hole_sp_x/2)
				ycopies(spacing=pcb_hole_sp_y, n=2)
				    cyl(
					d=pcb_standoff_o_d,
					h=body_h-body_t-case_joiner_h,
					anchor=BOTTOM,
					$fn=16*pcb_standoff_o_d
				    );
			}
			left(pcb_hole_sp_x/2)
			    ycopies(spacing=pcb_hole_sp_y, n=2)
				    up(body_h-body_t-case_joiner_h+ol)
					cyl(
					    d=pcb_standoff_i_d,
					    h=pcb_standoff_i_h+ol,
					    anchor=TOP,
					    chamfer1=pcb_standoff_i_d/2,
					    $fn=16*pcb_standoff_i_d
					);
		    }
	    }
	}

    down(ol) fwd(body_l/2-display_pos_y)
	cuboid(
	    [display_size, display_size, 2*body_t+2*ol],
	    anchor=BOTTOM+FRONT
	);

    down(ol) {
	for(b=in_big_buttons)
	    left(body_w/2-in_big_button_base[0]-b[0])
		fwd(body_l/2-in_big_button_base[1]-b[1])
		    cuboid(
			[in_big_button_size, in_big_button_size, body_t+2*ol],
			anchor=BOTTOM,
			rounding=in_big_button_r,
			edges="Z",
			$fn=6*in_big_button_r
		    );
	for(b=in_small_buttons)
	    left(body_w/2-in_small_button_base[0]-b[0])
		fwd(body_l/2-in_small_button_base[1]-b[1])
		    cuboid(
			[in_small_button_size, in_small_button_size, body_t+2*ol],
			anchor=BOTTOM,
			rounding=in_small_button_r,
			edges="Z",
			$fn=6*in_small_button_r
		    );
    }

    right(body_w/2+ol)
	up(body_h-case_joiner_h-power_sw_pos_z)
	    fwd(body_l/2-power_sw_pos_y)
		cuboid(
		    [body_t+2*ol, power_sw_size[0], power_sw_size[1]],
		    anchor=RIGHT,
		    rounding=power_sw_r,
		    edges="X",
		    $fn=16*power_sw_r
		);

    left(body_w/2+ol)
	up(body_h-case_joiner_h-charge_conn_pos_z)
	    back(body_l/2-charge_conn_pos_y)
		cuboid(
		    [body_t+2*ol, charge_conn_size[0], charge_conn_size[1]],
		    anchor=LEFT,
		    rounding=charge_conn_r,
		    edges="X",
		    $fn=16*charge_conn_r
		);
}
