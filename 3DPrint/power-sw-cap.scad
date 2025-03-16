cap_size=[4.25, 3.75];
cap_r=0.7;
cap_l=10;

sw_size=[3.15, 2.65];
sw_l=5;

brim_size=[12, 6, 0.75];
brim_pos_y=5.25;

ol=0.01;

include <BOSL2/std.scad>

difference() {
    union() {
	cuboid(
	    [cap_size[0], cap_size[1], cap_l],
	    anchor=BOTTOM,
	    rounding=cap_r,
	    except=TOP,
	    $fn=40*cap_r
	);
	up(cap_l-brim_pos_y)
	    cuboid(
		brim_size,
		anchor=TOP,
		rounding=cap_r,
		edges="Z",
		$fn=40*cap_r
	    );
    }
    up(cap_l+ol)
	cuboid(
	    [sw_size[0], sw_size[1], sw_l+ol],
	    chamfer=-0.2,
	    edges=TOP,
	    anchor=TOP
	);
}
