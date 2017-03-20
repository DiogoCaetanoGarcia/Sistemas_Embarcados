<?php
session_start();
include "remoteRobot.html";
$action = $_GET['GO'];
switch ($action)
{
	case "ON":
		shell_exec('sudo /bin/bash /var/www/init.sh');
		break;
	case "FORWARD":
		shell_exec('sudo /bin/bash /var/www/forward.sh');
		break;
	case "BACKWARD":
		shell_exec('sudo /bin/bash /var/www/backward.sh');
		break;
	case "LEFT":
		shell_exec('sudo /bin/bash /var/www/left.sh');
		break;
	case "RIGHT":
		shell_exec('sudo /bin/bash /var/www/right.sh');
		break;
}
?>
