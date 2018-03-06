-- All needed objects are here
req = {};
req[0] = "testBG"
req[1] = "clock1"
req[2] = "bin5"
req[3] = "painting1"
req[4] = "fence"
req[5] = "door51"

-- Tell the Engine were to position what
-- scene.background(Objectstring)
scene.background(req[0]);
-- scene.add(Objectstring, x (relativ bg 0,0), y, z (Layer))
scene.add(req[1], 22, 5, 1);
scene.add(req[2], 11, 100, 1);
scene.add(req[3], 50, 8, 1);
scene.add(req[4], 55, 100, 2);
scene.add(req[5], 75, 80, 1);

-- Hier Actions definieren