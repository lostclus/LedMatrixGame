SCADS=case-bottom.scad \
      case-top.scad \
      power-sw-cap.scad

STLS=$(patsubst %.scad,%.stl,$(SCADS))

%.stl: %.scad
	openscad -o $@ $<

compile: $(STLS)
