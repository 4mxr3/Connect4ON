<?php

include("./includes/user.php");
session_start();
$_SESSION["loginErr"] = "";
$currUser = new User();
$result = $currUser->fillFromSql($_SESSION["user"], $_SESSION["pass"]);

if ($result == -1){
    //If not user found, set login error message
    $_SESSION["loginErr"] = "No user with that username and password";
    //Send back to main page
    header("Location: ./index.php");
}


switch ($_POST["result"]){
    case 1:
        //Win
        $currUser->setWins($currUser->getWins() + 1);
        break;
    case 2:
        //Loss
        $currUser->setLosses($currUser->getLosses() + 1);
        break;
    case 3:
        //Tie
        $currUser->setTies($currUser->getTies() + 1);
        break;
}

$currUser->updateSql();

if ($_POST["replay"]){
    header("Location: ./playgame.php");
}else {
    header("Location: ./displaystats.php");
}

?>

