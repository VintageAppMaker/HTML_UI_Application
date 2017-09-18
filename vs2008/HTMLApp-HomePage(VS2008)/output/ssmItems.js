<!--

/*
Configure menu styles below
NOTE: To edit the link colors, go to the STYLE tags and edit the ssm2Items colors
*/
YOffset=50; // no quotes!!
XOffset=0;
staticYOffset=30; // no quotes!!
slideSpeed=20 // no quotes!!
waitTime=100; // no quotes!! this sets the time the menu stays out for after the mouse goes off it.
menuBGColor="black";
menuIsStatic="yes"; //this sets whether menu should stay static on the screen
menuWidth=150; // Must be a multiple of 10! no quotes!!
menuCols=2;
hdrFontFamily="굴림";
hdrFontSize="2";
hdrFontColor="white";
hdrBGColor="#222222";
hdrAlign="left";
hdrVAlign="center";
hdrHeight="15";
linkFontFamily="Verdana";
linkFontSize="2";
linkBGColor="white";
linkOverBGColor="#FFFF99";
linkTarget="_top";
linkAlign="Left";
barBGColor="#111111";
barFontFamily="굴림";
barFontSize="2";
barFontColor="white";
barVAlign="center";
barWidth=28; // no quotes!!
barText="Menu"; // <IMG> tag supported. Put exact html for an image to show.

///////////////////////////

// ssmItems[...]=[name, link, target, colspan, endrow?] - leave 'link' and 'target' blank to make a header
ssmItems[0]=["메인페이지"]//create header
ssmItems[1]=["홈..",    "main.html",""]
ssmItems[2]=["Project...", "", ""] //create header
ssmItems[3]=["업무관리", "work.html",    ""]
ssmItems[4]=["scrap...", "", ""] //create header
ssmItems[5]=["스크랩", "scrap.html",    ""]
ssmItems[6] =["About...", "", ""] //create header
ssmItems[7]=["사용법", "tutorial.html",    ""]

buildMenu();

//-->
