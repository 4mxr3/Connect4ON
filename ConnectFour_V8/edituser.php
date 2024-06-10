<?php
include("./includes/user.php");
if ($_SERVER["REQUEST_METHOD"] != "POST") {
    header("Location: ./index.php");
}
$currUser = new User();
$currUser->fillFromSql($_POST["u"], $_POST["p"]);

$currUser->printStats();
echo "<br>";

$currUser->setUser($_POST["username"]);
$currUser->setPass($_POST["password"]);
$currUser->setfName(ucfirst($_POST["fname"]));
$currUser->setlName(ucfirst($_POST["lname"]));
$currUser->setWins($_POST["wins"]);
$currUser->setLosses($_POST["losses"]);
$currUser->setTies($_POST["ties"]);
$currUser->setAdmin($_POST["admin"]);

$currUser->updateSql();

header("Location: ./allusers.php");