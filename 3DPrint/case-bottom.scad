include <case-common.scad>

body_h=5;

pcb_standoff_o_d=6.0;
pcb_standoff_i_d=2.9;
pcb_standoff_chamfer=1.5;
pcb_standoff_h=body_h-body_t-1.4;

include <BOSL2/std.scad>

difference() {
    union() {
	difference() {
	    union() {
		cuboid(
		    [
			body_w-body_t-2*case_joiner_tolerance,
			body_l-body_t-2*case_joiner_tolerance,
			body_h
		    ],
		    anchor=BOTTOM,
		    rounding=body_r,
		    except=TOP,
		    $fn=32*body_t
		);
		cuboid(
		    [body_w, body_l, body_h-case_joiner_h],
		    anchor=BOTTOM,
		    rounding=body_r,
		    except=TOP,
		    $fn=32*body_t
		);
	    }

	    up(body_t)
		cuboid(
		    [body_w-2*body_t, body_l-2*body_t, body_h-body_t+2*ol],
		    anchor=BOTTOM,
		    rounding=body_r,
		    except=TOP,
		    $fn=32*body_t
		);
	}

	up(body_t-ol)
	    grid_copies(spacing=[pcb_hole_sp_x, pcb_hole_sp_y], n=[2, 2])
		cyl(
		    d=pcb_standoff_o_d,
		    h=pcb_standoff_h+ol,
		    anchor=BOTTOM,
		    rounding1=-0.25*pcb_standoff_o_d,
		    $fn=16*pcb_standoff_o_d
		);
    }

    down(ol)
	grid_copies(spacing=[pcb_hole_sp_x, pcb_hole_sp_y], n=[2, 2])
	    cyl(
		d=pcb_standoff_i_d,
		h=body_t+pcb_standoff_h+2*ol,
		anchor=BOTTOM,
		chamfer1=-pcb_standoff_chamfer,
		$fn=16*pcb_standoff_i_d
	    );
}

