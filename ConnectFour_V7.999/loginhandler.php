<?php
include("./includes/user.php");
session_start();
$currUser = new User();
$result = $currUser->fillFromSql($_POST["user"], $_POST["pass"]);

//If user and password match database
if ($result != -1){
    //Save login to session
    $_SESSION["loggedIn"] = true;
    $_SESSION["user"] = $_POST["user"];
    $_SESSION["pass"] = $_POST["pass"];
    $_SESSION["err"] = "";
    
    //Send to user stats page
    header("Location: ./displaystats.php");
}
else{
    //If not user found, set login error message
    $_SESSION["err"] = "No user with that username and password";
    //Send back to main page
    header("Location: ./index.php");
}

